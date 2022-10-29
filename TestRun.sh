#!/usr/bin/env bash
echo "" > report
for f in test*; 
do 
    ./cmake-build-debug/P1_2048 < $f > "real_$f"
    echo $f
    diff -s "des_$f" "real_$f" >> report 2 >> report
done

cat report

 
