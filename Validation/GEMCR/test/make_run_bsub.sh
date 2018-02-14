#! /bin/sh

NeventsPerJob=10000
NJob=100
#NeventsPerJob=$1
#NJob=$2

#for RUN in 1 2 3 4 5
for RUN in 1
do
  JobId=0
  while [ $JobId -lt $NJob ]
  do
    echo run$RUN jobid$JobId
    cp run_bsub.sh run_bsub_${RUN}_${JobId}.sh

    #For batch job
    #bsub -q 1nd -J ${RUN}_${JobId} < run_bsub.sh ${RUN} ${NeventsPerJob} ${JobId}
    #bsub -q 1nd -J ${RUN}_${JobId} < run_bsub_${RUN}_${JobId}.sh ${RUN} ${NeventsPerJob} ${JobId}

    #For local job
    ./run_bsub.sh ${RUN} ${NeventsPerJob} ${JobId}

    sleep 1
    rm run_bsub_${RUN}_${JobId}.sh
    JobId=`expr $JobId + 1`
  done
done
