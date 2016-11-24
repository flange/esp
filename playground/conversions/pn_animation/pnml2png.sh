#!/bin/bash

if [ "x$1" == "x" ]; then
  echo "Usage: ./$0 <pnml file>"
  exit 1
fi

FILE=$(basename $1)

NAME="${FILE%.*}"
EXTENSION="${FILE##*.}"

sh pnml2dot.sh $1 | dot -Tpng -o $NAME.png
