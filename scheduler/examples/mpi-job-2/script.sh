#!/bin/bash
#JOB_TYPE mpi
#JOB_CLASS rigid
#MIN_NODES 1
#MAX_NODES 3

sleep 10
cd $SCRIPT_DIR
mpirun -n $NODES --hostfile $NODE_FILE ./main
