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



l1 = str(sys.argv[1]).split()
l2 = str(sys.argv[2]).split()

relations = getBinaryRelations(l1, l2)

#relation = [('a', 'x'), ('a', 'y')]
#relation = [('a', 'x'), ('a', 'y'), ('b', 'y')]
#print(relation)

for relation in relations:
  print(relation)

  lhs = set()
  rhs = set()

  for l,r in relation:
    lhs.add(l)
    rhs.add(r)


  lscombos = list(powerset(lhs))
  lscombos = list(map(lambda x: list(x), lscombos))
  lscombos.remove([])


  rscombos = list(powerset(rhs))
  rscombos = list(map(lambda x: list(x), rscombos))

  rscombos.remove([])

  almUnion = product(lscombos, rscombos)

  max_k = relationMaxComplexity(relation)

  almMap = {}

  for pair in almUnion:
    c = getComplexity(pair)
    almMap.setdefault(c, []).append(pair)

  for k in range(1, max_k + 1):
    if k not in almMap:
      continue

    pairs = almMap[k]

    for pair in pairs:
      print("  ", k, pair)

    print()



#  for p in almUnion:
#    print("  ", p[0], "-", p[1], len(p[0] * len(p[1])))



  print()


#pairs = relationToPairs(relation)

#for p in pairs:
#  print(p)

