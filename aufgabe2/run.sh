#!/bin/bash
passed=0
failed=0

if [ ! -f wsort ]; then
    echo "Couldn't find your binary wsort implementation, trying to locate source file"
    if [ ! -f wsort.c ]; then
        echo "Couldn't locate source file"
        exit
    else
        gcc -std=c11 -pedantic -Wall -Werror -D_XOPEN_SOURCE=700 -o wsort wsort.c
    fi
fi
if [ ! -f wsort-ref ]; then
    echo "Couldn't find wsort-ref, please rename the reference implementation"
    exit
fi

echo -e "\x1B[36m:=:=: [Custom Test] wsort.c v1.1 :=:=:"
echo -e "https://github.com/stormofice/sp-custom-tests"

echo -n -e "\x1b[33m"
if [ -d "raw/" ]; then
    echo "Found raw list directory"
else
    echo "Downloading raw word lists, this may take a while"
    mkdir raw
    cd raw
    wget https://raw.githubusercontent.com/stormofice/sp-custom-tests/main/aufgabe2/raw/10_ascii_way_too_long -q --show-progress
    wget https://raw.githubusercontent.com/stormofice/sp-custom-tests/main/aufgabe2/raw/16k_ascii_mixed -q --show-progress
    wget https://raw.githubusercontent.com/stormofice/sp-custom-tests/main/aufgabe2/raw/16k_ascii_too_long -q --show-progress
    wget https://raw.githubusercontent.com/stormofice/sp-custom-tests/main/aufgabe2/raw/16k_ascii_valid -q --show-progress
    wget https://raw.githubusercontent.com/stormofice/sp-custom-tests/main/aufgabe2/raw/length_check -q --show-progress
    cd ..
fi

# v1.0 upgrade
if [ "raw/null_byte_city" ]; then
    cd raw
    echo "Downloading new words lists"
    wget https://raw.githubusercontent.com/stormofice/sp-custom-tests/main/aufgabe2/raw/16k_unicode_sanitized-q --show-progress
    cd ..
fi;

echo -n -e  "\x1b[0m"

for f in raw/*; do
    echo -n -e "\x1b[33m"
    echo "Testing $f"
    echo -n -e  "\x1b[0m"
    ts=$(date +%s%N)
	(./wsort < $f) &> local_out
    
    tt=$((($(date +%s%N) - $ts) / 1000000))
	echo -e "\x1B[36m$f local solution took: $tt ms"
    ts=$(date +%s%N)
    (./wsort-ref < $f) &> reference_out
    tt=$((($(date +%s%N) - $ts) / 1000000))
    echo -e "\x1B[36m$f reference solution took: $tt ms"
    if [[ $(diff -q local_out reference_out) ]]; then
        (( failed++ ))
        echo -n -e "\x1b[33m"
        echo -e "\x1b[31mFailed $f"
        echo "You can continue (y), abort (n) or show diff (d) (y/n/d)"
        echo -n -e  "\x1b[0m"
        read -n1
        echo ""
        if [[ "n" = "$REPLY" ]]; then
            exit
        elif [[ "d" = "$REPLY" ]]; then
           diff local_out reference_out
           exit
        fi
        
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
