#include "index.h"
#include <iostream>

Index::Index(int queryNum, int dataNum) {
    com_index.resize(dataNum); //完全匹配集 数据节点索引
}

void Index::print_com_index() {
    cout<<"com_index================"<<endl;
    int n = 0;
    for (auto i: this->com_index) {
        cout<<n++<<": ";
        for (auto j: i) {
            cout<<j<<" ";
        }
        cout<<endl;
    }
    cout<<"================"<<endl;
}

