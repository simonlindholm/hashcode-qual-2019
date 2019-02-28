from random import *
from itertools import *

def score(

def pairwise(t):
    it = iter(t)
    return izip(it,it)

n = int(raw_input())
tags = []
verts = []
horis = []
for photo in xrange(n):
    line = raw_input().split()
    orient = line[0]
    tags = line[2:]
    if orient == 'H':
        horis.append([photo])
    else:
        verts.append(photo)

# Pair verts
shuffle(verts)
paired = zip(verts[::2], verts[1::2])
if paired[-1][1] == None:
    paired = paired[:-1]
slides = horis + paired
shuffle(slides)

print len(slides)
for slide in slides:
    print " ".join(map(str, slide))
