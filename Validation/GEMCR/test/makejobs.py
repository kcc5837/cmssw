#import sys, opt
import sys, os


strJobNum = sys.argv[ 1 ]
strJobName = "res_" + strJobNum

#strNumJob = "500" if len(sys.argv) < 3 else sys.argv[ 2 ]
strNumJob = "250"
strEvtNum = "40000"

if not os.path.isdir(strJobName): 
  os.mkdir(strJobName)
  open(strJobName + "/.create-batch", "w").write("")

open("run.sh", "w").write(open("run_template.sh", "r").read()%{"runnumber": strJobNum, "samplesize": strEvtNum})
open("submit.jds", "w").write(open("submit_template.jds", "r").read()%{"jobname": strJobName, "jobnum": strNumJob})

os.system("./full_archive.sh gemcr ; echo '@@ Archiving is complete' ; condor_submit submit.jds"%{"runnumber": strJobNum})


