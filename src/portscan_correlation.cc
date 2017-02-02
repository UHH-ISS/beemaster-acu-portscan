//
// Created by florian on 2/1/17.
//

#include "portscan_correlation.h"
#include <iostream>

namespace beemaster {

    PortscanCorrelation::PortscanCorrelation(acu::Storage *storage, std::vector<acu::Threshold> *thresholds)
            : Correlation(storage, thresholds) {
    }

    acu::OutgoingAlert* PortscanCorrelation::Invoke() {
        std::cout << "Invoke called!" << std::endl;
        return nullptr;
    }
}
