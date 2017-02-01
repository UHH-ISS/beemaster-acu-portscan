//
// Created by florian on 2/1/17.
//

#include "portscan_aggregation.h"

namespace beemaster {

    PortscanAggregation::PortscanAggregation(acu::Storage *storage, std::vector<acu::Threshold> *thresholds)
            : Aggregation(storage, thresholds) {
    }
}
