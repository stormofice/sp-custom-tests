#!/bin/bash
passed=0
failed=0

echo -e "\x1B[36m:=:=: [Custom Test] wsort.c v1.0 :=:=:"
echo -e "https://github.com/stormofice/sp-custom-tests"
echo -e -n "\x1b[0m"

for f in raw/*; do
    echo -n -e "\x1b[33m"
    echo "Testing $f"
    echo -n -e  "\x1b[0m"
    (./wsort < $f) &> local_out
    (./wsort-ref < $f) &> reference_out
    if [[ $(diff -q local_out reference_out) ]]; then
        (( failed++ ))
        echo -e "\x1b[31mFailed $f"
        echo -n -e "\x1b[33m"
        diff local_out reference_out
        echo -n -e  "\x1b[0m"
    else
        (( passed++ ))
        echo -n -e "\x1b[32m"
        echo -e "Passed $f"
        echo -n -e "\x1b[0m"
    fi
done
rm local_out
rm reference_out
echo -n -e "\x1b[33m"
echo -e  "Passed: $passed; Failed: $failed"
echo -n -e  "\x1b[0m"