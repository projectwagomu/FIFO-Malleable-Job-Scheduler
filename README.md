# Scheduler

```shell
scheduler $ ant
middlelayer $ ant
scheduler/examples $ ./submit.sh
```

### examples
`submit.sh`  
```
java Qsub /home/username/scheduler/scheduler/examples/job-dir-1/script.sh
java Qsub /home/username/scheduler/scheduler/examples/job-dir-2/script.sh
```

`script.sh`  
```
#!/bin/bash
#JOB_TYPE mpi
#JOB_CLASS rigid
#MIN_NODES 2
#MAX_NODES 2

cd $SCRIPT_DIR
mpirun -n $NODES --hostfile $NODE_FILE ./main
```

### todo
- refactor
