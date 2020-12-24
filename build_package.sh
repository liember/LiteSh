#!/bin/bash

mkdir -p build
cd build
cmake ..
cmake --build .
cd ..

./build/test/unit_tests

cp build/fctrl/fctrl package/usr/local/bin/fctrl
cp build/liteSH/liteSH package/usr/local/bin/litesh

dpkg-deb --build package/


