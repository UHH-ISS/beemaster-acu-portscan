# Portscan ACU

#### Build

- git-checkout this repository
- on the same level in the folder tree, git-checkout the ACU-FW repository
- `make` the framework
- `make` this concrete implementation

#### Container build

Das ACU Framework ist als git-submodule in diesem Projekt eingebunden, sodass der Container Build einfacher wird. Mit `docker build . -t acu && docker run acu` kann die ACU gebaut und gestartet werden.

## RocksDB und Portscan Keydesign

In der Portscan ACU wird [RocksDB](http://rocksdb.org) als persistenter Speicher verwendet. RocksDB ist ein schneller Key-Value Store, der eine native C++ API bietet.

Um effizient auf Daten zugreifen zu können, bedarf es eines geschickten Key-Designs. Für die Portscan ACU ist dies wie folgt:

`destination_ip / { desination_port }`

`"date" / destination_ip / last_modified_ts`

Jedes mal, wenn ein `IncomingAlert` -- hier nur speziell TCP Events -- von Bro empfangen wird, wird dieser (durch das Framework) persistiert. Dabei wird die zugegriffene IP als Key verwendet, das Value ist die Menge aller auf dieser IP zugegriffenen Ports. Außerdem wird unter dem Prefix `date/` der Zeitstempel gespeichert, andem zuletzt auf diese IP zugegriffen wurde.

## Portscan Erkennung

TODO