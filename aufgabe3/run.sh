#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
RESET='\033[0m'
CYAN='\x1B[36m'
YELLOW='\033[0;33m'  

echo -e "$CYAN:=:=: [Custom Test] halde.c v1.0 :=:=:"
echo -e "https://github.com/stormofice/sp-custom-tests"
echo "If you encounter a bug and don't know why, check out the according file in .tests/"

resetTest() {
    echo -n "#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include \"replace\"

int main(int argc, char const* argv[]) {
    test();
}
" > custom_test.c
}

resetTest


echo -e -n $RED
if [ ! -f halde-ref.o ]; then
    echo "Couldn't find halde-ref.o, please provide the reference file"
    exit
fi
if [ ! -f halde.h ]; then
    echo "Couldn't find halde.h, please provide the reference header"
    exit
fi
if [ ! -f halde.c ]; then
    echo "Couldn't find halde.c, please provide your local solution"
    exit
fi

echo -e -n $RESET

echo -e -n $YELLOW

if [ ! -d ".tests/" ]; then
    mkdir .tests
    echo "Downloading tests"
    cd .tests
    wget https://raw.githubusercontent.com/stormofice/sp-custom-tests/main/aufgabe3/.tests/test_calloc_multiplication_overflow.c -q --show-progress
    wget https://raw.githubusercontent.com/stormofice/sp-custom-tests/main/aufgabe3/.tests/test_calloc_reset.c -q --show-progress
    wget https://raw.githubusercontent.com/stormofice/sp-custom-tests/main/aufgabe3/.tests/test_calloc_calloc_simple.c -q --show-progress
    wget https://raw.githubusercontent.com/stormofice/sp-custom-tests/main/aufgabe3/.tests/test_free_null.c -q --show-progress
    wget https://raw.githubusercontent.com/stormofice/sp-custom-tests/main/aufgabe3/.tests/test_free_reset_memory.c -q --show-progress
    wget https://raw.githubusercontent.com/stormofice/sp-custom-tests/main/aufgabe3/.tests/test_malloc_big_fill.c -q --show-progress
    wget https://raw.githubusercontent.com/stormofice/sp-custom-tests/main/aufgabe3/.tests/test_malloc_memory_clear.c -q --show-progress
    wget https://raw.githubusercontent.com/stormofice/sp-custom-tests/main/aufgabe3/.tests/test_malloc_one_big_block.c -q --show-progress
    wget https://raw.githubusercontent.com/stormofice/sp-custom-tests/main/aufgabe3/.tests/test_malloc_repeated_free.c -q --show-progress
    wget https://raw.githubusercontent.com/stormofice/sp-custom-tests/main/aufgabe3/.tests/test_malloc_simple.c -q --show-progress
    wget https://raw.githubusercontent.com/stormofice/sp-custom-tests/main/aufgabe3/.tests/test_malloc_small_fill_overflow.c -q --show-progress
    wget https://raw.githubusercontent.com/stormofice/sp-custom-tests/main/aufgabe3/.tests/test_malloc_small_fill.c -q --show-progress
    wget https://raw.githubusercontent.com/stormofice/sp-custom-tests/main/aufgabe3/.tests/test_realloc_simple.c -q --show-progress
    wget https://raw.githubusercontent.com/stormofice/sp-custom-tests/main/aufgabe3/.tests/z_test_full_random.c -q --show-progress
    cd ..
fi

if [[ "$(md5sum < .tests/test_calloc_reset.c)" != "c9b76becebf0f41e7b3d731d0921b21b  -" ]]; then
    echo "Force redownload of new test"
    cd .tests
    rm test_calloc_reset.c
    wget https://raw.githubusercontent.com/stormofice/sp-custom-tests/main/aufgabe3/.tests/test_calloc_reset.c -q --show-progress
    cd ..
fi
echo -e -n $RESET

count=0
maxcount=0

for f in .tests/*; do

    if [[ "$f" == *".h"* ]]; then
        continue
    fi
    
    echo -e -n $YELLOW
    echo "Testing $f"
    sed "s+replace+$f+g" custom_test.c > test_temp.c
    mv test_temp.c custom_test.c
    
    if [[ "$f" == *"random"* ]]; then
        echo "Initiating random test and running it 128 times [or until failure]"
        
        sed "s+test();+test(atoi(argv[1]));+g" custom_test.c > test_temp.c
        mv test_temp.c cusstom_test.c
        
        gcc -std=c11 -pedantic -Wall -Werror -D_XOPEN_SOURCE=700 -o test halde.h halde.c custom_test.c
        gcc -std=c11 -pedantic -Wall -Werror -D_XOPEN_SOURCE=700 -o test-ref halde-ref.o custom_test.c
    
        max=127

        for x in $(eval echo {0..$max} )
        do
            seed=$(shuf -i 1-2147483648 -n 1)
            $(./test-ref $seed &> reference_out) 
            $(./custom_test $seed &> local_out)
        
            if [[ $(diff -q local_out reference_out) ]]; then
                echo -e "$seed : $RED[FAIL]"
                echo -n -e $RESET
                diff local_out reference_out
                exit
            fi
        
        done
        
        (( count++ ))
        (( maxcount++ ))
        
        continue
    
    fi
    
    gcc -std=c11 -pedantic -Wall -Werror -D_XOPEN_SOURCE=700 -o test halde.h halde.c custom_test.c
    gcc -std=c11 -pedantic -Wall -Werror -D_XOPEN_SOURCE=700 -o test-ref halde-ref.o custom_test.c
    
    echo -e -n $CYAN  
    ts=$(date +%s%N)
    ./custom_test &> local_out
    tt=$((($(date +%s%N) - $ts) / 1000000))
    sed 's/\x0//g' local_out > local_temp_out
    mv local_temp_out local_out
    echo -e "\x1B[36m$f local solution took: $tt ms"
    ts=$(date +%s%N)
    ./test-ref &> reference_out
    tt=$((($(date +%s%N) - $ts) / 1000000))
    sed 's/\x0//g' reference_out > reference_temp_out
    mv reference_temp_out reference_out
    
    echo -e "\x1B[36m$f reference solution took: $tt ms"
    (( maxcount++ ))
    if [[ $(diff -q local_out reference_out) ]]; then
        echo -e "${RED}Test failed"
        echo -n -e "${RESET}"
        
        echo "You can continue (y), abort (n) or show diff (d) (y/n/d)"
        echo -n -e  $RESET
        read -n1
        echo ""
        if [[ "n" = "$REPLY" ]]; then
            exit
        elif [[ "d" = "$REPLY" ]]; then
           diff local_out reference_out
           exit
        fi
    else
        (( count++ ))
        echo -e "${GREEN}Passed test"
        echo -n -e  "${RESET}"
    fi
    resetTest
done

echo -e -n $YELLOW
echo "Passed $count out of $maxcount tests"

echo -e -n $RESET

rm local_out
rm reference_out
rm custom_test.c