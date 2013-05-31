//
//  query2.cpp
//  
//
//  Created by Jeremy Hyrkas on 4/17/13.
//
//

#include "two_path.h"
#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>

using namespace std;

struct tuple {
    int to;
    int from;

    bool operator<(const tuple& rhs) const {
        return to < rhs.to;
    }

    bool operator==(const tuple& rhs) const {
        return to == rhs.to && from == rhs.from;
    }
};

void query(const char* filename) {
	
    //template for reading data
    vector<vector<int> > edges = vector<vector<int> >();
	ifstream edge_file(filename);
	int count = 0;
	vector<int> tmp = vector<int>();
	while (!edge_file.eof()) {
		int j;
		edge_file >> j;
		tmp.push_back(j);
		count++;
		if (count == 2) {
			count = 0;
			edges.push_back(tmp);
			tmp = vector<int>();
		}
	}
	edge_file.close();
    //end template

    cout << "done reading file.\n";
	
	//hash on data[0]
	map<int, vector<vector<int> > > hash1;
	for (int i = 0; i < edges.size(); i++) {
		if (hash1.find(edges[i][0]) == hash1.end()) {
			hash1[edges[i][0]] = vector<vector<int> > ();
		}
		hash1[edges[i][0]].push_back(edges[i]);
	}

    cout << "done creating map.\n";

    //vector<tuple> result = vector<tuple>();
    set<tuple> d_result = set<tuple>();

    //loop over edges a,b
   // ofstream myfile;
    //myfile.open("two_path.out");
    //int total_count = 0;
    for (int i = 0; i < edges.size(); ++i) {
        //if (i % 100000 == 0) {
        //    cout << i << "\n";
        //}
        int a = edges[i][0];
        if (hash1.find(edges[i][1]) == hash1.end()) {
            continue;
        }
        vector<vector<int> > matches1 = hash1[edges[i][1]];

        //loop over match b,c
        for (int j = 0; j < matches1.size(); ++j) {
            int c = matches1[j][1];
            tuple t;
            t.to = a;
            t.from = c;
            //++total_count;
            //myfile << t.to << " " << t.from << "\n";
            d_result.insert(t);
            //result.push_back(t);
            /*ostringstream convert;
            convert << a;
            string str1 = convert.str();
            ostringstream convert2;
            convert2 << c;
            string str2 = convert2.str();
            result.insert(str1 + " " + str2);*/
        }
    }

    //cout << total_count << "\n";

    //distinct
    //for (int i = 0; i < result.size(); ++i) {
    //    d_result.insert(result[i]);
    //}

    //for (set<string>::iterator it = result.begin(); it != result.end(); ++it) {
    //    cout << *it << "\n";
    //}

    cout << "found " << d_result.size() << " distinct two-paths\n";

}

int main(int argc, const char* argv[]) {
	query(argv[1]);
}
