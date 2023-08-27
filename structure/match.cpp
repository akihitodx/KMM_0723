#include "match.h"
#include "../alg/alg.h"
#include <iostream>
#include <queue>
#include <algorithm>


void Match::getPath(Graph &query, VertexID is_query) {
    kernel_path.clear();
    queue<VertexID> qqq;
    queue<VertexID> other;
    unordered_set<VertexID> over;
    over.insert(is_query);
    for(auto i : query.kernel->neighbor_kernel[is_query]){
        qqq.push(i);
        other.push(is_query);
    }
    while(!qqq.empty()){
        auto temp = qqq.front();
        qqq.pop();
        over.insert(temp);
        auto f = other.front();
        other.pop();
        kernel_path.emplace_back(f,temp);
        for(auto i : query.kernel->neighbor_kernel[temp]){
            if(over.find(i) == over.end()){
                qqq.push(i);
                other.push(temp);
            }
        }
    }

}

void Match::getPath(Graph &query, VertexID is_query,VertexID another) {
    kernel_path.clear();
    queue<VertexID> qqq;
    queue<VertexID> other;
    unordered_set<VertexID> over;
    over.insert(is_query);
    for(auto i : query.kernel->neighbor_kernel[is_query]){
        qqq.push(i);
        other.push(is_query);
    }
    while(!qqq.empty()){
        auto temp = qqq.front();
        qqq.pop();
        over.insert(temp);
        auto f = other.front();
        other.pop();
        kernel_path.emplace_back(f,temp);
        for(auto i : query.kernel->neighbor_kernel[temp]){
            if(over.find(i) == over.end()){
                qqq.push(i);
                other.push(temp);
            }
        }
    }
    auto it = std::find_if(kernel_path.begin(), kernel_path.end(),
                           [&is_query, &another](const std::pair<VertexID , VertexID>& p) {
                               return p.first == is_query && p.second == another;
                           });
    if (it != kernel_path.end()) {
        kernel_path.erase(it);
    }

}
bool Match::set_Match_exc(Graph &query,Graph &data,Index &index,VertexID is_query,VertexID data_node,VertexID another_data_node){
    getPath(query,is_query);
//    getUnkernel_path(query,is_query);
    this->match_table.clear();
    this->match_table.resize(query.vNum);
    this->match_table[is_query].push_back(data_node);
    auto flag = unKernel_Match(is_query,data_node,query,data,index,*this);
    if(!flag) return flag;
    int num = 0;
    for(auto i: query.kernel->neighbor_unkernel[is_query]){
        if(std::find(match_table[i].begin(), match_table[i].end(),another_data_node)!=match_table[i].end()){
            ++num;
        }
    }
    if(num == 0) return false;
    this->kernel_matched.insert(is_query);
    this->matched.insert(data_node);
    return flag;
}

bool Match::set_Match_single(Graph &query,Graph &data,Index &index,VertexID is_query,VertexID data_node,VertexID is_query_unkernel,VertexID data_node_unkernel){
    getPath(query,is_query);
//    getUnkernel_path(query,is_query);
    this->match_table.clear();
    this->match_table.resize(query.vNum);
    this->match_table[is_query].push_back(data_node);
    auto flag = unKernel_Match(is_query,data_node,query,data,index,*this);
    if(!flag) return flag;
    this->match_table[is_query_unkernel] = {data_node_unkernel};
    this->kernel_matched.insert(is_query);
    this->matched.insert(data_node);
    return flag;
}

bool Match::set_Match_double(Graph &query,Graph &data,Index &index,VertexID is_query,VertexID data_node,VertexID is_query_another, VertexID data_node_another){
    getPath(query,is_query,is_query_another);
    this->match_table.clear();
    this->match_table.resize(query.vNum);
    this->match_table[is_query].push_back(data_node);
    this->match_table[is_query_another].push_back(data_node_another);

    auto flag = unKernel_Match(is_query,data_node,query,data,index,*this);
    if(!flag) return flag;
    this->kernel_matched.insert(is_query);
    this->matched.insert(data_node);

    flag = unKernel_Match(is_query_another,data_node_another,query,data,index,*this);
    if(!flag) return flag;
    this->kernel_matched.insert(is_query_another);
    this->matched.insert(data_node_another);

    return flag;
}


bool Match::verification(){
    for(int i = 0;i<this->match_table.size();++i){
        if(this->kernel_matched.count(i) != 0) continue;
        auto it = match_table[i].begin();
        while(it != match_table[i].end()){
            if(this->matched.count(*it) != 0){
                it = this->match_table[i].erase(it);
            } else{
                ++it;
            }
        }
        if(this->match_table[i].empty()) return false;
    }
    return true;
}

void Match::insert_res(){
    if(verification()){
        this->res.push_back(this->match_table);
    }
}


