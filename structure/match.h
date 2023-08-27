#ifndef KMM_MATCH_H
#define KMM_MATCH_H

#include "../types.h"
#include "graph.h"
#include "index.h"
#include <vector>
#include <list>
using namespace std;

class Match {
public:
    int count = 0;
    vector<pair<VertexID, VertexID>> kernel_path;
//    vector<VertexID> unkernel_path;
    vector<vector<list<VertexID>>> res;
    vector<list<VertexID>> match_table;
    unordered_set<VertexID> kernel_matched;
    unordered_set<VertexID> matched;

public:
    bool set_Match_exc(Graph &query, Graph &data, Index &index, VertexID is_query, VertexID data_node,
                       VertexID another_data_node);

    bool set_Match_single(Graph &query, Graph &data, Index &index, VertexID is_query, VertexID data_node,
                          VertexID is_query_unkernel, VertexID data_node_unkernel);

    bool set_Match_double(Graph &query, Graph &data, Index &index, VertexID is_query, VertexID data_node,
                          VertexID is_query_another, VertexID data_node_another);

    void getPath(Graph &query, VertexID a);

    void getPath(Graph &query, VertexID a, VertexID b);

    bool verification();

    void insert_res();

    void get_res_split(Graph &query);
    void do_get_res_split(Graph &query,vector<VertexID> &temp,int num,int local);

};


#endif //KMM_MATCH_H
