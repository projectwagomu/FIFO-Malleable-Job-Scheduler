# Scheduler

This project contains:
- a FIFO malleable **scheduler** as well as some workloads in directory `src`
- external programs, the **middlelayer**, used to communicate with running malleable programs to transmit shrink/grow orders from the scheduler in directory ``shrink_expand`
- some example programs and batches with convenience scripts to submit them in bulk to the scheduler in directory `workloads`

## Project composition

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

The current implementation opens a socket on port 8081 and relays orders coming from the scheduler in the format required by the program.
This is done by running a third-party program for both of the runtimes mentionned above.

The program dealing with CHARM++ was copied from the samples of the CHARM++ repository. 
The program dealing with APGAS for Java program was created by us. 
Both are located in directory `shrink_expand` in a dedicated directory.


## Limitations, Hard-coded environment variables

A number of settings are hard-coded, including the port numbers used by programs to communicate etc.
The most significant ones are:
- the scheduler needs to be run on a host distinct from the ones used as computational host
- a computational host cannot receive more than 1 process at a time

This is due to the sockets used by the scheduler and the middlelayer to communicate between them, and the sockets used by malleable programs use the same port numbers. As a result, they cannot run on the same hosts. Also, the scheduler prepares an hostfile for the programs to use but does not currently handle cases where one hosts handles multiple processes (in MPI, `hostname slots=X` directives).

## Compilation Instructions

The *scheduler* implemented in Java is compiled using `ant` and created a JAR in directory `build/jar`.
The *middlelayer* can be compiled using a Makefile located in the `shrink_expand` directory.

A convenience script [`compile.sh`](compile.sh) is available to compile both the scheduler and the third-party programs used to communicate with malleable jobs.

To compile the programs used in the workloads that can be submitted to the scheduler, refer to the [`workloads/README.md`](`workloads/README.md`).

## Authors

- Patrick Finnerty
- Takuma Kanzaki
- Leo Takaoka
- Jonas Posner

