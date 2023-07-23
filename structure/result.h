#ifndef KMM_0723_RESULT_H
#define KMM_0723_RESULT_H


#include "../types.h"
#include <vector>
using namespace std;
class Result{
public:
    vector<vector<vector<VertexID>>> res;
    Result operator+(vector<vector<vector<VertexID>>> &rr);
    void print_res();
};


#endif //KMM_0723_RESULT_H
