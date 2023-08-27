#include "index.h"
#include <iostream>
#include <fstream>
Index::Index(int queryNum, int dataNum) {
    com_index.resize(dataNum); //完全匹配集 数据节点索引
}

void Index::print_com_index() {
    ofstream out("../index_init.txt");
    if(!out.is_open()){
        cout<<"open failed"<<endl;
        exit(0);
    }
    cout<<"com_index================"<<endl;
    int n = 0;
    for (auto i: this->com_index) {
        out<<n<<": ";
        cout<<n++<<": ";
        for (auto j: i) {
            out<<j<<" ";
            cout<<j<<" ";
        }
        out<<endl;
        cout<<endl;
    }
    out.close();
    cout<<"================"<<endl;
}

//void Index::print_com_index() {
//    cout<<"com_index================"<<endl;
//    int n = 0;
//    for (auto i: this->com_index) {
//        cout<<n++<<": ";
//        for (auto j: i) {
//            cout<<j<<" ";
//        }
//        cout<<endl;
//    }
//    cout<<"================"<<endl;
//}
