#!/bin/bash

if [ "x$1" == "x" ]; then
  echo "Usage: ./$0 <pnml file>"
  exit 1
fi

FILE=$(basename $1)

NAME="${FILE%.*}"
EXTENSION="${FILE##*.}"

for file in `/bin/ls | grep ".pnml"`; do
  sh pnml2png.sh $file
done

sh pngs2gif.sh $NAME
