#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
RESET='\033[0m'
CYAN='\x1B[36m'
YELLOW='\033[0;33m'  

echo -e "$CYAN:=:=: [Custom Test] creeper.c v1.0 :=:=:"
echo -e "https://github.com/stormofice/sp-custom-tests"

echo -e -n $RED
if [ ! -f creeper-ref ]; then
    echo "Couldn't find creeper-ref, please provide the reference file"
    exit
fi
if [ ! -f creeper ]; then
    echo "Couldn't find creeper, please provide your local solution"
    exit
fi

echo -n -e $YELLOW

createFolder() {
echo -e "Creating static test folder structure"

mkdir .customTestDir
mkdir .customTestDir/a
mkdir .customTestDir/a/b
mkdir .customTestDir/a/b/c1
mkdir .customTestDir/a/b/c2
mkdir .customTestDir/a/b/c1/d
mkdir .customTestDir/a/b/c1/d/e

touch .customTestDir/file1
touch .customTestDir/file2
touch .customTestDir/file3
touch .customTestDir/a/b/file1
touch .customTestDir/a/b/file2
touch .customTestDir/a/b/c1/file1
touch .customTestDir/a/b/c2/file1
touch .customTestDir/a/b/c1/d/file1
touch .customTestDir/a/b/c1/d/file2
touch .customTestDir/a/b/c1/d/file3
touch .customTestDir/a/b/c1/d/file4
touch .customTestDir/a/b/c1/d/e/file1

ln -s .customTestDir/a/b/c1 .customTestDir/link
}

count=0
maxcount=0
timelocal=0
timeref=0

testPath() {
path2=$1
pattern2=""
depth2=""
type=2""
if [ "$2" != "-1" ]; then
  pattern2=" -name=$2"
fi
if [ "$3" != "-1" ]; then
  depth2=" -maxdepth=$3"
fi
if [ "$4" != "-1" ]; then
  depth2=" -type=$4"
fi

echo -e -n "$YELLOW"
echo Testing "./creeper $path2$depth2$pattern2$type2"

ts=$(date +%s%N)
local_output=$(./creeper $path2$depth2$pattern2$type2 2>&1)
tt=$((($(date +%s%N) - $ts) / 1000000))
timelocal=$((timelocal+tt))
ts=$(date +%s%N)    
reference_output=$(./creeper-ref $path2 $depth2$pattern2$type2 2>&1)
tr=$((($(date +%s%N) - $ts) / 1000000))
timeref=$((timeref+tr))
echo -e -n "$CYAN"
echo -e "Local: $tt ms; Reference: $tr ms"

(( maxcount++ ))

if [[ $(diff -q <(echo "$local_output") <(echo "$reference_output")) ]]; then
        echo -e "${RED}Test failed"
        echo -n -e "${RESET}"
        
        echo "You can continue (y), abort (n), write to file (w) or show diff (d) (y/n/w/d)"
        echo -n -e  $RESET
        read -n1
        echo ""
        if [[ "n" = "$REPLY" ]]; then
            exit
        elif [[ "d" = "$REPLY" ]]; then
           diff <(echo "$local_output") <(echo "$reference_output")
           exit
        elif [[ "w" = "$REPLY" ]]; then
           echo "$local_output" > local_out
           echo "$reference_output" > reference_out
           exit
        fi
else
        (( count++ ))
        echo -e "${GREEN}Passed test"
        echo -n -e  "${RESET}"
fi  
}

if [ ! -d .customTestDir ]; then
  createFolder
fi


declare -a folders=("/bin/" "/usr/" ".customTestDir/" "/etc/" "/lib/")
declare -a patterns=("-1" "a" "1" "f")
declare -a maxdepths=("-1" "2" "4" "8")
declare -a types=("-1" "f" "d")


for folder in "${folders[@]}"
do
  for pattern in "${patterns[@]}"
  do
    for maxdepth in "${maxdepths[@]}"
      do
        for type in "${types[@]}"
        do
          testPath $folder $pattern $maxdepth $type
        done
      done
  done
done

echo -e -n $YELLOW
echo "=== Summary ==="
echo "Passed $count out of $maxcount tests"
echo "Cumulative timings: Local: $timelocal ms  Reference: $timeref ms"

echo -n -e $RESET
rm -r .customTestDir/