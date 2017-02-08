//
// Created by florian on 2/1/17.
//

#include "portscan_correlation.h"
#include "portscan_alert.h"
#include <algorithm>

namespace beemaster {

    // PUBLIC
    const std::string PortscanCorrelation::THRESHOLD_PORT_COUNT = "__portcount__";

    // PRIVATE
    const std::string NAME = "Portscan";
    const std::string PREFIX_DATE = "date/";

    PortscanCorrelation::PortscanCorrelation(RocksStorage *storage, std::vector<acu::Threshold> *thresholds)
            : Correlation(storage, thresholds), threshold_port(0) {
        for (const auto &thr : *thresholds) {
            if (thr.field_name == THRESHOLD_PORT_COUNT) {
                threshold_port = thr.count;
            }
        }
    }

    acu::OutgoingAlert* PortscanCorrelation::Invoke() {
        auto rocks = (RocksStorage*)storage;
        auto it = rocks->GetIterator();

        PortscanAlert *alert = nullptr;
        for (it->SeekToFirst(); it->Valid(); it->Next()) {

            if (it->key().ToString().find(PREFIX_DATE) == 0) {
                // Skip our inserted dates
                continue;
            }

            // We have a valid ip entry
            auto ports = it->value().ToString();
            if ((uint64_t)(std::count(ports.begin(), ports.end(), '|') + 1) >= threshold_port) {
                // We detected a portscan -> generate meta alert
                if (!alert) {
                    alert = new PortscanAlert(NAME, std::chrono::system_clock::now());
                }

                alert->destination_ips.push_back(it->key().ToString());
            }
        }

        // Do we really need to call delete when the iterator goes out-of-scope
        // immediately after? What about RAII?
        delete it;

        if (alert != nullptr) {
            std::cout << "OutgoingAlert: " << alert->incidentName << std::endl;
        }

        // Might be null, which is okay!
        return alert;
    }
}
