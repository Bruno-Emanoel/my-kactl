#!/bin/bash

./exec/compile.sh "$1"

echo "Executando..."

./a.exe
rm ./a.exe