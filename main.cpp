#include <tbb/tbb.h>
#include <vector>
#include <iostream>
#include <thread>

constexpr int FIELD_SIZE = 10;
constexpr int NB_LEVELS = 7;
constexpr int X_DIM = 5;
constexpr int Y_DIM = 5;
typedef std::vector<int> field_t;
class Matrix 
{
    public:
    std::shared_ptr<std::vector<int*> > levels;
    Matrix(){
        levels.reset(new std::vector<int*>(NB_LEVELS));
        for(int i = 0; i < NB_LEVELS; i++){
            (*levels)[i] = new int[X_DIM*Y_DIM];
        }
    }
    ~Matrix(){
        for(auto &l : *levels){
            delete [] l;
        }
    }
    void print(){
        for(int level_number = 0; level_number < NB_LEVELS; level_number++){
            auto &l = (*levels)[level_number];
            std::cout << "---------- level " << level_number << " --------------" << std::endl;
            for(int i = 0; i < X_DIM; i++){
                for(int j = 0; j < Y_DIM; j++){
                    std::cout << l[i + j*X_DIM] << " ";
                }
                std::cout << std::endl;
            }
        }
    }
};

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
        auto out_p = out.data() + r.begin();
        auto in_p = in.data() + r.begin();
        for (int i=r.begin(); i<r.end(); ++i)
        {
            *out_p++ = *in_p++/2;
        }
    });

    Matrix m;
    Matrix n;

    tbb::parallel_for(tbb::blocked_range2d<int, int>(0, NB_LEVELS, 0, X_DIM*Y_DIM),
                      [&](tbb::blocked_range2d<int, int> &r)
    {
        for(int l = r.rows().begin(); l < r.rows().end() ; l++){
            auto level = (*m.levels)[l];
            auto out_level = (*n.levels)[l];
            for(int i = r.cols().begin(); i < r.cols().end(); i++){
                level[i] = i %(l+1);
                out_level[i] = level[i] - 3;
            }
        }
    });
    m.print();

    std::cout << "=============================================================" << std::endl;
    for(int l = 0; l < NB_LEVELS; l++){
        auto &level = (*m.levels)[l];
        tbb::parallel_for(tbb::blocked_range<int>(0, X_DIM*Y_DIM),
                          [&](tbb::blocked_range<int> &r)
        {
            for(int i = r.begin(); i < r.end(); i++){
                level[i] *= -1;
            }
        });
    }
    m.print();

    // tbb::parallel_for(tbb::blocked_range<int>(0, NB_LEVELS),
    //                   [&](tbb::blocked_range<int> &r)
    // {
    //     for(int i = 0; i < X_DIM*Y_DIM; i++){

    //     }
    // });
    // m.print();


    Operation print_half;

    // Works but we have no iteration index
    // so we can't control where to put things in
    // the output.
    // tbb::parallel_for_each(in.begin(), in.end(), print_half);

    // print_field(in);
    // std::cout << "=============================================================" << std::endl;
    // print_field(out);

    n.print();
    return 0;
}