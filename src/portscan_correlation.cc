//
// Created by florian on 2/1/17.
//

#include "portscan_correlation.h"
#include "rocks_storage.h"
#include <iostream>
#include <algorithm>

namespace beemaster {

    PortscanCorrelation::PortscanCorrelation(RocksStorage *storage, std::vector<acu::Threshold> *thresholds)
            : Correlation(storage, thresholds) {
    }

    acu::OutgoingAlert* PortscanCorrelation::Invoke() {
        auto rocks = (RocksStorage*)storage;
        auto it = rocks->GetIterator();

        for (it->SeekToFirst(); it->Valid(); it->Next()) {
            if (it->key().ToString().find("date/") == 0) {
                continue;
            }

            auto ports = it->value().ToString();
            if (std::count(ports.begin(), ports.end(), '|') +1 >= thresholds->at(0).count) {
                std::cout << "ALERT, deine mutter brennt" << std::endl;
            }

        }
        delete it;

        return nullptr;
    }
}
