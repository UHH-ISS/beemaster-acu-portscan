/* main.cc
 * ACU Implementation
 *
 * The entrypoint for this ACU.
 * Sets everything up and starts the work.
 *
 * @author: 1jost
 */

#include <acu/acu.h>

#include "alert_mapper.h"
#include "config_parser.h"
#include "portscan_correlation.h"
#include "rocks_storage.h"
#include "vector_storage.h"
#include "portscan_aggregation.h"

#include <csignal>
#include <iostream>
#include <unistd.h>

using namespace beemaster;

/// http://en.cppreference.com/w/cpp/utility/program/signal
void signal_handler(int signum) {
    // TODO do we want to keep this?
    std::cout << "Received signal " << signum << ". Aborting." << std::endl;
    exit(signum);
}

/// The main function to invoke this ACU
///
/// This program expects a path to the configuration to use and
/// fails, if none is given.
///
/// The configuration file uses basic INI format. Sections are
/// marked in brackets (`[section]`). Key-value pairs are separated
/// by an equals sign (`=`). Comments are introduced with a hash
/// (`#`).
///
/// The following entries are expected (case-sensitive!):
///     storage/location = <path of storage location>
///     receiver/address = <address to listen on>
///     receiver/port    = <port to listen on>
///     sender/address   = <address to send to>
///     sender/port      = <port to send to>
/// There are no default values (for now).
///
/// @param argc     Number of passed arguments
/// @param argv     Array of arguments
/// @return         Status
int main(int argc, char* argv[]) {
    // setup signal handler for endless loop
    std::signal(SIGINT, signal_handler);
    std::signal(SIGTERM, signal_handler);

    // parsing argument // alternatively: getopt(3)
    if (argc < 2)
        throw std::runtime_error("Expect one argument for the configuration path!");
    std::string config_file(argv[1]);

    // parsing config
    auto config = ConfigParser(config_file);

    auto rocks_path = config.GetString("storage", "location");
    auto rec_addr = config.GetString("receiver", "address");
    auto rec_port = (acu::port_t)config.GetInt("receiver", "port");
    auto sender_addr = config.GetString("sender", "address");
    auto sender_port = (acu::port_t)config.GetInt("sender", "port");

    // setup storages
    auto rocks = new RocksStorage(rocks_path);

    // get mapper
    auto alert_mapper = new beemaster::AlertMapper();

    // setup algorithms
    auto agg_ths = new std::vector<acu::Threshold>;
    agg_ths->push_back(acu::Threshold(50, "destination_port", "*"));
    agg_ths->push_back(acu::Threshold(10, "timestamp", "*"));
    auto portscan_agg = new PortscanAggregation(rocks, agg_ths);

    auto corr_ths= new std::vector<acu::Threshold>;
    corr_ths->push_back(acu::Threshold(500, "dst_port", "*"));

    auto portscan_corr = new PortscanCorrelation(rocks, corr_ths);

    // setup acu
    auto acu = acu::Acu(rocks, alert_mapper);
    // - set connection details
    acu.SetReceiverInfo(rec_addr, rec_port);
    acu.SetSenderInfo(sender_addr, sender_port);
    // - add algorithms
    acu.Register(new std::vector<std::string>{"beemaster/bro/tcp"}, portscan_agg, portscan_corr);

    // start acu
    acu.Run();
    for (;;) {
        acu.CheckForAlerts();
        usleep(100);
    }

    return 0;
}
