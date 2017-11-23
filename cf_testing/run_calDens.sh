#!/bin/bash

cd ~/PScourse1/bin
echo Running
./caldensity  -r 0.8 -m 0.06 -k 0.2 -a 0.04 -b 0.02 -dt 0.4 -l 0.2 -loops 1000 -interval 1000 -show 0 -mapfile $HOME/PScourse1/cfg/map.dat -ppmfolder  $HOME/PScourse1/ppm_output
echo Finished
echo Running gprof and outputting to text file
gprof caldensity >> /mnt/c/Users/con-4/Documents/Uni/CMF/Programming\ Skills/Project/PS_coursework/cf_testing/gprof_results1.txt
