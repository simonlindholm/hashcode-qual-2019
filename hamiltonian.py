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
tag_nums = {}
tag_names = []
tag_count = 0
tags_by_pic = [0]*n
pics_by_tag = []
verts = []
horis = []

for pic in xrange(n):
    line = raw_input().split()
    orient = line[0]

    # store tag-pic relation
    tags_by_pic[pic] = set()
    for tag in line[2:]:
        # convert to num
        if tag not in tag_nums:
            tag_nums[tag] = tag_count
            tag_names.append(tag)
            pics_by_tag.append(set())
            tag_count += 1
            
        tag_num = tag_nums[tag]
        tags_by_pic[pic].add(tag_num)
        pics_by_tag[tag_num].add(pic)

    if orient == 'H':
        horis.append([pic])
    else:
        verts.append(pic)

print len(horis)
print len(verts)
print [len(tags_by_pic[i]) for i in xrange(10)]
for pic1 in xrange(20):
    left = tags_by_pic[randint(0, len(verts)-1)]
    best1 = 0
    best2 = 0
    best3 = 0
    for pic2 in verts:
        right = tags_by_pic[pic2]
        inter = left & right
        if len(inter) > best1:
            best3 = best2
            best2 = best1
            best1 = len(inter)

    print best1,best2+best3
#        print len(left) - len(inter), len(inter), len(right) - len(inter)
#        best = max(best, min(len(left) - len(inter), len(inter), len(right) - len(inter)))


# Pair verts
shuffle(verts)
paired = zip(verts[::2], verts[1::2])
if len(paired) > 0 and paired[-1][1] == None:
    paired = paired[:-1]
slides = horis + paired

num = len(slides)
t0 = time()
best_score = 0
best = []

# Randomly permute solution and keep best
count = 0
#while time()-t0 < 1:
#    count += 1
#    pos1 = randint(0,num)
#    pos2 = randint(0,num)
#    pos1, pos2 = min(pos1, pos2), max(pos1, pos2)
#
#    slides = slides[:pos1] + slides[pos1:pos2][::-1] + slides[pos2:]
#
#    new_score = score(slides, tags_by_pic)
#    if new_score >= best_score:
#        best_score = new_score
#        best = slides
#    else:
#        slides = best

print num
#for slide in best:
#    print " ".join(map(str, slide))
