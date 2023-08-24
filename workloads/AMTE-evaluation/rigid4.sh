#!/bin/bash
#JOB_TYPE mpi
#JOB_CLASS rigid
#MIN_NODES 4
#MAX_NODES 4


cd ${SCRIPT_DIR}
mpirun -n $NODES --hostfile $NODE_FILE ../../job_mpi/a.out

