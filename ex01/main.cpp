
#include "RPN.hpp"

int main(int ac, char **av){
    try{
        RPN OBJ;
        if (ac != 2)
            throw std::runtime_error("Invalid Number Of Parameters");
        std::string input = av[1];
        OBJ.parsInput(input);
        int res = OBJ.clculateValue(input);
        std::cout << res << std::endl;
    }catch (std::exception const &e){
        std::cerr << e.what() << std::endl;
    }
}
        