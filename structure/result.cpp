#include "result.h"
#include <iostream>

Result Result:: operator+(vector<vector<vector<VertexID>>> &rr){
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
