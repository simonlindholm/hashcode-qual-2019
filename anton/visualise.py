import pandas as pd
import matplotlib.pyplot as plt
import itertools as it

class Input:

    def __init__(self):
        self.N = int(input())
        self.orientations = []
        self.tags = []
        for _ in range(self.N):
            inp = input().split()
            self.orientations.append(inp[0])
            self.tags.append(set(inp[2:]))

data = Input()

print(len(set(it.chain(*data.tags))))
print(data.N)
# lens = list(map(len, data.tags))
# plt.hist()
