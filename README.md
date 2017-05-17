# compton_gemc

setup running env, see here

http://mep.phy.duke.edu/index.php/Computing#jlab_software

#edit compton_geometry.pl to change setup

#create new setup for simulation

./compton.pl config_compton.dat

#run simulation in graphic mode

gemc compton_inter.gcard

#analysis result

root[0].x analysis.C+("out.root")






