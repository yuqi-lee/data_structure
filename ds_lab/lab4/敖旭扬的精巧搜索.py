from graphviz import Graph
class Stack:
def __init__(self):
self.items = []
def empty(self):
return self.items == []
def push(self,item):
self.items.append(item)
def pop(self):
return self.items.pop()
def top(self):
return self.items[-1]
def size(self):
return len(self.items)
class Queue:
def __init__(self):
self.items = []
def empty(self):
return self.items == []
def enqueue(self, item):
self.items.insert(0,item)
def dequeue(self):
return self.items.pop()
def size(self):
return len(self.items)
#邻接矩阵表示的图
class MGraph:
def __init__(self, vexs=[], matrix=[[]],arcnum=0):
self.vexnum = len(vexs)
self.arcnum = arcnum
self.vexs = vexs
self.matrix = matrix
self.count = 1
self.visited = [False for i in range(self.vexnum)]
self.low = [0 for i in range(self.vexnum)]
self.order = [0 for i in range(self.vexnum)]
self.m = [0 for i in range(self.vexnum)]
self.pre = [0 for i in range(self.vexnum)]
self.articul = []
self.count = 1
def reset(self):
self.count = 1
self.visited = [False for i in range(self.vexnum)]
self.low = [0 for i in range(self.vexnum)]
self.order = [0 for i in range(self.vexnum)]
self.m = [0 for i in range(self.vexnum)]
self.pre = [0 for i in range(self.vexnum)]
self.articul = []
def findArticul(self):
self.reset()
self.visited[0] = True
self.order[0] = 1
for v in range(self.vexnum):
if self.matrix[0][v] != 0:
self.DFSArticul(v)
break
if self.count < self.vexnum:
self.articul.append(0)
for i in range(v + 1,self.vexnum):
if self.matrix[0][i] != 0 and self.visited[i] == False:
self.DFSArticul(i)
self.articul = list(set(self.articul))
print(" ".join(str(i) for i in self.articul))
def DFSArticul(self,v): #非递归版
S = Stack()
self.visited[v] = True
self.count+=1
self.m[v] = self.count
self.order[v] = self.count
S.push(v)
while not S.empty():
v = S.top()
w = 0
while w < self.vexnum:
if self.matrix[v][w] != 0: #w 是 v 的邻接顶点
if self.visited[w] == False:
self.visited[w] = True
self.pre[w] = v #v 是 w 的父母
self.count+=1
self.order[w] = self.count
self.m[w] = self.count
S.push(w)
break
elif self.order[w] < self.m[v]:
self.m[v] = self.order[w]
w+=1
if w == self.vexnum: #v 遍历完毕
S.pop()
self.low[v] = self.m[v]
w = v v = self.pre[w] #w 遍历完成,v 是父母
if v != 0: #根顶点是否为关节点不采用此判断方式
if self.low[w] < self.m[v]:
self.m[v] = self.low[w]
if self.low[w] >= self.order[v]:
self.articul.append(v)
#邻接表表示的图
class ALGraph:
def __init__(self, vexs=[], matrix=[[]],arcnum=0):
self.vexnum = len(vexs)
self.arc = [[] for i in range(self.vexnum)]
self.vexs = vexs
self.visited = [False for i in range(self.vexnum)]
for i in range(self.vexnum):
for j in range(self.vexnum):
if matrix[i][j] != 0:
self.arc[i].append(j)
def firstNbr(self,v): #v 的第一个邻顶
if self.arc[v] != []:
return self.arc[v][0]
else:
return -1 #-1 表示无邻顶
def nextNbr(self,v,w): #v 的 w 的下一个邻顶
for i in self.arc[v]:
if i > w:
return i
return -1
def BFSGetDist(self,v0=0): #搜索无权图其他点到 v0 的最短路径
Q = Queue()
v = v0
path = [[v] for i in range(self.vexnum)]
self.visited[v] = True
Q.enqueue(v)
while not Q.empty():
v = Q.dequeue()
for w in self.arc[v]:
if self.visited[w] == False:
self.visited[w] = True
path[w] = path[v] + [w]
Q.enqueue(w)
for v in range(self.vexnum):
if v != v0:
print(len(path[v]) - 1,end=' ')
print("->".join(str(i) for i in path[v]))
vg = Graph('图及其应用')
with open('case1.txt') as case:
n = int(case.readline()) #n 表示图中的顶点数
for i in range(n):
vg.node(name=str(i),color='red')
vexs = [str(i) for i in range(n)]
matrix = [[0] * n for i in range(n)]
edges = case.readlines()
arcnum = len(edges)
for edge in edges:
v1,v2 = map(int, edge.split())
matrix[v1][v2] = 1
matrix[v2][v1] = 1 #无向图
vg.edge(str(v1),str(v2),color='blue') g = MGraph(vexs,matrix,arcnum)
alg = ALGraph(vexs,matrix,arcnum)
g.findArticul()
alg.BFSGetDist(0)
vg.view()