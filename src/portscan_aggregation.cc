//
// Created by florian on 2/1/17.
//

#include "portscan_aggregation.h"

namespace beemaster {

    PortscanAggregation::PortscanAggregation(acu::Storage *storage, std::vector<acu::Threshold> *thresholds)
            : Aggregation(storage, thresholds), alert_count(0) {
    }

    bool PortscanAggregation::Invoke(const acu::IncomingAlert *alert) {
        return ++alert_count % thresholds->at(0).count == 0;
    }
}
