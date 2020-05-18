#include"graph.h"
#include"../Queue/queue.h"
#include"../Stack/stack.h"
template <typename Tv,typename Te>
void Graph<Tv, Te>::bfs(int s) {
	reset(); int clock = 0; int v = s;
	do
		if (UNDISCOVERED == status(v))
			BFS(v, clock);
	while (s != (v = (++v%n)));
}
template <typename Tv,typename Te>
void Graph<Tv, Te>::BFS(int v, int& clock) {
	Queue<int> Q;
	status(v) = DISCOVERED; Q.enqueue();
	while (!Q.empty()) {
		int v = Q.dequeue(); dTime = ++clock;
		for(int u=firstNbr(v);-1<u;u=nextNbr())
			if (UNDISCOVERED == status(u)) {
				status(u) = DISCOVERED; Q.enqueue();
				status(v, u) = TREE; parent(u) = v;
			}
			else {
				status(v, u) = CROSS;
			}
		status(v) = VISITED;
	}
}
template <typename Tv,typename Te>
void Graph<Tv, Te>::dfs(int s) {
	reset(); int clock = 0; int v = s;
	do
		if (UNDISCOVERED == status(v))
			DFS(v, clock);
	while (s != (v = (++v%n)));
}
template <typename Tv,typename Te>
void Graph<Tv, Te>::DFS(int v, int& clock) {
	dTime(v) = ++clock; status(v) = DISCOVERED;
	for(int u=firstNbr(v);-1<u;u=nextNbr(v,u))
		switch (status(u)) {
			case UNDISCOVERED:
				status(v, u) = TREE; parent(u) = v; DFS(u, clock); break;
			case DISCOVERED:
				status(v, u) = BACKWARD; break;
			default:
				status(v, u) = (dTime(v) < dTime(u)) ? FORWARD : CROSS; break;
		}
	status(v) = VISITED;
}
template <typename Tv,typename Te>
Stack<Tv>* Graph<Tv, Te>::tSort(int s) {
	reset(); int colck = 0; int v = s;
	Stack<Tv>* S = new Stack<Tv>;
	do {
		if (UNDISCOVERED == status(v))
			if (!TSort(v, colck, S)) {
				while (!S->empty())
					S->pop(); 
				break;
			}
	} while (s != (v = (++v%n)));
	return S;
}
template <typename Tv,typename Te>
bool Graph<Tv, Te>::TSort(int v, int& clock, Stack<Tv>* S) {
	dTime(v) = ++clock; status(v) = DISCOVERED;
	for(u=firstNbr(v);-1<u;u=nextNbr(v,u))
		switch (status(u)) {
			case UNDISCOVERED:
				parent(u) = v; status(v, u) = TREE;
				if (!TSort(u, clock, S))
					return false;
				break;
			case DISCOVERED:
				status(v, u) = BACKWARD;
				return false;
			default:
				status(v, u) = (dTime(v) < dTime(u)) ? FORWARD : CROSS;
				break;
		}
	status(v) = VISITED; S->push(vertex(v));
	return true;
}
template <typename Tv,typename Te>
void Graph<Tv, Te>::bcc(int s) {
	reset(); int colck = 0; int v = s; Stack<int> S;
	do
		if (UNDISCOVERED == status(v)) {
			BCC(v, colck, S);
			S.pop();
		}
	while (s != (v = (++v%n)));
}
#define hca(x) (fTime(x))
template <typename Tv,typename Te>
void Graph<Tv, Te>::BCC(int v, int& colck, Stack<int>& S) {
	hca(v) = dTime(v) = ++clock; status(v) = DISCOVERED; S.push(v);
	for(u=firstNbr(v);-1<u;u=nextNbr(v,u))
		swich(status(u)) {
			case UNDISCOVERED:
				parent(u) = v; status(v, u) = TREE; BCC(u, colck, S);
				if (hca(u) < dTime(v))
					hca(v) = min(hca(v), hca(u));
				else {
					while (v != S.pop());
					S.push(v);
				}
				break;
			case DISCOVERD:
				status(v, u) = BACKWARD;
				if (u != parent(v)) hca(v) = min(hca(v), dTime(u));
				break;
			default:
				status(v, u) = (dTime(v) < dTime(u)) ? FORWARD : CROSS;
				break;
	}
	status(v) = VISITED;
}
template <typename Tv,typename Te> template <typename PU>
void Graph<Tv, Te>::pfs(int s, PU prioUpdater) {
	reset(); int v = s;
	do
		if (UNDISCOVERED == status(v))
			PFS(v, prioUpdater);
	while (s != (v = (++v%n)));
}
template <typename Tv,typename Te> template <typename PU>
void Graph<Tv, Te>::PFS(int s, PU prioUpdater) {
	priority(s) = 0; status(s) = VISITED; parent(s) = -1;
	while (1) {
		for (int w = firstNbr(s); -1 < w; w = nextNbr(s, w))
			prioUpdater(this, s, w);
		for(int shortest=INT_MAX,w=0;w<n;w++)
			if(status(w)==UNDISCOVERED)
				if(shortest>priority(w)){
					shortest = priority(w); s = w;
				}
		if (VISITED == status(s)) break;
		status(s) = VISITED; status(parent(s), s) = TREE;
	}
}
template <typename Tv, typename Te> struct PrimPU {
	virtual void operator()(Graph<Tv, Te>* g, int uk, int v) {
		if(g->status(v)==UNDISCOVERED)
			if (g->priority(v) > g->weight(uk, v)) {
				g->priority(v) = g->weight(uk, v);
				g->parent(v) = uk;
			}
	}
};
template <typename Tv, typename Te> struct DijkstraPU {
	virtual void operator()(Graph<Tv, Te>* g, int uk, int v) {
		if(g->status(v)==UNDISCOVERED)
			if (g->priority(v) > g->priority(uk) + g->weight(uk, v)) {
				g->priority(v) = g->priority(uk) + g->weight(uk, v);
				g->parent(v) = uk;
			}
	}
};