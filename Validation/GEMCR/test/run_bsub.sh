#! /bin/sh

RUN=$1
NeventsPerJob=$2
JobId=$3

runFile=runGEMCosmicStand_sim_temp_${RUN}_${JobId}.py

srcDir=/afs/cern.ch/user/j/jslee/gemcrs/src
workDir=$srcDir/Validation/GEMCR/test
resultDir=$workDir/Tree

cd $srcDir
eval `scramv1 runtime -sh`
#eval `scramv1 runtime -csh`
#cmsenv
cd $workDir

#mkdir $resultDir

sed -e 's/"runNum",1,/"runNum",'${RUN}',/' \
    -e 's/"eventsPerJob",10000,/"eventsPerJob",'${NeventsPerJob}',/' \
    -e 's/"idxJob","-1",/"idxJob","'${JobId}'",/' \
    -e 's/out_reco_MC.root/out_reco_MC_'${RUN}'_'${JobId}'.root/' runGEMCosmicStand_sim.py > ${runFile}
    #-e 's/temp_/temp_'${RUN}'_'${JobId}'_/' runGEMCosmicStand_sim.py > runGEMCosmicStand_sim_temp_${RUN}_${JobId}.py

chmod 777 ${runFile}
cmsRun ${runFile}
mv temp_out_reco_MC_${RUN}_${JobId}.root ${resultDir}
rm out_reco_MC_${RUN}_${JobId}.root
rm ${runFile}
