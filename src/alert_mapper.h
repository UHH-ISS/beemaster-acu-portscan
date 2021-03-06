/* alert_mapper.h
 * ACU Implementation
 *
 * Provide an implementation of the AlertMapper for this
 * particular ACU. It is implemented for TcpAlerts.
 *
 * @author: 1jost
 */

#ifndef ACU_IMPL_ALERTMAPPER_H
#define ACU_IMPL_ALERTMAPPER_H

#include <acu/alert_mapper.h>

namespace beemaster {

    class AlertMapper : public acu::AlertMapper {
    public:
        /// Map an incoming broker-message into an IncomingAlert.
        /// The implementation may decide to return a more specific alert.
        ///
        /// \param topic    The topic, this message arrived on
        /// \param msg      The message, which will be converted
        /// \return         The corresponding IncomingAlert (possible subtype)
        acu::IncomingAlert* GetAlert(const std::string*, const broker::message&) const;
    };
}


#endif //ACU_IMPL_ALERTMAPPER_H
