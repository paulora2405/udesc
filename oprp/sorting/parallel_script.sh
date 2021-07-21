#!/bin/bash

MAX_THREADS=6
ARRAY_SIZE=200000
REPETITIONS=10
APP=quick.out
OUTDIR=${APP}_parallel_reverse

if [ ! -d "$OUTDIR" ]; then mkdir $OUTDIR; fi;

for (( j=1; j<=$MAX_THREADS; j++));
do
  echo "num_threads=$j";
  echo -e "time" > $OUTDIR/${j}_threads.txt;
  export OMP_NUM_THREADS=$j;
  for (( i=0; i<$REPETITIONS; i++));
  do
    ./$APP $ARRAY_SIZE;
  done >> $OUTDIR/${j}_threads.txt;
done;
exit;