//
// Created by florian on 2/1/17.
//

#include "portscan_correlation.h"

namespace beemaster {

    PortscanCorrelation::PortscanCorrelation(acu::Storage *storage, std::vector<acu::Threshold> *thresholds)
            : Correlation(storage, thresholds) {
    }
}
