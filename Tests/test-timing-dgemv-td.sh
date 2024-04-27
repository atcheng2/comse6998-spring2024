#!/bin/bash

# Varying CPU tests
for i in {1,2,3,4}; do
    export OMP_NUM_THREADS=$i
    rm dgemv_td
    rm runomp
    NO_TIMING=1 make dgemv_td
    /bin/time -f "%e" -a -o "timing/dgemv-td-no-timing-cores" ./dgemv_td 32 32 32 1 1
    make dgemv_td
    make runomp
    /bin/time -f "%e" -a -o "timing/dgemv-td-timing-cores" ./dgemv_td 32 32 32 1 1
    /bin/time -f "%e" -a -o "timing/dgemv-td-pipe-cores" ./runomp dgemv_td
done

# 2 CPUs for most testing (default)
export OMP_NUM_THREADS=2
NO_TIMING=1 make dgemv_td
for i in {1,2,4,8,16,32,64,128,256}; do
    /bin/time -f "%e" -a -o "timing/dgemv-td-no-timing" ./dgemv_td $i $i $i 1 1
done

rm dgemv_td
make dgemv_td
make runomp

for i in {1,2,4,8,16,32,64,128,256}; do
    /bin/time -f "%e" -a -o "timing/dgemv-td-timing" ./dgemv_td $i $i $i 1 1
    /bin/time -f "%e" -a -o "timing/dgemv-td-pipe" ./runomp dgemv_td
done


