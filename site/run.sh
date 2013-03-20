#!/bin/sh
./footprint --docroot=".;/images,/resources" --http-address=127.0.0.1 --http-port=8080 --approot=. -c wt_config.xml

