#!/bin/bash
#JOB_TYPE apgas
#JOB_CLASS malleable
#MIN_NODES 2
#MAX_NODES 12

# currentDir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

java -cp "/home/patrick/apgas-for-java/lib/*" \
 -Dapgas.places=$NODES\
 -Dapgas.threads=8\
 -Dapgas.immediate.threads=4\
 -Dglb.multiworker.workerperplace=2\
 -Dapgas.elastic=malleable \
 -Dapgas.hostfile=$NODE_FILE\
 -Dglb.multiworker.lifelinestrategy=glb.multiworker.lifeline.MyHypercubeStrategy\
 handist.glb.examples.nqueens.StartNQueens -n 15 -t 11
