//
// Created by florian on 2/2/17.
//

#ifndef ACU_IMPL_ALERTMAPPER_H
#define ACU_IMPL_ALERTMAPPER_H

#include <acu/alert_mapper.h>

namespace beemaster {

    class AlertMapper : public acu::AlertMapper {
    public:
        acu::IncomingAlert* GetAlert(const std::string*, const broker::message&) const;
    };
}


#endif //ACU_IMPL_ALERTMAPPER_H
