//
// Created by florian on 2/6/17.
//

#ifndef ACU_IMPL_PORTSCAN_ALERT_H
#define ACU_IMPL_PORTSCAN_ALERT_H

#include <acu/outgoing_alert.h>

namespace beemaster {
    class PortscanAlert : public acu::OutgoingAlert {
    public:
        PortscanAlert(const std::string &name,
                      const std::chrono::time_point<std::chrono::system_clock> &timestamp);

        std::vector<std::string> destination_ips;

        const std::string EventName() const override;
        const broker::message ToMessage() const override;
    };
}


#endif //ACU_IMPL_PORTSCAN_ALERT_H
