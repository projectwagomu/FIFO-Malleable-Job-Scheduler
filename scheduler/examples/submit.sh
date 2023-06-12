#!/bin/bash

CWD="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

java Qsub ${CWD}/apgas-malleable-1-2/script.sh
java Qsub ${CWD}/apgas-malleable-2-4/script.sh

