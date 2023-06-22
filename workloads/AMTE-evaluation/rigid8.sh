#!/bin/bash
#JOB_TYPE mpi
#JOB_CLASS rigid
#MIN_NODES 8
#MAX_NODES 8

#cd $SCRIPT_DIR
mpirun -n $NODES --hostfile $NODE_FILE /home/patrick/scheduler/scheduler/AMTE-evaluation/main

