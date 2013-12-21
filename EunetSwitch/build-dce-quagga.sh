#!/bin/sh
hg clone http://code.nsnam.org/bake bake
export BAKE_HOME=`pwd`/bake
export PATH=$PATH:$BAKE_HOME
export PYTHONPATH=$PYTHONPATH:$BAKE_HOME
mkdir dce
cd dce
bake.py configure -e dce-ns3-dev -e dce-quagga-dev
bake.py download
bake.py build

