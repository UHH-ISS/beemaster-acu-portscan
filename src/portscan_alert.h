//
// Created by florian on 2/6/17.
//

#ifndef ACU_IMPL_PORTSCAN_ALERT_H
#define ACU_IMPL_PORTSCAN_ALERT_H

#include <acu/outgoing_alert.h>

namespace beemaster {
    class PortscanAlert : public acu::OutgoingAlert {
    public:
        /// Instantiate a PortscanAlert.
        /// This alert represents an outgoing alert, produced by the PortscanCorrelation.
        ///
        /// \param name         The name of the event
        /// \param timestamp    The point in time, this alert was created
        PortscanAlert(const std::string &name,
                      const std::chrono::time_point<std::chrono::system_clock> &timestamp);

        /// The targeted IP adresses
        std::vector<std::string> destination_ips;

        /// \return     This event's name
        const std::string EventName() const override;
        /// \return     The corresponding broker-message of this alert
        const broker::message ToMessage() const override;
    };
}


#endif //ACU_IMPL_PORTSCAN_ALERT_H
