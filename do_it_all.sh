#!/bin/csh
uname -a | cat > out.log
more /etc/redhat-release | cat >> out.log
lscpu | cat >> out.log
more /proc/meminfo | cat >> out.log

#use official installation on farm and ifarm
source /group/solid/solid_svn/set_solid 1.3 

#run simulation
#gemc compton_batch.gcard -BEAM_P="gamma,85*MeV,0*deg,0*deg" -SPREAD_P="0*GeV,0*deg,0*deg" -BEAM_V="(0,0,-1)m" -SPREAD_V="(0,0)cm" -N=1e7 | cat >> out.log

root -b -q 'gemcInputGenerator.C(50000000)'
gemc compton_batch.gcard -INPUT_GEN_FILE="LUND,GemcInput.dat" -N=5e7 | cat >> out.log

#convert evio to root
#need more option for banks other than flux
evio2root -INPUTF=out.evio | cat >> out.log

root -b -q 'FileReduce.C+("out.root")'

mv -f out.root_skim out.root

