//
// Created by florian on 2/1/17.
//

#include "portscan_aggregation.h"
#include "rocks_storage.h"
#include "utils.h"

namespace beemaster {

    const std::string PortscanAggregation::THRESHOLD_PORT = "__destination_port__";
    const std::string PortscanAggregation::THRESHOLD_TIMESTAMP = "__timestamp__";

    PortscanAggregation::PortscanAggregation(acu::Storage *storage, std::vector<acu::Threshold> *thresholds)
            : Aggregation(storage, thresholds), alert_count(0), threshold_port(0), threshold_timestamp(0) {
        for (const auto &thr : *thresholds) {
            if (thr.field_name == THRESHOLD_PORT) {
                threshold_port = thr.count;
            } else if (thr.field_name == THRESHOLD_TIMESTAMP) {
                threshold_timestamp = thr.count;
            }
        }
    }

    bool PortscanAggregation::Invoke(const acu::IncomingAlert *alert) {

        auto rocks = (RocksStorage*)storage;
        auto last_ts = rocks->Get("date/" + alert->destination_ip());
        auto now = std::chrono::system_clock::now();

        if (!last_ts.empty() && decrement_minutes(now, threshold_timestamp) > last_ts) {
            rocks->Delete(alert->destination_ip());
            rocks->Delete("date/" + alert->destination_ip());
        }

        return ++alert_count % threshold_port == 0;
    }
}
