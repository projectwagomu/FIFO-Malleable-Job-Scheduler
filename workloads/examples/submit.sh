#!/bin/bash

CWD="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
cd $CWD

java -cp ../../build/jar/Scheduler.jar scheduler.Qsub ${CWD}/apgas-malleable-2-4/script.sh
sleep 5
java -cp ../../build/jar/Scheduler.jar scheduler.Qsub ${CWD}/apgas-malleable-1-2/script.sh