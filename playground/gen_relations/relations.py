#! /usr/bin/env python

import sys
import itertools
from itertools import chain, combinations

def product(l1, l2):
    return list(itertools.product(l1, l2))

def getBinaryRelations(l1, l2):
  Result = []

  todo = []
  todo.append(product(l1, l2))


  while (len(todo) > 0):

    curr = todo.pop(0)

    if curr not in Result:
      Result.append(curr)

    for k in range(0, len(curr)):
      nr = list(curr)
      nr.pop(k)

      if (len(nr) == 0):
        continue

      todo.append(nr)

  Result.reverse()
  return Result

def powerset(iterable):
    "powerset([1,2,3]) --> () (1,) (2,) (3,) (1,2) (1,3) (2,3) (1,2,3)"
    s = list(iterable)
    return chain.from_iterable(combinations(s, r) for r in range(len(s)+1))

def relationToDict(relation):
  d = {}

  for x, y in relation:
      d.setdefault(x, []).append(y)

  return d


def relationToPairs(relation):
  res = []

  for p in list(powerset(relation)):

    subrelation = list(p)

    if len(subrelation) == 0:
      continue

    correspondences = relationToDict(subrelation)

    for item in correspondences.items():
      res.append(item)

  return res

def relationMaxComplexity(relation):
  lhs = set()
  rhs = set()

  for l,r in relation:
    lhs.add(l)
    rhs.add(r)

  return len(lhs) * len(rhs)

def getComplexity(almPair):
  return len(almPair[0]) * len(almPair[1])

def printRelation(relation):
  tmp = []

  for corr in relation:
    tmp.append((set(corr[0]), set(corr[1])))

  print(tmp)




l1 = str(sys.argv[1]).split()
l2 = str(sys.argv[2]).split()

relations = getBinaryRelations(l1, l2)

new_relations = []

for relation in relations:
  new_relation = []

  for corr in relation:
    new_corr = (frozenset(corr[0]), frozenset(corr[1]))
    new_relation.append(new_corr)

  new_relations.append(new_relation)



for relation in new_relations:

  printRelation(relation)

  almMap = {}
  almMap[1] = set()

  # 1er Korrespondenzen
  for t in relation:
    almPair = (frozenset(t[0]), frozenset(t[1]))
    almMap[1].add(almPair)


  for corr in almMap[1]:

    lhs_labels_remaining = frozenset([x for x in l1 if x not in corr[0] ])
    rhs_labels_remaining = frozenset([x for x in l2 if x not in corr[1] ])

    for l in lhs_labels_remaining:
      v_corr = (frozenset([l]), corr[1])

      if v_corr in relation:

        new_corr = (corr[0].union(v_corr[0]), corr[1])
        new_corr_c = getComplexity(new_corr)

        if not new_corr_c in almMap:
          almMap[new_corr_c] = set()

        if new_corr not in almMap[new_corr_c]:
          almMap.setdefault(new_corr_c, []).add(new_corr)


    for l in rhs_labels_remaining:
      v_corr = (corr[0], frozenset([l]))

      if v_corr in relation:

        new_corr = (corr[0], corr[1].union(v_corr[1]))
        new_corr_c = getComplexity(new_corr)

        if not new_corr_c in almMap:
          almMap[new_corr_c] = set()

        if new_corr not in almMap[new_corr_c]:
          almMap.setdefault(new_corr_c, []).add(new_corr)

  print()

  for p in almMap:
    corr_set = almMap[p]

    for corr in corr_set:
      print("  ", p, set(corr[0]), " - ", set(corr[1]))

    print()

  print("-----------------------------------------------------------\n")





