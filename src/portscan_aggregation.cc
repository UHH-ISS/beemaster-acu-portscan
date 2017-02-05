//
// Created by florian on 2/1/17.
//

#include "portscan_aggregation.h"
#include "rocks_storage.h"
#include "utils.h"

namespace beemaster {

    PortscanAggregation::PortscanAggregation(acu::Storage *storage, std::vector<acu::Threshold> *thresholds)
            : Aggregation(storage, thresholds), alert_count(0) {
    }

    bool PortscanAggregation::Invoke(const acu::IncomingAlert *alert) {

        auto rocks = (RocksStorage*)storage;
        auto last_ts = rocks->Get("date/" + alert->destination_ip());
        auto now = std::chrono::system_clock::now();

        if (!last_ts.empty() && decrement_minutes(now, (uint16_t)thresholds->at(1).count) > last_ts) {
            rocks->Delete(alert->destination_ip());
            rocks->Delete("date/" + alert->destination_ip());
        }

        return ++alert_count % thresholds->at(0).count == 0;
    }
}
