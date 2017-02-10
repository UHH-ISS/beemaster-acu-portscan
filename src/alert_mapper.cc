/* alert_mapper.cc
 * ACU Implementation
 *
 * <src/alert_mapper.h>
 */

#include "alert_mapper.h"
#include "tcp_alert.h"

namespace beemaster {

    acu::IncomingAlert *AlertMapper::GetAlert(const std::string *topic, const broker::message &msg) const {
        if (broker::is<std::string>(msg[0])) {
            auto event_name = broker::get<std::string>(msg[0]);
            if (event_name[0] == "beemaster::tcp_event") {
                return new TcpAlert(topic, msg);
            }
        }
        return acu::AlertMapper::GetAlert(topic, msg);
    }
}
