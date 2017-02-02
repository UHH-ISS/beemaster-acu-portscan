//
// Created by florian on 2/1/17.
//

#include "tcp_alert.h"

namespace beemaster {

    TcpAlert::TcpAlert(const std::string *topic, const broker::message &msg)
            : IncomingAlert(topic, msg) {
        assert(msg.size() >= 3);
    }

    const TcpType& TcpAlert::type() const {
        assert(broker::is<uint32_t>(message[2]));
        return (TcpType&)(*broker::get<uint32_t>(message[2]));
    }
}
