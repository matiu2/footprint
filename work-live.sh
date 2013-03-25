#!/bin/sh
./bin/debug
iwatch -e modify,create,delete -c ./on-file-change.sh -r -x ../build ..
