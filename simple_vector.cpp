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
    std::vector<int> in = make_field(FIELD_SIZE);
    std::vector<int> out(FIELD_SIZE);

    tbb::parallel_for( tbb::blocked_range<int>(0,in.size()),
                       [&](tbb::blocked_range<int> r)
    {
        auto out_p = out.data() + r.begin();
        auto in_p = in.data() + r.begin();
        for (int i=r.begin(); i<r.end(); ++i)
        {
            *out_p++ = *in_p++/2;
        }
    });

    print_field(in);
    std::cout << "=============================================================" << std::endl;
    print_field(out);

    return 0;
}