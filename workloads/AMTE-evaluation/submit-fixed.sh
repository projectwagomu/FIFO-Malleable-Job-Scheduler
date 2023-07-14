#!/bin/bash

CWD="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

for jobs in `ls -d job*`
do
    echo "Submitting job ${jobs}"
    java -cp ../build/jar/Scheduler.jar Qsub $PWD/$jobs/fixed.sh 2> /dev/null > /dev/null
done

