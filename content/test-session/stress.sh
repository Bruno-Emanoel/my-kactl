#!/bin/bash
set -e

declare -i N

if [ -z "$1" ] ; then
  N=100
else
  N=$1
fi

g++ -std=c++20 -O2 gen.cpp -o gen
g++ -std=c++20 -O2 brute.cpp -o brute
g++ -std=c++20 -O2 code.cpp -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -o code

echo "Arquivos compilados"

diffFound=0

i=1
while [ $i -le $N ] ; do
    ./gen $i > in
    ./code < in > out
     ./brute < in > ok
    if diff -w out ok > /dev/null 2>&1; then
      echo "Passed test: " $i
    else
      diffFound=1
      break
    fi
    ((++i))
done

if [ $diffFound -ne 0 ] ; then
  echo "WA no seguinte teste:"
  cat in
  echo "Sua resposta eh:"
  cat out
  echo "A resposta correta eh:"
  cat ok
else
  echo "Todos os teste passaram!"
fi

rm ./gen
rm ./code
rm ./brute
# rm in
# rm out
# rm ok