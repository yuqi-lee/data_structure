#pragma once
#include"graph.h"
template <typename Te> struct Edge {
	Te data;
	int weight;
	EStatus status;
	Edge(Te const& d, int w) :data(d), weight(w), status(UNDETERMINED) {};
};