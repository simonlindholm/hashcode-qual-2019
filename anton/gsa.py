import random
import math
from copy import deepcopy

class Sol:
    def __init__(self, data):
        self.slides = []
        self.content = []
        self.n_rows = int(input())
        for _ in range(self.n_rows):
            r = tuple(map(int, input().split()))
            self.slides.append(r)
            if len(r) == 1:
                self.content.append(data.tags[r[0]])
            else:
                self.content.append(data.tags[r[0]] | data.tags[r[1]])

    def swap(self, i, j):
        self.slides[i], self.slides[j] = self.slides[j], self.slides[i]
        self.content[i], self.content[j] = self.content[j], self.content[i]

    def print(self):
        print(self.n_rows)
        for i in range(self.n_rows):
            print(*self.slides[i])


class Input:
    def __init__(self):
        self.N = int(input())
        self.orientations = []
        self.tags = []
        self.hs = []
        self.vs = []
        for i in range(self.N):
            inp = input().split()
            self.orientations.append(inp[0])

            tags = set(inp[2:])
            self.tags.append(tags)

            if inp[0] == 'H':
                self.hs.append((i, tags))
            else:
                assert inp[0] == 'V'
                self.vs.append((i, tags))

data = Input()
s = Sol(data)

def score(s1, s2):
    return min(len(s1&s2), len(s1-s2), len(s2 -s1))

def delta(i1, i2):
    a0 = s.content[i1-1]
    a1 = s.content[i1]
    a2 = s.content[i1+1]

    b0 = s.content[i2-1]
    b1 = s.content[i2]
    b2 = s.content[i2+1]

    p = score(a0, b1) + score(b1, a2) + score(b0, a1) + score(a1, b2)
    m = score(a0, a1) + score(a1, a2) + score(b0, b1) + score(b1, b2)

    return p - m

t0 = 10
N = 1e6
lamb = 0.001
reset_limit = 1000

dtot = 0
best = 0

print(sum(score(s.content[i], s.content[i+1]) for i in range(len(s.content)-1)))

# print(s.slides)
last_improvement = 0
reset_s = deepcopy(s)
for i in range(int(N)):
    idx1 = random.randint(0, len(s.content)-2)
    idx2 = random.randint(0, len(s.content)-2)

    if idx1 < 1 or idx1 > len(s.content)-2:
        continue
    if idx2 < 1 or idx2 > len(s.content)-2:
        continue

    d = delta(idx1, idx2)
    # print(i)
    # print(d)

    t = t0 * (1 - i/N*1.1)
    if t <= 0:
        accept = d > 0
    else:
        accept = d > 0 or math.exp(d/t)
    if random.random() < accept:
        dtot += d
        s.swap(idx1, idx2)
        # print(dtot)
    if dtot > best:
        best = dtot
        reset_s = deepcopy(s)
    if d > 0:
        last_improvement = i
    if i - last_improvement > reset_limit:
        dtot = best
        s = reset_s

    if dtot > 1:
        break


# print(dtot)
# print(best)
# print(s.slides)
reset_s.print()
