#!/bin/bash
# Compiling the malleable APGAS library and the lifeline-based global load balancer
CWD="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
cd $CWD
cd ../../
git submodule init
git submodule update

cd $CWD/apgas
git checkout v0.0.1
mvn install -DskipTests

cd $CWD/lifelineglb
git checkout 0.0.1
mvn package