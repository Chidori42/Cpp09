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

std::vector<int> getGreaters(std::vector<std::pair<long, long> > array){
    std::vector<int> my_vect;
    std::vector<std::pair<long, long> >::iterator it;
    for (it = array.begin(); it != array.end(); ++it){
        int value = static_cast<int>(it->first);
        my_vect.push_back(value);
    }
    return (my_vect);
}
std::vector<int> getLowest(std::vector<std::pair<long, long> > array){
    std::vector<int> my_vect;
    std::vector<std::pair<long, long> >::iterator it;
    for (it = array.begin(); it != array.end(); ++it){
        if (it->second != LONG_MAX)
        {
            int value = static_cast<int>(it->second);
            my_vect.push_back(value);
        }
    }
    return (my_vect);
}

int main(int ac, char **av){
    try{
        if (ac != 2)
            throw "Error";

        PmergeMe obj;
        std::string input = av[1];
        std::vector<std::string> vec = split_input(input);
        int size = 0;
        if (obj.checkInteger(vec, size))
        throw "Invalid Input!!";
        obj.DesplayNumbers("Before", size);
        obj.sortPairs();
        obj.sortLargElements(obj.getArray().size());
        std::vector<int> largeNumbers = getGreaters(obj.getArray());
        std::vector<int> LowNumbers = getLowest(obj.getArray());
        obj.insertSort(largeNumbers, LowNumbers);
        std::vector<int>::iterator it;
        // for (it = largeNumbers.begin(); it != largeNumbers.end(); ++it) {
        //     std::cout << *it << std::endl;
        // }
        obj.DesplayNumbers(largeNumbers, "After", size);

        

    }catch(const char *str){
        if (!str[0])
            return (0);
        std::cout << str << std::endl;
    }
    return (0);
}