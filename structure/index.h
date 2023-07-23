#ifndef KMM_INDEX_H
#define KMM_INDEX_H

#include "../types.h"
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <vector>
using namespace std;
class Index{
public:
    vector<unordered_set<VertexID>> com_index;  //data_id: query_id...
public:
    Index(int queryNum,int dataNum);
    void print_com_index();

};










#endif //KMM_INDEX_H
