#!/usr/bin/env python

import sys

#lolafile = open("ex-small.graph", "r")

source  = 0
target  = 0
lowlink = 0
trans   = "bla"

print("digraph {")

with open(sys.argv[1]) as lolafile:
    for line in lolafile:

      if len(line) == 1:
        continue

      linelist = line.split(" ")

      if "STATE" in linelist:
        source = linelist[1]
        lowlink = linelist[3].rstrip()

      if "->" in linelist:
        trans  = linelist[0]
        target = linelist[2].rstrip()

        print('''  {} -> {} [label="{}", lowlink="{}"];'''.format(source, target, trans, lowlink))



print("}")
