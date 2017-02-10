//
// Created by florian on 2/1/17.
//

#ifndef ACU_IMPL_TCP_EVENT_H
#define ACU_IMPL_TCP_EVENT_H

#include <acu/incoming_alert.h>

namespace beemaster {

    /// Type of a TCP message
    enum TcpType : unsigned int {
        /// SYN TCP event
        SYN = 1
    };

    class TcpAlert : public acu::IncomingAlert {
    public:
        /// Instantiate a TcpAlert.
        /// This alert represents an incoming tcp event.
        ///
        /// \param topic    The topic, this alert was sent on
        /// \param msg      The message of this event
        explicit TcpAlert(const std::string *, const broker::message&);

        /// \return     The TcpType of this event
        const TcpType& type() const;
    };
}


#endif //ACU_IMPL_TCP_EVENT_H
