#!/bin/bash

cd ~/PScourse1/bin
echo loop 10
./caldensity  -r 0.8 -m 0.06 -k 0.2 -a 0.04 -b 0.02 -dt 0.4 -l 0.2 -loops 10 -interval 10 -show 0 -mapfile $HOME/PScourse1/cfg/map.dat -ppmfolder  $HOME/PScourse1/ppm_output >> ~/PS_coursework/cf_testing/loop_results
echo loop 100
./caldensity  -r 0.8 -m 0.06 -k 0.2 -a 0.04 -b 0.02 -dt 0.4 -l 0.2 -loops 100 -interval 100 -show 0 -mapfile $HOME/PScourse1/cfg/map.dat -ppmfolder  $HOME/PScourse1/ppm_output >> ~/PS_coursework/cf_testing/loop_results
echo loop 1000
./caldensity  -r 0.8 -m 0.06 -k 0.2 -a 0.04 -b 0.02 -dt 0.4 -l 0.2 -loops 1000 -interval 1000 -show 0 -mapfile $HOME/PScourse1/cfg/map.dat -ppmfolder  $HOME/PScourse1/ppm_output >> ~/PS_coursework/cf_testing/loop_results
echo loop 10000
./caldensity  -r 0.8 -m 0.06 -k 0.2 -a 0.04 -b 0.02 -dt 0.4 -l 0.2 -loops 10000 -interval 10000 -show 0 -mapfile $HOME/PScourse1/cfg/map.dat -ppmfolder  $HOME/PScourse1/ppm_output >> ~/PS_coursework/cf_testing/loop_results
