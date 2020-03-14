#include <tbb/tbb.h>
#include <vector>
#include <iostream>
#include <thread>
#include "common.hpp"


int main(void)
{

    Matrix m;
    Matrix n;

    for(int l = 0; l < NB_LEVELS; l++){
        auto &level_in = (*m.levels)[l];
        auto &level_out = (*n.levels)[l];
        tbb::parallel_for(tbb::blocked_range<int>(0, X_DIM*Y_DIM),
                          [&](tbb::blocked_range<int> &r)
        {
            for(int i = r.begin(); i < r.end(); i++){
                level_out[i] = level_in[i]*-1;
            }
        });
    }
    // m.print();
    // std::cout << "=============================================================" << std::endl;
    // n.print();

    return 0;
}