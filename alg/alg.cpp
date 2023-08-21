#include "alg.h"
bool com_Match(multiset<int> &queryNode,multiset<int> &dataNode){
    // dataNode 包含 querNode
    return includes(dataNode.begin(),dataNode.end(),queryNode.begin(),queryNode.end());
}

void preProsessing(Graph &query, Graph &data,Index &index){
    for(VertexID data_node = 0; data_node<data.vNum; ++data_node){
        auto label_set = query.kernel->index_kernel_label[data.node_label[data_node]];
        for(VertexID query_node: label_set){
            //度不满足匹配条件
            if(query.node_degree[query_node] > data.node_degree[data_node]){
                continue;
            }
            if(com_Match(query.neighbor_label[query_node],data.neighbor_label[data_node])){
                //满足完全匹配基本条件
                index.com_index[data_node].insert(query_node);
            }
        }
    }
}

void updateIndex(VertexID node, VertexID nei ,Graph &query, Graph &data, Index &index){
    data.neighbor_label[node].insert(data.node_label[nei]);
    data.node_adj[node].insert(nei);
    data.index_nei_label[node][data.node_label[nei]].insert(nei);

    auto label_set = query.kernel->index_kernel_label[data.node_label[node]];
    auto c_index = index.com_index[node];
    for(auto i:label_set){
        if(c_index.find(i)==c_index.end() && com_Match(query.neighbor_label[i],data.neighbor_label[node])){
            index.com_index[node].insert(i);
        }
    }
}

void Kernel_Match(Graph &query, Graph &data, Index &index, Match &match,VertexID query_exc, VertexID data_exc){
    if (match.count == match.kernel_path.size()) {
//        if(query_exc == -1 || match.match_table[query_exc][0] != data_exc){
//            match.res.push_back(match.match_table);
//        }
        match.res.push_back(match.match_table);
        return;
    }
    VertexID is_query = match.kernel_path[match.count].first;
    VertexID next = match.kernel_path[match.count].second;
    for (auto m_id: match.match_table[is_query]) {
        for (auto i: data.node_adj[m_id]) {
            if (data.node_label[i] != query.node_label[next]  ||  index.com_index[i].find(next) == index.com_index[i].end() || (query_exc == next && data_exc == i)) {
                continue;
            }
            auto old_match = match.match_table;
            ++match.count;
            match.match_table[next].push_back(i);
            bool flag = false;
            if(match.kernel_matched.count(next) == 0 ){
                flag = unKernel_Match(next,i,query,data,index,match);

            }
            if(flag){
                match.kernel_matched.insert(next);
                Kernel_Match(query, data, index,match,query_exc,data_exc);
                match.kernel_matched.erase(next);
                --match.count;
                match.match_table = old_match;
            } else{
                --match.count;
                match.match_table[next].pop_back();
            }

        }
    }

}

bool unKernel_Match(VertexID is_query,VertexID data_node, Graph &query, Graph &data, Index &index, Match &match){
    auto unkernel_set = query.kernel->neighbor_unkernel[is_query];
    for(VertexID qid: unkernel_set){
        vector<VertexID> temp;
        for (auto i: data.node_adj[data_node]) {
            if (data.node_label[i] != query.node_label[qid] ){
                continue;
            }
            temp.push_back(i);
        }
        if(temp.empty()) return false;
        if (match.match_table[qid].empty()) {
            match.match_table[qid] = temp;
        } else {
            vector<int> change;
            set_intersection(match.match_table[qid].begin(), match.match_table[qid].end(), temp.begin(),
                             temp.end(), back_inserter(change));
            if (change.empty()) return false;
            match.match_table[qid] = {change.begin(),change.end()};
        }
    }
    return true;
}

void subgraph_Match(VertexID left_node,VertexID right_node,Graph &query,Graph &data, Index &index, Result &result){
    VertexLabel left_label = data.node_label[left_node];
    VertexLabel right_label = data.node_label[right_node];
//    if(data.node_label[left_node]==data.node_label[right_node]){
//        //考虑等价->同构
//    }
    set<pair<VertexID,VertexID>> match_edge;
    auto it = query.edge_count.find({left_label,right_label});
    if(it != query.edge_count.end()){
        do_submatch(it->second,left_node,right_node,query,data,index,result);
    } else{
        it = query.edge_count.find({right_label,left_label});
        if(it != query.edge_count.end()){
            do_submatch(it->second,right_node,left_node,query,data,index,result);
        } else{
            return;
        }
    }


}

bool do_main(VertexID a,VertexID b,Graph &query, Graph &data,Index &index){
    clock_t begin,end;
    double elapsedTime;
    begin = clock();
    updateIndex(a,b,query,data,index);
    updateIndex(b,a,query,data,index);
    Result *res = new Result();
    subgraph_Match(a,b,query,data,index,*res);
    res->print_res();
    end = clock();
    elapsedTime = static_cast<double>(end-begin) / CLOCKS_PER_SEC;
    cout<<"elapsedTime:"<<elapsedTime<<endl;
    if(!res->res.empty()){
        delete res;
        return true;
    } else{
        delete res;
        return false;
    }
//    match->print_res();

}
void do_submatch(set<pair<VertexID,VertexID>> &match_edge,VertexID first,VertexID second,Graph &query,Graph &data, Index &index, Result &result){
    vector<pair<VertexID , VertexID>> should_match;
    auto com_first = index.com_index[first];
    auto com_second = index.com_index[second];
    for(auto edge:match_edge){
        if(com_first.find(edge.first)!=com_first.end() || com_second.find(edge.second)!=com_second.end()){
            should_match.emplace_back(edge);
        }
    }
    for(auto edge: should_match){
        bool left_is_kernel = query.kernel->kernel_set.find(edge.first) != query.kernel->kernel_set.end();
        bool right_is_kernel = query.kernel->kernel_set.find(edge.second) != query.kernel->kernel_set.end();
        bool ff;
        if(left_is_kernel && right_is_kernel){
            Match mm;
            ff = mm.set_Match_double(query,data,index,edge.first,first,edge.second,second);
            if(ff){
                Kernel_Match(query,data,index,mm,-1,-1);
                result = result + mm.res;
            }

            Match m1 ;
//            ff = m1.set_Match_exc(query,data,index,edge.first,first,second);
            ff = m1.set_Match_exc(query,data,index,edge.first,first,second);
            if(ff){
//                Kernel_Match(query,data,index,m1,edge.second,second);
                Kernel_Match(query,data,index,m1,edge.second,second);
                result = result + m1.res;
            }

            Match m2 ;
            ff = m2.set_Match_exc(query,data,index,edge.second,second,first);
            if(ff){
//                Kernel_Match(query,data,index,m2,edge.first,first);
                Kernel_Match(query,data,index,m2,edge.first,first);
                result = result + m2.res;
            }
        }else{
            if(left_is_kernel){
                Match m1 ;
                ff = m1.set_Match_single(query,data,index,edge.first,first,edge.second,second);
                if(!ff) continue;
                Kernel_Match(query,data,index,m1,-1,-1);
                result = result + m1.res;
            }else{
                Match m2 ;
                ff = m2.set_Match_single(query,data,index,edge.second,second,edge.first,first);
                if(!ff) continue;
                Kernel_Match(query,data,index,m2,-1,-1);
                result = result + m2.res;
            }
        }
    }
}