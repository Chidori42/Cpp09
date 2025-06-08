#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <utility>
#include <climits>

bool ComparePairFirst (long a, long b){
    return (a > b);
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

std::vector<int> sortPairs(std::vector<std::pair<long, long> > &array){
    long tmp;
    std::vector<std::pair<long, long> >::iterator it;
    for (it = array.begin(); it != array.end(); ++it){
        if (!ComparePairFirst (it->first, it->second) && it->second != LONG_MAX){
            tmp = it->first; 
            it->first = it->second;
            it->second = tmp;
        }
    }
    return (getGreaters(array));
}
void checkInteger(std::vector<std::string> vec, std::vector<std::pair<long, long> > &array){
    try {
        size_t i;
        for (i = 0; (i + 1) < vec.size(); i += 2)
        {
            int first, second;
            std::istringstream iss1(vec[i]);
            std::istringstream iss2(vec[i + 1]);

            if (!(iss1 >> first) || !(iss1.eof())) {
                throw std::invalid_argument(vec[i]);
            }
            if (!(iss2 >> second) || !(iss2.eof())) {
                throw std::invalid_argument(vec[i + 1]);
            }
            array.push_back(std::make_pair(first, second));

        }
        if ((vec.size() % 2))
        {
            long last;
            std::istringstream iss_last(vec[vec.size() - 1]);
            if (!(iss_last >> last) || !(iss_last.eof())) {
                throw std::invalid_argument("Invalid integer: " + vec[vec.size() - 1]);
            }
            array.push_back(std::make_pair(last, LONG_MAX));
        }
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error\nInvalid input: " << e.what() << std::endl;
        throw "";
    }
}
std::vector<std::string> split_input(std::string &input){
    std::stringstream ss(input);

    std::string word;
    std::vector<std::string> vec;
    while (ss >> word){
        vec.push_back(word);
    }
    return (vec);
}

int partition(std::vector<int>& arr, int low, int high) {
    //arr = 0 4 3 2 9
    int pivot = arr[high];
    //pivot = 9
  
    int i = low - 1;
    // i = 1
    // j = 1
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);  
    return i + 1;
}

void quickSort(std::vector<int>& arr, int low, int high) {
  
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}


int main(int ac, char **av){
    try{
        if (ac != 2)
            throw "Invalid Number Of Parameters";
        std::string input = av[1];
        std::vector<std::pair<long, long> > array;
        std::vector<std::string> vec = split_input(input);
        checkInteger(vec, array);
        std::vector<int>::iterator it;
        std::vector<int> my_array = sortPairs(array);
        quickSort(my_array, 0, my_array.size() - 1);
        for (it = my_array.begin(); it != my_array.end(); ++it)
        {
            std::cout << *it << std::endl;
        }

    }catch(const char *str){
        if (!str[0])
            return (0);
        std::cout << "Error\n" << str << std::endl;
    }
    return (0);
}