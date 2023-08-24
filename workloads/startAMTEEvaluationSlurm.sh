#!/bin/bash
####### Mail Notify / Job Name / Comment #######
#SBATCH --mail-type=NONE
#SBATCH --job-name=AMTEEvaluation

####### Constraints #######
#SBATCH --time=0-00:30:00
#SBATCH --partition=general2
#SBATCH --exclusive

####### Node Info #######
#SBATCH --nodes=13
#SBATCH --distribution=cyclic

####### Output #######
#SBATCH --output=/home/apgas/posner/out/AMTEEvaluation.out.%j
#SBATCH --error=/home/apgas/posner/out/AMTEEvaluation.err.%j

####### Script #######
#scontrol show config
#scontrol show jobid -dd ${SLURM_JOB_ID}

thishost=$(hostname | cut -d. -f1)
allhosts=$(scontrol show hostnames)
tobeadded=$(echo "$allhosts" | grep -v "$thishost")

#echo "thishost: $thishost"
#echo "allhosts: $allhosts"
#echo "tobeadded: $tobeadded"

echo "$tobeadded" > ${HOME}/scheduler/workloads/hostfile.txt

${HOME}/scheduler/workloads/launchMiddlelayer.sh &
middlepid=$!
sleep 1
${HOME}/scheduler/workloads/launchScheduler.sh &
schedulerpid=$!
sleep 1
${HOME}/scheduler/workloads/AMTE-evaluation/submit-malleable.sh
wait $schedulerpid
kill -9 $middlepid
echo "slurm done"
#TODO scheduler_log should be unique per run, e.g., by containing the job id