#!/bin/bash
#JOB_TYPE mpi
#JOB_CLASS rigid
#MIN_NODES 2
#MAX_NODES 2


cd ${SCRIPT_DIR}
mpirun -n $NODES --hostfile $NODE_FILE ../../job_mpi/a.out

