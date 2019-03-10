#include <iostream>
#include "UnionFind1.h"
#include <time.h>

using namespace std;


void testUnionFind1(int n){
    
    clock_t startTime = clock();
    UnionFind1 unionFind1 = UnionFind1(n);
    for (int i = 0; i < n; i++){
        unionFind1.find(i);
    }
    for (int i = 0; i < n -1; i++){
        unionFind1.unionElements(i, i+1);
    }
    clock_t endTime = clock();

    cout << "运行时间：" << (double)(endTime - startTime) / CLOCKS_PER_SEC << endl;
}