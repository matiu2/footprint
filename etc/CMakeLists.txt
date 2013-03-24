project(etc)

set(DEBUG_JS true CACHE STRING "true, stack, false: 'true' for debug; 'stack' for problem solving in prod; 'false' for not sharing info with client")
set(LOG_FILE footprint.log CACHE STRING "Where to log errors; empty = stderr")
set(LOG_LEVELS "*" CACHE STRING "eg. '* -debug' (log all, except debug) -- '* -debug my_feature:debug' only log debug for my_feature")
set(MAX_UPLOAD 524288 CACHE STRING "max size of a post request in KB")

configure_file(footprint_cfg.xml.in footprint_cfg.xml)
