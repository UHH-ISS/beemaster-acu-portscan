## Lattice Implementation for a `beemaster` Alert Correlation Unit

#### Build

- git-checkout this repository
- on the same level in the folder tree, git-checkout the ACU-FW repository
- `make` the framework
- `make` this concrete implementation 

#### Container build

In order to build and use this ACU implementation, the `beemaster` ACU-Framework is required. The framework has to be built and bei discoverable.

- git-checkout this repository
- on the same level in the folder tree, git-checkout the ACU-FW repository
- symlink this repositories `Dockerfile` to the above directory, so the `Dockerfile` is on the same level as `acu` and `acu-fw`
- `docker build . -t acu && docker run -p 7777:7777 acu`