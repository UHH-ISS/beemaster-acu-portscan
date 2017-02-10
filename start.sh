#!/bin/sh

docker build . -t acu_portscan
docker run --name acu --rm acu_portscan
