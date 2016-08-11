#!/bin/bash

./run data/fold/$1.txt data/sim-out/$1.txt data/sim-in/$1.txt $2 $3 $4 > r/$1$5.pred 2> r/$1$5.tsv
