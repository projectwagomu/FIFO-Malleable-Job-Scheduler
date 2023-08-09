#!/bin/bash

CWD="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
cd ${CWD}
./launchScheduler.sh &
sleep 1
./launchMiddlelayer.sh &
sleep 1
AMTE-evaluation/submit-malleable.sh