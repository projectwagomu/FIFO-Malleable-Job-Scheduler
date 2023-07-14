# Workloads

This directory contains a few workoads, each containing individual jobs that can be submitted to the job scheduler for execution.

To launch a particular workload, the two scripts [`launchScheduler.sh`](launchScheduler.sh), and [`launchMiddlelayer.sh`](launchMiddlelayer.sh) should be launched in a dedicated terminal.
Note that script `launchScheduler` expects to find a file named `hostfile.txt` in which the hosts on which jobs can be scheduled should be listed.
It is assumed all these hosts can be reached through password-less SSH connection.

## example batch

This batch contains two simple jobs that can be submitted through the provided script [example/submit.sh](example/submit.sh).

## AMTE-evaluation batch

This batch was used as the basis for our evaluation in our article _Malleable APGAS Programs and their Support in Batch Job Schedulers_.
There are two batches present in this directory:
- one containing only fixed jobs that can be submitted using the [AMTE-evaluation/submit-fixed.sh](AMTE-evaluation/submit-fixed.sh) script
- one containing a mix of half fixed, half malleable jobs that can be submitted using the [AMTE-evaluation/submit-malleable.sh](AMTE-evaluation/submit-malleable.sh) script

