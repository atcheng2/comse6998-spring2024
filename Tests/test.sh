#!/bin/bash

# for i in {1..5}; do
#     for j in {1..3}; do
#     done
# done

# for i in {1,100}; do
#     make NSTU=$i zdotu
#     ./zdotu >> dse/store.dse
# done

# for i in {1,100}; do
#     make NBRU=$i zdotu
#     ./zdotu >> dse/branch.dse
# done

for i in {1..5}; do
    for j in {1..5}; do
        for k in {1..5}; do
            make NFPU=$i NFXU=$j NLDU=$k zdotu
            ./zdotu >> dse/big-units.dse
        done
    done
done
