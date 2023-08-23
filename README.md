# Malleable Job Scheduler

This project contains:
- a FIFO malleable **scheduler** as well as some workloads in directory `src`
- external programs, the **middlelayer**, used to communicate with running malleable programs to transmit shrink/grow orders from the scheduler in directory ``shrink_expand`
- some example programs and batches with convenience scripts to submit them in bulk to the scheduler in directory `workloads`


## Directories [src](src) and [shrink_expand](shrink_expand)

### Scheduler

This program is responsible for receiving jobs from users and deciding when to launch them / on which hosts.
This program listens on port 8080 to receive job scripts from users (see class `scheduler/ScriptReceiver`).
Programs can be submitted through the `scheduler/Qsub` Java program like so: `java -cp scheduler.jar scheduler/Qsub /home/user/scheduler/examples/job-dir-1/script.sh`.
The requested number of hosts/ limits on minimum-maximum number of hosts for malleablejobs are expected to be written inside the script.
Below is an example of a **rigid** MPI job:

```bash
#!/bin/bash
#JOB_CLASS rigid
#JOB_TYPE mpi
#MIN_NODES 4
#MAX_NODES 4
# Program execution
cd $SCRIPT_DIR
mpirun -n $NODES --hostfile $NODE_FILE a.out
```

When submitting malleable jobs, the `JOB_CLASS` variable must be set as `malleable`. The `JOB_TYPE` is used to indicate to the scheduler how to communicate with the program to send shrink of grow orders. Currently, two values are supported: `apgas` and `charm` based on the programs available in the *middlelayer* and implemented in class [`middlelayer/Main`](src/middlelayer/Main.java).
The minimum and maximum number of processes can be specified using variables `MIN_NODES` and `MAX_NODES`.
The `JOB_TYPE` variable is used to determine

### Middelayer

This middlelayer is used as an intermediary by the scheduler to send shrink/grow messages to running malleable programs.
Currently, there are two types of malleable jobs supported:
- malleable APGAS for Java jobs
- malleable CHARM++ jobs

The current implementation opens a socket on port `8081` and relays orders coming from the scheduler in the format required by the program.
This is done by running a third-party program for both of the runtimes mentionned above.

The program dealing with CHARM++ was copied from the samples of the CHARM++ repository.
The program dealing with APGAS for Java program was created by us.
Both are located in `shrink_expand` in a dedicated directory.

### Compilation instructions

Both the scheduler and the middlelayer can be automatically compiled using the [`compile.sh`](compile.sh) script provided.

A number of settings are hard-coded, including the port numbers used by programs to communicate etc. This incurs some limitations when using this scheduler, the most significant ones are:
- the scheduler needs to be run on a host distinct from the ones used as computational host
- a computational host cannot receive more than 1 process at a time

This is due to the sockets used by the scheduler and the middlelayer to communicate between them, and the sockets used by malleable programs use the same port numbers. As a result, they cannot run on the same hosts. Also, the scheduler prepares a hostfile for the programs to use but does not currently handle cases where hosts handles multiple processes (in MPI, `hostname slots=X` directives).

## Directory [workloads](workloads)
This directory contains:

- two programs compatible with the scheduler
- two job batches, each containing jobs that can be submitted to the job scheduler for execution

### Compiling the programs

#### Directory [job_apgas](workloads/job_apgas)

This directory actually contains multiple programs based on the malleable lifeline-based global load balancer. The necessary sources are downloaded as git submodules and compiled automatically using the [`compile.sh`](workloads/job_apgas/compile.sh) script provided.

More details about the implementation can be found in the following two repositories:
- https://github.com/projectwagomu/apgas
- https://github.com/projectwagomu/lifelineglb

#### Directory [job_mpi](workloads/job_mpi)

This directory contains a dummy MPI program [`main.c`](workloads/job_mpi/main.c) whose execution lasts for 25 seconds.
MPI needs to be installed on the host to be able to compile the program using the provided [`compile.sh`](workloads/job_mpi/compile.sh) convenience script.

### Launching the scheduler

To launch a particular workload, the two scripts [`launchScheduler.sh`](workloads/launchScheduler.sh), and [`launchMiddlelayer.sh`](workloads/launchMiddlelayer.sh) should each be launched in a dedicated terminal on the host used to coordinate the computational hosts of the cluster.

Note that script `launchScheduler` expects to find a file named `hostfile.txt` in which the hosts on which jobs can be scheduled should be listed.
It is assumed all these hosts can be reached through password-less SSH connection.

### Submitting a batch

The batches provided here rely on distributed programs that are provided in the [job_mpi](workloads/job_mpi) and [job_apgas](workloads/job_apgas) directories.
The MPI job includes a basic `main.c` program, while the APGAS program is included as git submodules downloading the contents of repositories [projectwagomu/apgas](https://github.com/projectwagomu/apgas) and [projectwagomu/lifelineglb](https://github.com/projectwagomu/lifelineglb). These programs need to be compiled before they batches provided here can be used successfully (see above).

#### Directory [examples](workloads/examples)

This batch is meant to be launched with a cluster containing 4 computational hosts to demonstrate two malleable changes in allotment.
This batch contains two malleable jobs that can be submitted through the provided script [workloads/examples/submit.sh](workloads/examples/submit.sh).

A gap of 5 seconds separates the submission of the first and the second job.
This makes the scheduler reduce the first job's allotment from the full 4 nodes to allow the second job to start executing.
When either of the programs completes execution, the freed nodes are then allocated to the remaining job until its completion.

#### Directory [AMTE-evaluation](workloads/AMTE-evaluation)

This batch was used as the basis for our evaluation in our article _Malleable APGAS Programs and their Support in Batch Job Schedulers_.
There are two batches present in this directory:
- one containing only fixed jobs that can be submitted using the [submit-fixed.sh](workloads/AMTE-evaluation/submit-fixed.sh) script
- one containing a mix of half fixed, half malleable jobs that can be submitted using the [submit-malleable.sh](workloads/AMTE-evaluation/submit-malleable.sh) script

Both batches contain the same programs with the same computational complexity and can therefore be compared against each other.

## License

This software is released under the terms of the [Eclipse Public License v2.0](LICENSE.txt), though it also uses third-party packages with their own licensing terms.

## Publications

- Patrick Finnerty, Leo Takaoka, Takuma Kanzaki,and Jonas Posner. *Malleable APGAS Programs and their Support in Batch Job Schedulers*. In Euro‐Par Parallel Processing, Asynchronous Many-Task systems for Exascale Workshop (AMTE), 2023. to appear.

## Contributors

In alphabetical order:

 - Patrick Finnerty
 - Takuma Kanzaki
 - Jonas Posner
 - Leo Takaoka
