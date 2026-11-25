#!/bin/bash

EXE=$1
TEST_DIR=$2

i=1

for test in $TEST_DIR/id*; do {
    echo;
    echo "TEST "$i;
    i=$(($i+1));
    cat -A $test;
    echo;
    ./$EXE < $test;
    echo;
} done
