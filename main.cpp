#include <iostream>
#include <fstream>
#include <ctime>
#include "structure/graph.h"
#include "structure/index.h"
#include "alg/alg.h"
using namespace std;

int main() {
    clock_t begin, end;
    double elapsedTime;
    bool flag;

//    string query_path = "../test/insert/query_graph/Q_0";
//    string data_path = "../test/insert/data_graph/data.graph";
//    string insert_path = "../test/insert/data_graph/insertion.graph";

//    string query_path = "../test/querySet";
//    string data_path = "../test/dataSet";
//    string insert_path = "../test/insert_demo";

    string query_path = "../test/simple_test/query_demo3";
    string data_path = "../test/simple_test/data_demo3";
    string insert_path = "../test/simple_test/insert_demo3";

    Graph *query = new Graph();
    query->readGraph(query_path);
    query->set_kernel();
    Graph *data = new Graph();
    data->readGraph(data_path);
    Index *index = new Index(query->vNum, data->vNum);
    preProsessing(*query, *data, *index);
    index->print_com_index();
    ifstream ifs;
    ifs.open(insert_path);
    if (!ifs.is_open()) {
        cout << insert_path << " open failed" << endl;
        exit(0);
    }


    int i = 0;
    vector<pair<int, int>> res;
    vector<int> res1;
    while (!ifs.eof()) {
        cout << i++;
        char t;
        int a, b, c;
        ifs >> t >> a >> b >> c;
        bool f = do_main(a, b, *query, *data, *index);
        if (f) {
            res1.push_back(1);
//            res.emplace_back(a,b);

        }
    }
    for (auto i: res) {
        cout << i.first << " " << i.second << endl;
    }
    cout << res1.size();
//    do_func(8816,8817,*query,*data,*index);
//    do_func(105621,227771,*query,*data,*index);
//    do_func(180767,328784 ,*query,*data,*index);

    delete query;
    delete data;
    delete index;

    return 0;
}