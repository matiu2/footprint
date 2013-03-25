#!/bin/sh
killall footprint
cmake .. && make -j4 && ./bin/debug &
