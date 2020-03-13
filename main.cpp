#include <tbb/tbb.h>
#include <vector>
#include <iostream>
#include <thread>

constexpr int FIELD_SIZE = 10;
typedef std::vector<int> field_t;
std::vector<int> make_field(unsigned int size)
{
    std::vector<int> out(size);
    for(auto &v : out){
        v = std::rand();
    }
    return out;
}

void print_field(std::vector<int> field)
{
    for(auto v : field){
        std::cout << v << std::endl;
    }
}

struct Operation {
    void operator()(int &i) const {
        std::cout << i/2 << std::endl;
    }
};

int main(void)
{
    field_t in = make_field(FIELD_SIZE);
    field_t out(FIELD_SIZE);

    tbb::parallel_for( tbb::blocked_range<int>(0,in.size()),
                       [&](tbb::blocked_range<int> r)
    {
        for (int i=r.begin(); i<r.end(); ++i)
        {
            out[i] = in[i]/2;
        }
    });

    Operation print_half;

    // Works but we have no iteration index
    // so we can't control where to put things in
    // the output.
    tbb::parallel_for_each(in.begin(), in.end(), print_half);

    print_field(in);
    std::cout << "=============================================================" << std::endl;
    print_field(out);

    return 0;
}