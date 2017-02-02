//
// Created by florian on 2/1/17.
//

#ifndef ACU_IMPL_PORTSCAN_CORRELATION_H
#define ACU_IMPL_PORTSCAN_CORRELATION_H

#include <acu/correlation.h>

namespace beemaster {

    class PortscanCorrelation : public acu::Correlation {
    public:
        PortscanCorrelation(acu::Storage *storage, std::vector<acu::Threshold> *thresholds);

        acu::OutgoingAlert* Invoke();
    };
}


#endif //ACU_IMPL_PORTSCAN_CORRELATION_H
