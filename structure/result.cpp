#include "result.h"
#include <iostream>

Result Result:: operator+(vector<vector<list<VertexID>>> &rr){
    this->res.insert(res.end(),rr.begin(),rr.end());
    return *this;
}

void Result::print_res() {
    cout<<"res=================="<<endl;
    for(auto i: res){
        for(auto j : i){
            cout<<"(";
            for(auto k : j){
                cout<<k<<" ";
            }
            cout<<")";
        }
        cout<<endl<<"====================="<<endl;
    }
}
void Result::do_get_res_split(Graph &query,vector<VertexID> &temp,unordered_set<VertexID> &matched, int num,int local){
    if(num==query.vNum){
        this->res_split.push_back(temp);
        return;
    }
    if(query.kernel->kernel_set.count(num) != 0){
        auto value =this->res[local][num].front();
        temp[num] = value;
        ++num;
        do_get_res_split(query,temp,matched,num,local);
        --num;
        temp[num] = -1;
    } else{
        for(auto& e: this->res[local][num]){
            if(matched.count(e) != 0) continue;
            temp[num] = e;
            matched.insert(e);
            ++num;
            do_get_res_split(query,temp,matched,num,local);
            --num;
            matched.erase(e);
            temp[num] = -1;
        }
    }

}
void Result::get_res_split(Graph &query) {
    for(int i = 0;i<this->res.size();++i){
        vector<VertexID> temp(query.vNum,-1);
        unordered_set<VertexID> matched;
        for(auto id: query.kernel->kernel_set){
            matched.insert(res[i][id].front());
        }
        do_get_res_split(query,temp,matched,0,i);
    }
}

void Result::print_res_split() {
    cout<<"res_split=================="<<endl;
    for(auto i: res_split){
        for(auto j : i){
            cout<<"(";
                cout<<j;
            cout<<") ";
        }
        cout<<endl<<"====================="<<endl;
    }
}
