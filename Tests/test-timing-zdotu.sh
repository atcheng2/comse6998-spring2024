#!/bin/bash

NO_TIMING=1 make zdotu
for i in {1,2,4,8,16,32,64,128,256,512,1024,2048}; do
    /bin/time -f "%e" -a -o "timing/zdotu-no-timing" ./zdotu $i 1 1
done

rm zdotu
make zdotu
make run

for i in {1,2,4,8,16,32,64,128,256,512,1024,2048}; do
    /bin/time -f "%e" -a -o "timing/zdotu-timing" ./zdotu $i 1 1
    /bin/time -f "%e" -a -o "timing/zdotu-pipe" ./run zdotu
done

