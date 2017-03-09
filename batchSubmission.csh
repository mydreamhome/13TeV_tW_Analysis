export X509_USER_PROXY=/afs/cern.ch/work/p/ppriyank/public/x509up_u80952
n=$1
s=1
id=1

while [ $s -le $n ]
do
	e=`expr $s + $2 - 1 `

	if [ $e -gt $n ]
	then
		e=$n
	fi

		echo "#!/bin/csh" > job$id.csh
		echo "cd /afs/cern.ch/work/p/ppriyank/private/816all/tW/CMSSW_8_0_16/src" >> job$id.csh 
		echo "eval \`scramv1 runtime -csh\`" >> job$id.csh
		echo "PatMuonEDMAnalyzer $id $s $e" >> job$id.csh

		bsub -q 1nd < job$id.csh
		echo "bsub -q 1nd < job$id.csh"
	s=`expr $e + 1`
	id=`expr $id + 1`
done
