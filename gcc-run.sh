#!/bin/bash

touch ./res-gcc/auto.txt
touch ./res-gcc/dynamic.txt
touch ./res-gcc/static.txt
touch ./res-gcc/guided.txt
touch ./res-gcc/dyn-1.txt
touch ./res-gcc/dyn-4.txt
touch ./res-gcc/dyn-16.txt
touch ./res-gcc/dyn-20.txt
touch ./res-gcc/stat-1.txt
touch ./res-gcc/stat-4.txt
touch ./res-gcc/stat-16.txt
touch ./res-gcc/stat-20.txt
touch ./res-gcc/gu-1.txt
touch ./res-gcc/gu-4.txt
touch ./res-gcc/gu-16.txt
touch ./res-gcc/gu-20.txt
touch ./res-gcc/dyn-1024.txt
touch ./res-gcc/stat-1024.txt
touch ./res-gcc/gu-1024.txt

for (( c=10000; c<=250000; c+=10000 ))
do  

   # ./lab2-auto $c >> ./res-gcc/auto.txt
   # ./lab2-dynamic $c >> ./res-gcc/dynamic.txt
   # ./lab2-static $c >> ./res-gcc/static.txt
   # ./lab2-guided $c >> ./res-gcc/guided.txt
   # ./lab2-dyn-1 $c >> ./res-gcc/dyn-1.txt
   # ./lab2-dyn-4 $c >> ./res-gcc/dyn-4.txt
   # ./lab2-dyn-16 $c >> ./res-gcc/dyn-16.txt
   # ./lab2-dyn-20 $c >> ./res-gcc/dyn-20.txt
   # ./lab2-stat-1 $c >> ./res-gcc/stat-1.txt
   # ./lab2-stat-4 $c >> ./res-gcc/stat-4.txt
   # ./lab2-stat-16 $c >> ./res-gcc/stat-16.txt
   # ./lab2-stat-20 $c >> ./res-gcc/stat-20.txt
   # ./lab2-gu-1 $c >> ./res-gcc/gu-1.txt
   # ./lab2-gu-4 $c >> ./res-gcc/gu-4.txt
   # ./lab2-gu-16 $c >> ./res-gcc/gu-16.txt
   # ./lab2-gu-20 $c >> ./res-gcc/gu-20.txt
   ./lab2-dyn-1024 $c >> ./res-gcc/dyn-1024.txt
   ./lab2-stat-1024 $c >> ./res-gcc/stat-1024.txt
   ./lab2-gu-1024 $c >> ./res-gcc/gu-1024.txt

done

