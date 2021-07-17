#!/bin/bash

if [ ! -d "output" ]; then mkdir output; fi;

for j in {1..6};
do
  echo "num_threads=$j";
  echo -e "gosa,\ttime" > output/${j}_threads.txt;
  export OMP_NUM_THREADS=$j;
  for i in {1..10};
  do
    ./himeno < himeno.in;
  done >> output/${j}_threads.txt;
done;
exit;