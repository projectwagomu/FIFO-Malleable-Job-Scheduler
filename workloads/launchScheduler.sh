#!/bin/bash

CWD="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
cd ${CWD}
java -cp ../build/jar/Scheduler.jar scheduler.Scheduler hostfile.txt