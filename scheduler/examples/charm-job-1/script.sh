#!/bin/bash
#JOB_TYPE charm
#JOB_CLASS rigid
#MIN_NODES 2
#MAX_NODES 2

cd $SCRIPT_DIR
./charmrun +p$NODES ++nodelist $NODE_FILE ./hello
