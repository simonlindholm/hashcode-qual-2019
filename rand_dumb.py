from random import *
from itertools import *
from time import *

def score(slides, tags):
    total = 0
    for slide in xrange(1,len(slides)):
        left = set()
        for pic in slides[slide-1]:
            left = left | tags[pic]
        right = set()
        for pic in slides[slide]:
            right = right | tags[pic]
        inter = left & right
        total += min(len(left) - len(inter), len(inter), len(right) - len(inter))
    return total

def pairwise(t):
    it = iter(t)
    return izip(it,it)

n = int(raw_input())
tags = [0]*n
verts = []
horis = []
for pic in xrange(n):
    line = raw_input().split()
    orient = line[0]
    tags[pic] = set(line[2:])
    if orient == 'H':
        horis.append([pic])
    else:
        verts.append(pic)

t0 = time()
best_score = 0
best = []

while time()-t0 < 1:
    # Pair verts
    shuffle(verts)
    paired = zip(verts[::2], verts[1::2])
    if len(paired) > 0 and paired[-1][1] == None:
        paired = paired[:-1]
    slides = horis + paired
    shuffle(slides)

    new_score = score(slides, tags)
    if new_score > best_score:
        best_score = new_score
        best = slides[:]

print len(slides)
for slide in slides:
    print " ".join(map(str, slide))
