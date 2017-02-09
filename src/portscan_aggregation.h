//
// Created by florian on 2/1/17.
//

#ifndef ACU_IMPL_PORTSCAN_AGGREGATION_H
#define ACU_IMPL_PORTSCAN_AGGREGATION_H

#include <acu/aggregation.h>

namespace beemaster {

    class PortscanAggregation : public acu::Aggregation {
    public:
        const static std::string THRESHOLD_PORT;
        const static std::string THRESHOLD_TIMESTAMP;

        PortscanAggregation(acu::Storage *storage, std::vector<acu::Threshold> *thresholds);

        bool Invoke(const acu::IncomingAlert*);
    private:
        uint64_t alert_count;

        uint64_t threshold_port;
        uint64_t threshold_timestamp;
    };
}


#endif //ACU_IMPL_PORTSCAN_AGGREGATION_H
