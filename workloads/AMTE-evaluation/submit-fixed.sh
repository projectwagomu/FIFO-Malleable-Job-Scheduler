#!/bin/bash

CWD="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

for jobs in `ls -d job*`
do
    echo "Submitting job ${jobs}"
    java -cp ../../build/jar/Scheduler.jar scheduler.Qsub $PWD/$jobs/fixed.sh
done

