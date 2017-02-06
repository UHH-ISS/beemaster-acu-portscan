//
// Created by florian on 2/6/17.
//

#include "portscan_alert.h"

namespace beemaster {
    using namespace std::chrono;

    PortscanAlert::PortscanAlert(const std::string &name, const time_point<system_clock> &timestamp)
            : OutgoingAlert(name, timestamp), destination_ips(std::vector<std::string>()) {
    }

    const broker::message PortscanAlert::ToMessage() {
        auto ips = new broker::vector();
        for (const auto &ip : destination_ips) {
            ips->push_back(ip);
        }
        auto msg = acu::OutgoingAlert::ToMessage();
        msg.push_back(*ips);

        return msg;
    }
}
