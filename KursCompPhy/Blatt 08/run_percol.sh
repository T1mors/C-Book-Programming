#!/bin/bash
for L in 10 20 50 100 200 300 500; do
    # Empty file
    >$"perc$L.dat"
    for p in 0.1 0.2 0.3 0.4 0.45 0.5 0.52 0.54 0.56 0.57 0.58 0.59 \
        0.60 0.61 0.62 0.64 0.66 0.68 0.7 0.8 0.9 1.0; do
        ./percol $L $p 100 >>$"perc$L.dat"
    done
    echo $"perc$L.dat"
done
