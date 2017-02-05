## Lattice Implementation for a `beemaster` Alert Correlation Unit

#### Build

- git-checkout this repository
- on the same level in the folder tree, git-checkout the ACU-FW repository
- `make` the framework
- `make` this concrete implementation

#### Container build

The framework is included as submodule, so the container build is a lot easier. Simply do `docker build . -t acu && docker run acu`


Notizen mit Flo, WIP:

zeitintervall 	        - verlängert sich ggf jedesmal
dst_ip			- gleiches ziel
dst_port 		- zum checken dass ports unterschiedlich


---------------------------------------------------------

DB key design

dst_ip1 / { dst_ports }
dst_ip2 / { dst_ports }

date / dst_ip1 / current_range
date / dst_ip2 / current_range
