//
// Created by florian on 2/1/17.
//

#ifndef ACU_IMPL_TCP_EVENT_H
#define ACU_IMPL_TCP_EVENT_H

#include <acu/incoming_alert.h>

namespace beemaster {

    enum TcpType : unsigned int {
        SYN = 1
    };

    class TcpAlert : public acu::IncomingAlert {
    public:
        explicit TcpAlert(const std::string *, const broker::message&);

        const TcpType& type() const;
    };
}


#endif //ACU_IMPL_TCP_EVENT_H
