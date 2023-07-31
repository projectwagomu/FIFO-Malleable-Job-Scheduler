#!/bin/bash
#JOB_TYPE apgas
#JOB_CLASS malleable
#MIN_NODES 1
#MAX_NODES 2

cd ${SCRIPT_DIR}

pwd

java -cp "../../job_apgas/lifelineglb/target/*" \
 -Dapgas.places=$NODES\
 -Dapgas.threads=8\
 -Dapgas.immediate.threads=4\
 -Dapgas.verbose.launcher=true\
 -Dapgas.consoleprinter=true\
 -Dapgas.resilient=true\
 -Dapgas.hostfile=$NODE_FILE\
 -Dglb.multiworker.lifelinestrategy=handist.glb.multiworker.lifeline.ConfigurableHypercubeStrategy\
 -Dglb.multiworker.workerperplace=2\
 -Dglb.multiworker.benchmarkrepetitions=1\
 -Dglb.multiworker.n=1\
 -Dglb.multiworker.w=1\
 -Dapgas.elastic=malleable \
 -Dmalleable_scheduler_ip=localhost \
 -Dmalleable_scheduler_port=8080 \
 handist.glb.examples.syntheticBenchmark.StartSynthetic -b 0 -dynamic -g 45000 -t 6000 -u 20 2> error.txt
