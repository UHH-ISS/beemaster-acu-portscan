# Custom Beemaster ACU

Beemaster ships with two custom ACU implementations, using the Beemaster [acu framework](https://git.informatik.uni-hamburg.de/iss/mp-ids-acu-fw). The `master` branch of this repository contains the general Beemaster setup for custom ACUs, featuring a build setup and Dockerfile. Additionally, it contains the sources for a portscan detection ACU.

A second ACU can be found at the `experimental_lattice` branch. It is a more sophisticated ACU, implementing the lattice algorithm. Please find the details below.

## Build & run

The build instructions are generally the same for all branches.

This repository references the acu framework repository as submodule in [mp-ids-acu-fw](mp-ids-acu-fw). Please use `git clone --recursive` when cloning this repo.


#### Manual build & run

A call to `make` will first build the framework and then build the actual ACU. This needs to be done, since the ACU links against the framework library `.so`. The compiled binary of the ACU can then be found in the `build/` directory.

The compiled binay inside the build directory can be executed. A config file must be provided as first argument. Use the following command for a local start (local means Bro master is running on the same host as the ACU): `build/src/acu-impl config-local.ini`

#### Container build & run

This repo contains a [Dockerfile](Dockerfile). It can be uesd to build the ACU with all required resources and bundle into a Docker image (eg. via `docker build . -t acu_portscan`).

The dockerized ACU can be run with `docker run --name acu acu_portscan`.

You can use the [start.sh](start.sh) script, it executes the two above commands.


## RocksDB and keydesign

The portscan ACU uses [RocksDB](http://rocksdb.org) as persistent storage abstraction. RocksDB is a fast key value store that comes with a native C++ API.

To use the key value structure efficiently, a clever key design is needed. The portscan ACU stores data as follows:

`destination_ip / { desination_port }`

`"date" / destination_ip / last_modified_ts`

The [rocksdb storage](src/rocks_storage.h) class implements the storage interface of the ACU framework. Thus, every time an `IncomingAlert` enters the ACU, it gets persisted (framework operation). We use the accessed IP as key and the set of accessed ports of that IP as values. The prefix `date/` is used to store timestamps of the last change of the portset of an IP.

## Portscan detection

The runtime configuration of the portscan ACU can be seen in the [main class](src/main.cc). Custom algorithms for that implement the ACU frameworks `Aggregation` and `Correlation` classes are registered to an `ACU` instance. Thresholds are used to configure the aggregation with a message count of `50` and a `10 minutes` timeframe. The correlation is configured with a `500` different ports threshold.

Whenever 50 `IncomingAlerts` have been counted within a timeframe of 10 minutes, the aggregation reports a positive value. Then the correlation is triggered. If the correlation detects (by database lookup) that on any IP more than 500 different ports have been accessed, a meta alert is generated. The meta alert contains basic information of about the type of the attack (`Portscan`) and a list of IPs under attack.


## Lattice

TODO: lattice beschreiben (@marco)