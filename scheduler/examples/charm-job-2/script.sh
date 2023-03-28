#!/bin/bash
#JOB_TYPE charm
#JOB_CLASS malleable
#MIN_NODES 3
#MAX_NODES 5

cd $SCRIPT_DIR
./charmrun +p$NODES ./jacobi2d 200 20 5000 +balancer GreedyLB ++nodelist $NODE_FILE +shrinkexpand_basedir /home/takaoka/workdir ++server ++server-port 1234
