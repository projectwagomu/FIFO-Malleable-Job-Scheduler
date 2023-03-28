#!/bin/bash
#JOB_TYPE apgas
#JOB_CLASS rigid
#MIN_NODES 4
#MAX_NODES 8

currentDir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
cd ${currentDir}/../../../../posner-evolving-glb/bin

java -cp .:${currentDir}/../../../../posner-evolving-glb/lib/\* \
 -Dapgas.places=$NODES\
 -Dapgas.threads=8\
 -Dapgas.immediate.threads=4\
 -Dapgas.verbose.launcher=true\
 -Dapgas.consoleprinter=true\
 -Dapgas.resilient=true\
 -Dapgas.hostfile=$NODE_FILE\
 -Dglb.multiworker.lifelinestrategy=glb.multiworker.lifeline.MyHypercubeStrategy\
 -Dglb.multiworker.workerperplace=2\
 -Dglb.multiworker.benchmarkrepetitions=1\
 -Dglb.multiworker.malleability=true\
 -Dglb.multiworker.malleability.add=true\
 -Dglb.multiworker.n=1\
 -Dglb.multiworker.w=1\
 glb.examples.syntheticBenchmark.StartSynthetic -b 0 -dynamic -g 45000 -t 6000 -u 20
