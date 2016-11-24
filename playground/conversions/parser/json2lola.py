#!/usr/bin/env python

import json
from pprint import pprint
import sys

class Transition:

    def __init__(self, json):
        self.consumes = []
        self.produces = []
        self.transjson = json

    def addConsume(self, place):
        self.consumes.append(place)

    def addProduce(self, place):
        self.produces.append(place)

    def getId(self):
        return self.transjson["resourceId"]

    def getTitle(self):
        return self.transjson["properties"]["title"]


    def print(self):
        print("transition:")
        print("  name: " + self.transjson["properties"]["title"] + "  (" + self.transjson["resourceId"] + ")")

        print("  consumes:")

        for place in self.consumes:
            print("    " + place["properties"]["title"])

        print("  produces:")

        for place in self.produces:
            print("    " + place["properties"]["title"])

        print()




if len(sys.argv) != 2:
    print("Usage: python " + sys.argv[0] + " <petri net json>")
    exit(1);


with open(sys.argv[1]) as jsonFile:
    pn = json.load(jsonFile)

pnElements = pn["childShapes"]

places = []
transitions = []
arcs = []

for elem in pnElements:
    if elem["stencil"]["id"] == "Place":
        places.append(elem)

    if elem["stencil"]["id"] == "Transition":
        transitions.append(elem)

    if elem["stencil"]["id"] == "Arc":
        arcs.append(elem)


print("PLACE")
for place in places[:-1]:
    print("  " + place["properties"]["title"] + ",")

print("  " + places[-1]["properties"]["title"])
print(";\n")


print("MARKING")
print("  " + places[0]["properties"]["title"] + ":  1")
print(";\n")


finalTransitions = []

for transition in transitions:
    ft = Transition(transition)
    finalTransitions.append(ft)

    # consuming places
    for place in places:
        outArcIds = [x["resourceId"] for x in place["outgoing"]]
        outArcs = []

        for oaId in outArcIds:
            for arc in arcs:
                if arc["resourceId"] == oaId:
                    outArcs.append(arc)

        for oa in outArcs:
            if oa["target"]["resourceId"] == transition["resourceId"]:
                ft.addConsume(place)

    # producing places
    outArcIds = [x["resourceId"] for x in transition["outgoing"]]
    outArcs = []

    for oaId in outArcIds:
        for arc in arcs:
            if arc["resourceId"] == oaId:
                outArcs.append(arc)

    targetPlaces = []

    for oa in outArcs:
        for place in places:
            if place["resourceId"] == oa["target"]["resourceId"]:
                ft.addProduce(place)





for ft in finalTransitions:
    print("TRANSITION " + ft.getTitle())

    print("CONSUME");
    if len(ft.consumes) == 0:
        print(";")
    else:
        for place in ft.consumes[:-1]:
            print("  " + place["properties"]["title"] + ":  1,")

        print("  " + ft.consumes[-1]["properties"]["title"] + ":  1;")


    print("PRODUCE")
    if len(ft.produces) == 0:
        print(";")
    else:
        for place in ft.produces[:-1]:
            print("  " + place["properties"]["title"] + ":  1,")

        print("  " + ft.produces[-1]["properties"]["title"] + ":  1;")

    print()










print("\n{ END OF FILE }")









