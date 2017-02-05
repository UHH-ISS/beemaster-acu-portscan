//
// Created by florian on 2/1/17.
//

#include "portscan_correlation.h"
#include "rocks_storage.h"
#include <iostream>

namespace beemaster {

    PortscanCorrelation::PortscanCorrelation(RocksStorage *storage, std::vector<acu::Threshold> *thresholds)
            : Correlation(storage, thresholds) {
    }

    acu::OutgoingAlert* PortscanCorrelation::Invoke() {
        auto rocks = (RocksStorage*)storage;
        auto it = rocks->GetIterator();

        for (it->SeekToFirst(); it->Valid(); it->Next()) {
            std::cout << it->key().ToString() << ":" << it->value().ToString() << std::endl;
        }
        delete it;
        /*for (it->Seek("0.0.0.0");
            it->Valid() && it->key().ToString() < "255.255.255.255";
            it->Next()) {

            std::cout << it->value().ToString() << std::endl;
        }*/
        return nullptr;
    }
}
