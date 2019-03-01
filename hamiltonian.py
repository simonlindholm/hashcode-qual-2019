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

best_score = 0
best_slides = []
for samp in xrange(10):
    # Construct graph
    neis = [0]*n
    for pic in xrange(n):
        neis[pic] = set()
        for tag in tags_by_pic[pic]:
            for pic2 in pics_by_tag[tag]:
                neis[pic].add(pic2)
        neis[pic].remove(pic)

    # Sort pics by degree and make maps
    counts = [(len(neis[pic]), pic) for pic in xrange(n)]
    count_pos = [0]*n
    counts.sort()
    for pos in xrange(n):
        count_pos[counts[pos][1]] = pos

    used = [False]*n
    next_pos = 0
    curr = randint(0,n-1)
    slides = []
    count = n

    for pos in xrange(n-1):
        # Move to the lowest degree neighbor
        best = 100
        best_nei = -1
        for nei in neis[curr]:
            #print neis[nei]
            if len(neis[nei]) < best:
                best = nei
                best_nei = nei
            neis[nei].remove(curr)

        used[count_pos[curr]] = True
        slides.append([curr])
        curr = best_nei
        # If no neighbor, start over
        if curr == -1:
            count -= 1
            while used[next_pos]:
                next_pos += 1
            curr = counts[next_pos][1]

    slides.append([curr])
    #print count*3
    #print score(slides, tags_by_pic)
    if count > best_score:
        best_score = count
        best_slides = slides[:]

print n
#print score(best_slides, tags_by_pic)
for slide in best_slides:
    print " ".join(map(str, slide))
