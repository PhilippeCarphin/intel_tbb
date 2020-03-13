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

void print_field(std::vector<int> field)
{
    for(auto v : field){
        std::cout << v << std::endl;
    }
}

class Halver {
public:
    Halver(int N){
        out = new std::vector<int>();
    }
    field_t *out;
    void operator()(int n){
        out->push_back(n/2);
    }
    field_t *get_field(){
        return out;
    }
};

int main(void)
{
    field_t in = make_field(FIELD_SIZE);

    field_t out(FIELD_SIZE);


    Halver h = Halver(FIELD_SIZE);
    Halver h2 = std::for_each(in.begin(), in.end(), h);

    print_field(in);
    std::cout << "=============================================================" << std::endl;
    print_field(*h2.out);


    
    return 0;
}