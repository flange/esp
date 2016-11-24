#!/bin/bash

if [ "x$1" == "x" ]; then
  echo "Usage: ./$0 <gif name>"
  exit 1
fi

convert -delay 20 -loop 0 *.png $1.gif
