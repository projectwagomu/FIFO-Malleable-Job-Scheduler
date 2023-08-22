# Workloads

This directory contains:

- two programs compatible with the scheduler
- two job batches, each containing jobs that can be submitted to the job scheduler for execution

## Compiling the programs

### job_apgas

This directory actually contains multiple programs based on the malleable lifeline-based global load balancer.
The necessary sources are downloaded as git submodules and compiled automatically using the [`compile.sh`](job_apgas/compile.sh) script provided.

More details about the implementation can be found in the following two repositories:
- https://github.com/projectwagomu/apgas
- https://github.com/projectwagomu/lifelineglb

### job_mpi

This directory contains a dummy MPI program [`main.c`](job_mpi/main.c) whose execution lasts for 25 seconds.
MPI needs to be installed on the host to be able to compile the program using the provided [`compile.sh`](job_mpi/compile.sh) convenience script.

## Launching the scheduler

To launch a particular workload, the two scripts [`launchScheduler.sh`](launchScheduler.sh), and [`launchMiddlelayer.sh`](launchMiddlelayer.sh) should each be launched in a dedicated terminal on the host used to coordinate the computational hosts of the cluster.

Note that script `launchScheduler` expects to find a file named `hostfile.txt` in which the hosts on which jobs can be scheduled should be listed.
It is assumed all these hosts can be reached through password-less SSH connection.

## Submitting a batch

The batches provided here rely on distributed programs that are provided in the [job_mpi](job_mpi) and [job_apgas](job_apgas) directories.
The MPI job includes a basic `main.c` program, while the APGAS program is included as git submodules downloading the contents of repositories [projectwagomu/apgas](https://github.com/projectwagomu/apgas) and [projectwagomu/lifelineglb](https://github.com/projectwagomu/lifelineglb). These programs need to be compiled before they batches provided here can be used successfully (see above).

### example

This batch is meant to be launched with a cluster containing 4 computational hosts to demonstrate two malleable changes in allotment.
This batch contains two malleable jobs that can be submitted through the provided script [example/submit.sh](example/submit.sh).

A gap of 5 seconds separates the submission of the first and the second job.
This makes the scheduler reduce the first job's allotment from the full 4 nodes to allow the second job to start executing.
When either of the programs completes execution, the freed nodes are then allocated to the remaining job until its completion.

### AMTE-evaluation

This batch was used as the basis for our evaluation in our article _Malleable APGAS Programs and their Support in Batch Job Schedulers_.
There are two batches present in this directory:
- one containing only fixed jobs that can be submitted using the [submit-fixed.sh](AMTE-evaluation/submit-fixed.sh) script
- one containing a mix of half fixed, half malleable jobs that can be submitted using the [submit-malleable.sh](AMTE-evaluation/submit-malleable.sh) script

Both batches contain the same programs with the same computational complexity and can therefore be compared against each other.
