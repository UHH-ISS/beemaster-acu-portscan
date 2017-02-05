//
// Created by florian on 2/1/17.
//

#ifndef ACU_IMPL_PORTSCAN_AGGREGATION_H
#define ACU_IMPL_PORTSCAN_AGGREGATION_H

#include <acu/aggregation.h>

namespace beemaster {

    class PortscanAggregation : public acu::Aggregation {
    public:
        PortscanAggregation(acu::Storage *storage, std::vector<acu::Threshold> *thresholds);

        bool Invoke(const acu::IncomingAlert*);
    private:
        long alert_count;
    };
}


#endif //ACU_IMPL_PORTSCAN_AGGREGATION_H
