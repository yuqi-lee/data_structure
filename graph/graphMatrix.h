#pragma once
#include"../Vector/vector.h"
#include"graph.h"
#include"edge.h"
#include"vertex.h"
template <typename Tv, typename Te>
class GraphMatrix :public Graph<Tv, Te> {
private:
	Vector< Vertex<Tv> >V;
	Vector< Vector< Edge<Te>* > >E;
public:
	GraphMatrix() { n = e = 0; }
	~GraphMatrix() {
		for (int j = 0; j < n; j++)
			for (int k = 0; k < n; k++)
				delete E[j][k];
	}
	virtual Tv& vertex(int i) { return V[i].data; }
	virtual int inDegree(int i) { return V[i].inDegree; }
	virtual int outDegree(int i) { return V[i].outDegree; }
	virtual firstNbr(int i) { return nextNbr(i, n); }
	virtual nextNbr(int i, int j) {
		while ((-1 < j) && (!exists(i, --j))); return j;
	}
	virtual VStatus& status(int i) { return V[i].status; }
	virtual int& dTime(int i) { return V[i].dTime; }
	virtual int& fTime(int i) { return V[i].fTime; }
	virtual int& parent(int i) { return V[i].parent; }
	virtual int& priority(int i) { return V[i].priority; }
	virtual int insert(Tv const& vertex) {
		for (int j = 0; j < n; j++) E[j].insert(NULL); n++;
		E.insert(Vector<Edge<Te>*>(n, n, (Edge<Te>*) NULL));
		return V.insert(Vector<Tv>(vertex));
	}
	virtual Tv remove(int i) {
		for (int j = 0; j < n; j++)
			if (exists(i, j)) { delete E[i][j]; V[j].inDegree--; }
		for (int j = 0; j < n; j++)
			if (exists(j, i)) { delete E[j].remove(i); V[j].outDegree--; }
		Tv vBak = vertex(i); V.remove(i);
		return vBak;
	}
	virtual bool exists(int i, int j) {
		return (0 <= i) && (i < n) && (0 <= j) && (j < n) && E[i][j] != NULL;
	}
	virtual EStatus& status(int i, int j) { return E[i][j]->status; }
	virtual Te& edge(int i, int j) { return E[i][j]->data; }
	virtual int& weight(int i, int j) { return E[i][j]->weight; }
	virtual void insert(Te const& edge, int w, int i, int j) {
		if (exists(i, j)) return;
		E[i][j] = new Edge<Te>(edge, w);
		e++; V[i].outDegree++; V[j].inDegree++;
	}
	virtual Te remove(int i, int j) {
		Te eBak = edge(i, j); delete E[i][j]; E[i][j] = NULL;
		e--; V[i].outDegree--; V[j].inDegree--;
		return eBak;
	}
};
