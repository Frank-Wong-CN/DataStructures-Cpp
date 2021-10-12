#!/bin/bash

if [[ ! -e "Build" ]]; then
	mkdir Build
fi

cd Build
cmake ..
make
cd ..

