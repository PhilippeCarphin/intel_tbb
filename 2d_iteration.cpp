#include <tbb/tbb.h>
#include <vector>
#include <iostream>
#include <thread>
#include "common.hpp"


struct Operation {
    void operator()(int &i) const {
        std::cout << i/2 << std::endl;
    }
};

int main(void)
{
    field_t in = make_field(FIELD_SIZE);
    field_t out(FIELD_SIZE);

    Matrix m;
    Matrix n;

    tbb::parallel_for(tbb::blocked_range2d<int, int>(0, NB_LEVELS, 0, X_DIM*Y_DIM),
                      [&](tbb::blocked_range2d<int, int> &r)
    {
        for(int l = r.rows().begin(); l < r.rows().end() ; l++){
            auto in_level = (*m.levels)[l];
            auto out_level = (*n.levels)[l];
            for(int i = r.cols().begin(); i < r.cols().end(); i++){
                out_level[i] = in_level[i] - 10;
            }
        }
    });
    // m.print();
    // std::cout << "=============================================================" << std::endl;
    // n.print();
    return 0;
}