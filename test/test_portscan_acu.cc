/* test_portscan_acu.cc
 * ACU Framework (test)
 *
 * Dataflow test for the Portscan ACU.
 *
 * @author: 0ortmann
 */

#include "catch.hpp"

#include <acu/acu.h>
#include <broker/message_queue.hh>

#include <unistd.h>
#include <rocks_storage.h>
#include <portscan_aggregation.h>
#include <portscan_correlation.h>
#include <alert_mapper.h>


TEST_CASE("Testing ACU roundtrip dataflow", "[acu]") {

    // This is kind of a "framework integration test"

    acu::AlertMapper *mapper = new acu::AlertMapper();
    auto thr = acu::Threshold(1, "proto", "http");
    auto thresholds = new std::vector<acu::Threshold>();
    thresholds->push_back(thr);

    auto inc_topic = "beemaster/bro/tcp";
    auto alert_topic = "beemaster/acu/alert";

    auto rocks_path = "/tmp/portscan_acu_test_rocks";
    auto rec_addr = "127.0.0.1";
    auto rec_port = 8888;
    auto sender_addr = "127.0.0.1";
    auto sender_port = 7777;

    auto rocks = new beemaster::RocksStorage(rocks_path);
    auto alert_mapper = new beemaster::AlertMapper();

    // setup algorithms
    auto agg_ths = new std::vector<acu::Threshold>;
    agg_ths->push_back(acu::Threshold(1, beemaster::PortscanAggregation::THRESHOLD_PORT, "*"));
    agg_ths->push_back(acu::Threshold(1, beemaster::PortscanAggregation::THRESHOLD_TIMESTAMP, "*"));
    auto portscan_agg = new beemaster::PortscanAggregation(rocks, agg_ths);

    auto corr_ths= new std::vector<acu::Threshold>;
    corr_ths->push_back(acu::Threshold(1, beemaster::PortscanCorrelation::THRESHOLD_PORT_COUNT, "*"));

    auto portscan_corr = new beemaster::PortscanCorrelation(rocks, corr_ths);

    // setup acu
    auto acu = acu::Acu(rocks, alert_mapper);
    // - set connection details
    acu.SetReceiverInfo(rec_addr, rec_port);
    acu.SetSenderInfo(sender_addr, sender_port);
    // - add algorithms
    acu.Register(new std::vector<std::string>{inc_topic}, portscan_agg, portscan_corr);

    // remote bro-broker "mock" via localhost
    broker::endpoint meta_alert_rec("Meta Alert Receiver",
                                    broker::AUTO_ROUTING | broker::AUTO_ADVERTISE);
    broker::message_queue meta_alert_queue(alert_topic, meta_alert_rec, broker::GLOBAL_SCOPE);

    meta_alert_rec.listen(sender_port, sender_addr);

    auto inc_alert_sender = broker::endpoint("incoming alert sender",
                                             broker::AUTO_ROUTING | broker::AUTO_PUBLISH);

    inc_alert_sender.listen(rec_port, rec_addr);
    usleep(100 * 1000);

    std::cout << "ACU start" <<std::endl;
    acu.Run();


    SECTION("Test successful roundtrip") {
        auto time_stamp = std::chrono::system_clock::now();
        auto truncated = std::chrono::duration_cast<std::chrono::duration<double>>(time_stamp.time_since_epoch());
        auto broker_stamp = broker::time_point{truncated.count()};
        auto rec = broker::record({
                                          broker::record::field(broker_stamp),
                                          broker::record::field("127.0.0.1"),
                                          broker::record::field((acu::port_t)8080),
                                          broker::record::field("192.168.0.1"),
                                          broker::record::field((acu::port_t)9090)

        });
        auto msg = broker::message{inc_topic, rec, 1};

        // the fake incoming alert sender must have received a peer from our receiver
        REQUIRE(inc_alert_sender.incoming_connection_status().need_pop().front().status
                == broker::incoming_connection_status::tag::established);

        inc_alert_sender.send(inc_topic, msg);
        usleep(1000*300);
        acu.CheckForAlerts();
        usleep(1000*500); // rocksdb interaction


        std::cout << "If the tests hangs here, the test is failing!" << std::endl;
        for (auto &msg : meta_alert_queue.need_pop()) {
            std::cout << broker::to_string(msg) <<std::endl;
            REQUIRE(msg.at(0) == "Beemaster::portscan_meta_alert");
            //REQUIRE(msg.at(1) == well, figure it..);
            REQUIRE(msg.at(2) == "Portscan");
            REQUIRE(broker::to_string(msg.at(3)) == "[192.168.0.1]");
        }
    }
}
