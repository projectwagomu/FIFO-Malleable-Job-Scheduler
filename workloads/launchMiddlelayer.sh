#!/bin/bash

CWD="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

cd ${CWD}/..
pwd
java -cp build/jar/Scheduler.jar middlelayer.Main
