# compton_gemc

setup running env, see here

http://mep.phy.duke.edu/index.php/Computing#jlab_software

#edit compton_geometry.pl to change setup

#create new setup for simulation

./compton.pl config_compton.dat

#run simulation in graphic mode

gemc compton_inter.gcard

#run simulation in batch mode

gemc compton_inter.gcard
and refer to "do_it_all.sh"

#scipt for jlab farm job
do_it_all.sh
exec_sim
LongRun_sim
FileReduce.C

#analysis result

root[0].x analysis.C+("out.root")






