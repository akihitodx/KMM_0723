#ifndef KMM_ALG_H
#define KMM_ALG_H

#include "../structure/graph.h"
#include "../structure/index.h"
#include "../structure/result.h"
#include "../structure/match.h"
#include <algorithm>
#include <iostream>
void preProsessing(Graph &query, Graph &data,Index &index);

void updateIndex(VertexID node, VertexID nei ,Graph &query, Graph &data, Index &index);

void Kernel_Match(Graph &query, Graph &data, Index &index, Match &match,VertexID query_exc, VertexID data_exc);

bool unKernel_Match(VertexID is_query,VertexID data_node, Graph &query, Graph &data, Index &index, Match &match);

void subgraph_Match(VertexID left_node,VertexID right_node,Graph &query,Graph &data, Index &index, Result &res);

bool do_main(VertexID a,VertexID b,Graph &query, Graph &data,Index &index);

void do_submatch(set<pair<VertexID,VertexID>> &match_edge,VertexID first,VertexID second,Graph &query,Graph &data, Index &index, Result &result);
#endif //KMM_ALG_H
