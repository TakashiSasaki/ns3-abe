#!/bin/sh
if [ -e bake ]; then
  hg pull bake
else
  hg clone http://code.nsnam.org/bake bake
fi
export BAKE_HOME=`pwd`/bake
export PATH=$PATH:$BAKE_HOME
export PYTHONPATH=$PYTHONPATH:$BAKE_HOME
mkdir dce
cd dce
#bake.py distclean
#bake.py check  --all
bake.py configure -vvv -e dce-ns3-dev -e dce-quagga-dev -e gccxml-ns3 -e pygccxml
#(cd dce/source/ns-3-dev-dce/; ./waf distclean)
#bake.py configure -vvv -e dce-ns3-dev -e dce-quagga-dev -e gccxml-ns3 -e pygccxml
bake.py check -v
bake.py download -vvv
bake.py build -vvv 

