//
// Created by florian on 2/1/17.
//

#include "tcp_event.h"

namespace beemaster {

    TcpEvent::TcpEvent(const std::string *topic, const broker::message &msg)
            : IncomingAlert(topic, msg) {
        assert(msg.size() >= 2);
    }

    const TcpType& TcpEvent::type() const {
        assert(broker::is<uint32_t>(message[1]));
        return (TcpType&)(*broker::get<uint32_t>(message[1]));
    }
}
