//
// Created by florian on 2/1/17.
//

#ifndef ACU_IMPL_PORTSCAN_CORRELATION_H
#define ACU_IMPL_PORTSCAN_CORRELATION_H

#include <acu/correlation.h>
#include "rocks_storage.h"

namespace beemaster {

    class PortscanCorrelation : public acu::Correlation {
    public:
        /// Constant port-count fieldname for the threshold
        const static std::string THRESHOLD_PORT_COUNT;

        /// Instantiate a PortscanCorrelation.
        /// 
        /// \param storage      The shared storage object
        /// \param threshold    The thresholds for operation granulation
        PortscanCorrelation(RocksStorage *storage, std::vector<acu::Threshold> *thresholds);

        /// Method triggered by the aggregation result.
        /// Correlates aggregated data to build up a possible meta-alert.
        ///
        /// \return     nullptr, if no correlation happened; valid OutgoingAlert otherwise
        acu::OutgoingAlert* Invoke();

    private:
        uint64_t threshold_port;
    };
}


#endif //ACU_IMPL_PORTSCAN_CORRELATION_H
