#! /bin/sh

NC='\E[m'
RedB='\E[41m'
BlueB='\E[44m'
PurpleB='\E[45m'
White='\E[37m'

# Init stuff
sDir=${PWD}

# DEPENDENCIES
# Git
echo ''
echo "${RedB} ${White} installing git ${BlueB}"
echo 'Y' | pkgin install scmgit-base

# GCC
echo ''
echo "${RedB} ${White} installing gcc ${BlueB}"
echo 'Y' | pkgin install gcc47-4.7.2nb3
echo 'Y' | pkgin install gcc47-4.7.2
echo 'Y' | pkgin install gmake

# Set up dependency tree
echo ''
echo "${RedB} ${White} setting up /opt/tools/ for downloads... ${BlueB}"
echo "cd /"
cd /
echo "mkdir -p opt"
mkdir -p opt
echo "cd opt"
cd opt
echo "mkdir -p tools"
mkdir -p tools
echo "cd tools"
cd tools

# Download source
echo "${PurpleB}"
git clone https://github.com/luceracloud/dtrace.git
echo "${NC}"

# ZMQ
cd /opt/tools
echo ''
echo "${RedB} ${White} installing zmq ${BlueB}"
curl -klO http://download.zeromq.org/zeromq-2.2.0.tar.gz
tar zxf zeromq-2.2.0.tar.gz
cd zeromq-2.2.0
./configure --prefix /opt/local
make
make install

# Protocol Buffers
cd /opt/tools
echo ''
echo "${RedB} ${White} installing protocol buffers ${BlueB}"
curl -klO https://protobuf.googlecode.com/files/protobuf-2.5.0.tar.gz
tar zxvf protobuf-2.5.0.tar.gz
cd protobuf-2.5.0
./configure --prefix /opt/local
make
make install

# build server
cd /opt/tools/dtrace/server
make rel

# Set everything to normal again
cd ${sDir}
echo "${NC}"
