constexpr int FIELD_SIZE = 100000000;
constexpr int NB_LEVELS = 700;
constexpr int X_DIM = 500;
constexpr int Y_DIM = 500;
typedef std::vector<int> field_t;
class Matrix 
{
    public:
    std::shared_ptr<std::vector<int*> > levels;
    Matrix(){
        levels.reset(new std::vector<int*>(NB_LEVELS));
        for(int i = 0; i < NB_LEVELS; i++){
            auto int_p = new int[X_DIM*Y_DIM];
            (*levels)[i] = int_p;
            
            for(size_t j = 0; j < X_DIM*Y_DIM; j++){
                int_p[j] = j;
            }
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