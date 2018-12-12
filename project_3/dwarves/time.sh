#! /bin/bash

make
runs=${1:-100}
task=${2:-"a"}
avg=0
for i in $(seq $runs); do
    avg=$(( $avg + $(./dwarves $task - - - $RANDOM fast | awk '/Lumber/ { print $2 }') ))
done
echo $(($avg / $runs))
