#!/bin/bash
#JOB_TYPE apgas
#JOB_CLASS malleable
#MIN_NODES 6
#MAX_NODES 6

# currentDir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

java -cp "/home/patrick/apgas-for-java/lib/*" \
 -Dapgas.places=$NODES\
 -Dapgas.threads=8\
 -Dapgas.immediate.threads=4\
 -Dglb.multiworker.workerperplace=2\
 -Dapgas.elastic=malleable \
 -Dapgas.hostfile=$NODE_FILE\
 -Dmalleable_scheduler_ip=localhost \
 -Dmalleable_scheduler_port=8080 \
 handist.glb.examples.uts.StartMultiworkerUTS -d 15
#  -Dglb.multiworker.lifelinestrategy=glb.multiworker.lifeline.MyHypercubeStrategy\

