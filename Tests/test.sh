#!/bin/bash

for i in {1..8}; do
    export OMP_NUM_THREADS=$i
    make dgemv_td

    echo "Test $i" >> results.txt
    ./dgemv_td >> results.txt 2>>efficiency.txt
    echo >> results.txt
done
