#include <tbb/tbb.h>
#include <vector>
#include <iostream>

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

void print_field(std::vector<int> & field)
{
    for(auto v : field){
        std::cout << v << std::endl;
    }
}

int main(void)
{
    field_t in = make_field(FIELD_SIZE);

    field_t out(FIELD_SIZE);


    for(field_t::iterator in_it = in.begin(), out_it = out.begin(); in_it != in.end(); in_it++, out_it++){
        *out_it = *in_it / 2;
    }

    print_field(in);
    std::cout << "=============================================================" << std::endl;
    print_field(out);


    
    return 0;
}