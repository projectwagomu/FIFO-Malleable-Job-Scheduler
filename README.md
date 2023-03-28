# Scheduler

This project contains the source files to buils a FIFO malleable scheduler. 
The scheduler accepts job scripts in a format similar to actual batch job schedulers.

## Project composition

There are 2 components present in this project:
### 1. The "scheduler"

This program is responsible for receiving jobs from users and deciding when to launch them / on which hosts.
This program listens on port 8080 to receive job scripts from users (see class `scheduler/ScriptReceiver`). 
Programs can be submitted through the `Qsub` Java program like so: `java Qsub /home/user/scheduler/examples/job-dir-1/script.sh`. 
The requested number of hosts/ limits on minimum-maximum number of hosts for malleablejobs are expected to be written inside the script.
Below is an example of a **rigid** APGAS job:
  
```bash
#!/bin/bash
#JOB_TYPE apgas
#JOB_CLASS rigid
#MIN_NODES 4
#MAX_NODES 6

currentDir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
cd ${currentDir}/../../../../posner-evolving-glb/bin

java -cp .:${currentDir}/../../../../posner-evolving-glb/lib/\* \
 -Dapgas.places=$NODES\
 -Dapgas.threads=8\
 <...>
 -Dglb.multiworker.w=1\
 glb.examples.syntheticBenchmark.StartSynthetic -b 0 -dynamic -g 45000 -t 6000 -u 20
```
  
Below is an example of a malleable Charm++ job:
  
```bash
#!/bin/bash
#JOB_TYPE charm
#JOB_CLASS malleable
#MIN_NODES 3
#MAX_NODES 5

cd $SCRIPT_DIR
./charmrun +p$NODES ./jacobi2d 200 20 5000 +balancer GreedyLB ++nodelist $NODE_FILE +shrinkexpand_basedir /home/takaoka/workdir ++server ++server-port 1234
```

### 2. the "middelayer**

This middlelayer is used as an intermediary by the scheduler to send shrink/grow messages to running malleable programs. 
Currently, there are two types of malleable jobs supported:
- malleable APGAS for Java jobs
- malleable CHARM++ jobs

The current implementation opens a socket on port 8081 and relays orders coming from the scheduler in the format required by the program.
This is done by running a third-party program for both of the runtimes mentionned above.

These programs were copied from the CHARM++ samples in the case of CHARM++, or created by Kanzaki in the case of APGAS and are located in directory `middlelayer/shrink_expand` in a dedicated directory for each of them.


## Limitations, Hard-coded environment variables

A number of settings are hard-coded, including the port numbers used by programs to communicate etc.
The most significant one are:

1. the hosts that the scheduler operates on (see [`ScriptManager#L15`](https://gittk.cs.kobe-u.ac.jp/elastic/scheduler/-/blob/master/scheduler/src/scheduler/ScriptManager.java#L15))
2. the path to the external programs the middlelayer relies on (see [`middlelayer/Main.java` l35](https://gittk.cs.kobe-u.ac.jp/elastic/scheduler/-/blob/master/middlelayer/src/middlelayer/Main.java#L35), [line ](https://gittk.cs.kobe-u.ac.jp/elastic/scheduler/-/blob/master/middlelayer/src/middlelayer/Main.java#L55), [line 70](https://gittk.cs.kobe-u.ac.jp/elastic/scheduler/-/blob/master/middlelayer/src/middlelayer/Main.java#L70), and [line 102](https://gittk.cs.kobe-u.ac.jp/elastic/scheduler/-/blob/master/middlelayer/src/middlelayer/Main.java#L102))



## Compilation Instructions

```bash
$ cd middlelayer
$ ant jar
$ cd shrink_expand
$ cd apgas
$ javac Client.java
$ cd ../charm
$ make                 # Requires Charm++ to be compiled and installed with elastic options on the system
$ cd ../../../scheduler
$ ant clean-build
```

## Experiment setup

### External dependencies

#### 1) Malleable APGAS for Java with GLB

This program 

```bash

```

## Running the test



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
