import random
import math

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

def delta(i):
    s1 = s.content[i]
    s2 = s.content[i+1]

    p = 0
    m = 0
    if i-1 >= 0:
        s0 = s.content[i-1]
        p += score(s0, s2)
        m += score(s0, s1)
    if i +2 < len(s.content):
        s3 = s.content[i+2]
        p += score(s1, s3)
        m += score(s2, s3)

    return p - m

t0 = 10
N = 1000000
# lamb = 0.001

dtot = 0
best = 0

# print(sum(score(s.content[i], s.content[i+1]) for i in range(len(s.content)-1)))

# print(s.slides)
for i in range(N):
    idx = random.randint(0, len(s.content)-2)
    d = delta(idx)

    t = t0 - t0*i/N*1.1
    if t <= 0:
        accept = d > 0
    else:
        accept = d > 0 or math.exp(d/t)
    if random.random() < accept:
        dtot += d
        s.swap(idx, idx+1)
        print(dtot)
    if dtot > best:
        best = dtot
    if dtot > 10000:
        break


# print(dtot)
# print(best)
# print(s.slides)
s.print()
