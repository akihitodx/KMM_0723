#ifndef KMM_0723_RESULT_H
#define KMM_0723_RESULT_H


#include "../types.h"
#include <vector>
#include <list>
#include "graph.h"
using namespace std;
class Result{
public:
    vector<vector<list<VertexID>>> res;
    vector<vector<VertexID>> res_split;
    Result operator+(vector<vector<list<VertexID>>> &rr);
    void get_res_split(Graph &query);
    void do_get_res_split(Graph &query,vector<VertexID> &temp,unordered_set<VertexID> &matched,int num,int local);
    void print_res();
    void print_res_split();
};


#endif //KMM_0723_RESULT_H
