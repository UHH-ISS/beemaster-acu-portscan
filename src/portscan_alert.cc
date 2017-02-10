/* portscan_alert.cc
 * ACU Implementation
 *
 * <src/portscan_alert.h>
 */

#include "portscan_alert.h"

namespace beemaster {
    using namespace std::chrono;


    PortscanAlert::PortscanAlert(const std::string &name, const time_point<system_clock> &timestamp)
            : OutgoingAlert(name, timestamp), destination_ips(std::vector<std::string>()) {
    }

    const std::string PortscanAlert::EventName() const {
        // this event name can be used in bro scripts
        return "Beemaster::portscan_meta_alert";
    }

    const broker::message PortscanAlert::ToMessage() const {
        auto ips = new broker::vector();
        for (const auto &ip : destination_ips) {
            ips->push_back(ip);
        }
        auto msg = acu::OutgoingAlert::ToMessage();
        msg.push_back(*ips);
        //std::cout << "PortscanAlert ToMessage() built msg: " << broker::to_string(msg) << std::endl;
        return msg;
    }
}
