//
// Created by florian on 2/2/17.
//

#include "alert_mapper.h"
#include "tcp_alert.h"

namespace beemaster {

    acu::IncomingAlert *AlertMapper::GetAlert(const std::string *topic, const broker::message &msg) const {
        auto event_name = broker::get<std::string>(msg[0]);
        if (event_name[0] == "beemaster::tcp_event") {
            return new TcpAlert(topic, msg);
        }
        return acu::AlertMapper::GetAlert(topic, msg);
    }
}
