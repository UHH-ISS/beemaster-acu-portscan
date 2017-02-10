//
// Created by florian on 2/1/17.
//

#ifndef ACU_IMPL_PORTSCAN_AGGREGATION_H
#define ACU_IMPL_PORTSCAN_AGGREGATION_H

#include <acu/aggregation.h>

namespace beemaster {

    class PortscanAggregation : public acu::Aggregation {
    public:
        /// Constant port fieldname for the threshold 
        const static std::string THRESHOLD_PORT;
        /// Constant timestamp fieldname for the threshold
        const static std::string THRESHOLD_TIMESTAMP;

        /// Instantiate a PortscanAggregation.
        ///
        /// \param storage      The shared storage object
        /// \param threshold    The thresholds to trigger the PortscanCorrelation
        PortscanAggregation(acu::Storage *storage, std::vector<acu::Threshold> *thresholds);

        /// Method triggered upon new IncomingAlert.
        /// Aggregates values and returns true, if the correlation shall be triggered.
        ///
        /// \param alert    The new IncomingAlert.
        /// \return     True, if correlation shall be triggered, false otherwise
        bool Invoke(const acu::IncomingAlert*);
    private:
        uint64_t alert_count;

        uint64_t threshold_port;
        uint64_t threshold_timestamp;
    };
}


#endif //ACU_IMPL_PORTSCAN_AGGREGATION_H
