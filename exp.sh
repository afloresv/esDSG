#!/bin/bash

./run.sh nr -1 0.1832 0.3684 80
./run.sh nr -1 0.2311 0.4722 90
./run.sh nr -1 0.2758 0.5536 95
./run.sh nr -1 0.5448 0.6873 98

./run.sh gpcr -1 0.1416 0.2955 80
./run.sh gpcr -1 0.1912 0.3514 90
./run.sh gpcr -1 0.2295 0.4000 95
./run.sh gpcr -1 0.3242 0.4737 98

./run.sh ic -1 0.0227 0.2826 80
./run.sh ic -1 0.0338 0.3429 90
./run.sh ic -1 0.1355 0.3929 95
./run.sh ic -1 0.3134 0.4667 98

./run.sh e -1 0.0222 0.2500 80
./run.sh e -1 0.0269 0.3023 90
./run.sh e -1 0.0356 0.3462 95
./run.sh e -1 0.0888 0.4048 98