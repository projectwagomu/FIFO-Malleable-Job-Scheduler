#!/bin/bash

CWD="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
cd $CWD

echo "Compiling the scheduler core library"
ant jar

echo "Compiling the middlelayer used to transmit orders to running programs"
cd shrink_expand
make