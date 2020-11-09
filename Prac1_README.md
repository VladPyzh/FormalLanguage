# Practicum 1
This repository contains C++ solution for 1st practical task, MIPT, 3rd semester: \
      One can find algorithm desription in Prac1_Algo.txt 

Quick Start Ubuntu \
      Install boost and openssl, if you don't have them already: \
      $ sudo apt-get install libboost-all-dev \
      $ sudo apt-get install openssl libssl-dev \
      Run script: \
      $ /install_deps.sh python<your python version> \
      Standart Make procedure: \
      $ mkdir build \
      $ cd build \
      $ cmake -DCMAKE_BUILD_TYPE=Debug .. \
      $ sudo make -j<num cores + 1> \
      $ cd .. \
      Main executable code: \
      $ cd bin \
      $ ./Solver \
      $ cd .. \
      Code coverage: \
      $ cd build \
      $ sudo make coverage_report \
      Open an appeared in /build .html file - it will display information related to test coverage