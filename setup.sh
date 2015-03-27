#!/bin/sh

#setup VICI_HOME var
cwd=$(pwd)

#string
export_string="export VICI_HOME=$cwd"

#add to bash profile
touch /.bash_profile

echo $export_string >> ~/.bash_profile
cat ~/.bash_profile
