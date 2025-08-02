#include "PmergeMe.hpp"

std::vector<std::string> split_input(std::string &input){
    std::stringstream ss(input);

    std::string word;
    std::vector<std::string> vec;
    while (ss >> word){
        vec.push_back(word);
    }
    return (vec);
}

int main(int ac, char **av){
    try{
        if (ac == 1)
            throw "Error";
        PmergeMe obj;
        int i = 1;
        while (av[i]){
            std::string input = av[i]; 
            std::vector<std::string> vec = split_input(input);
            if (obj.checkInteger(vec)){
                throw "Error";
            }
            i++;
        }
        obj.makePairs();
        obj.DesplayNumbers("Before");
        obj.vectorGenerate(obj);
        obj.dequeGenerate(obj);

    }catch(const char *str){
        std::cerr << str << std::endl;
    }
    return (0);
}