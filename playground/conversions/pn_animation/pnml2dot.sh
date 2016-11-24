#!/bin/bash

if [ "x$1" == "x" ]; then
  echo "Usage: ./$0 <pnml file>"
  exit 1
fi

FILE=$(basename $1)

NAME="${FILE%.*}"
EXTENSION="${FILE##*.}"

petri -i pnml -o dot $FILE

sed 's#fixedsize# #g' $FILE.dot > $NAME.dot
rm $FILE.dot

cat $NAME.dot

