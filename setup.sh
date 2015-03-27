#!/bin/sh

#setup VICI_HOME var
cwd=$(pwd)

#string
export_string="export VICI_HOME=$cwd"
export_tools_string="export VICI_TOOLS=$cwd/tools/scripts"

#add to bash profile
touch /.bash_profile

echo $export_string >> ~/.bash_profile
echo $export_tools_string >> ~/.bash_profile
cat ~/.bash_profile
