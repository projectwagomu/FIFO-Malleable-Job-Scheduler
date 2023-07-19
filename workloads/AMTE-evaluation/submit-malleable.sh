#!/bin/bash

CWD="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

for jobs in `ls -d job*`
do

    if [ -f $jobs/malleable.sh ]
    then
        echo "Submitting malleable job ${jobs}"
        java -cp ../../build/jar/Scheduler.jar scheduler.Qsub $PWD/$jobs/malleable.sh
    else
        echo "Submitting fixed     job ${jobs}"
        java -cp ../../build/jar/Scheduler.jar scheduler.Qsub $PWD/$jobs/fixed.sh
    fi
done



