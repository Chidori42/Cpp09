#include "PmergeMe.hpp"

PmergeMe::PmergeMe(){

}
PmergeMe::~PmergeMe(){

}
std::vector<std::pair<long, long> > PmergeMe::getArray() const{
    return (this->array);
}

bool ComparePairFirst(long a, long b){
    return (a > b);
}

void PmergeMe::sortPairs(void){
    std::vector<std::pair<long, long> >::iterator it;
    for (it = this->array.begin(); it != this->array.end(); ++it){
        if (!ComparePairFirst (it->first, it->second) && it->second != LONG_MAX){
            std::swap(it->first, it->second);
        }
    }
}
bool PmergeMe::checkInteger(std::vector<std::string> vec, int &size){
    size_t i;
    for (i = 0; (i + 1) < vec.size(); i += 2)
    {
        int first, second;
        std::istringstream iss1(vec[i]);
        std::istringstream iss2(vec[i + 1]);
        if (!(iss1 >> first) || !(iss1.eof())){
            return (1);
        }
        if (!(iss2 >> second) || !(iss2.eof())){
            return (1);
        }
        this->array.push_back(std::make_pair(first, second));
        size += 2;
    }
    if ((vec.size() % 2))
    {
        long last;
        std::istringstream iss_last(vec[vec.size() - 1]);
        if (!(iss_last >> last) || !(iss_last.eof())){
            return (1);
        }
        this->array.push_back(std::make_pair(last, LONG_MAX));
        size += 1;
    }
    return (0);
}


void swapPairs(std::pair<long, long> &p1, std::pair<long, long> &p2){
    std::pair<long, long> tmp;
    tmp = p1;
    p1 = p2;
    p2 = tmp;
}

void PmergeMe::sortLargElements(int n){
    if (n <= 1){
        return ;
    }

    for (size_t i = 0; i + 1 < this->array.size(); ++i) {
        if (this->array[i].first > this->array[i + 1].first) {
            swapPairs(this->array[i], this->array[i + 1]);
        }
    }

    sortLargElements(n - 1);
}

void binaryInsert(std::vector<int>& main_chain, int value) {
    std::vector<int>::iterator it = std::lower_bound(main_chain.begin(), main_chain.end(), value);
    main_chain.insert(it, value);
}

int getIndex(int k) {
    return ((std::pow(2, k) + 1 + std::pow(-1, k)) / 3);
}
std::vector<int> JacobsthalInsertionOrder(int size) {
    std::vector<int> indices;
    int k = 1;

    while (true) {
        int index = getIndex(k);

        if (index >= size)
            break;

        indices.push_back(index);
        ++k;
    }

    std::reverse(indices.begin(), indices.end());
    return indices;
}

void insertNumber(std::vector<int>& main_chain, const std::vector<int>& pend_chain, int index){
    int value = pend_chain[index];
    std::vector<int>::iterator pos = std::lower_bound(main_chain.begin(), main_chain.end(), value);
    main_chain.insert(pos, value);
}

void PmergeMe::insertSort(std::vector<int>& main_chain, std::vector<int>& pend_chain) {
    int size = static_cast<int>(pend_chain.size());
    std::vector<int> indices =  JacobsthalInsertionOrder(size - 1);
    for (std::size_t i = 0; i < indices.size(); i++){
        int index = indices[i];
        if (index < size){
            insertNumber(main_chain, pend_chain, index);
        }
    }
    for (std::size_t i = 0; i < pend_chain.size(); i++){
        if (std::find(indices.begin(), indices.end(), i) == indices.end()){
            insertNumber(main_chain, pend_chain, i);
        }
    }
}

void PmergeMe::Desplaytime(long time, std::size_t size){ 
    std::cout << "Time to process a range of " << size 
        << " elements with std::[..] : " << time << " us" << std::endl;
}

void PmergeMe::DesplayNumbers(std::string str, int size){
    if (size <= 5)
    {
        std::cout << str << ":";
        std::vector<std::pair<long, long> >::iterator it;
        for (it = this->array.begin(); it != this->array.end(); ++it){
            std::cout << " " << it->first;
            if (it->second != LONG_MAX){
                std::cout << " " << it->second;
            }
        }
        if (!(size % 2)){
            std::cout << " " << it->first;
        }
        std::cout << std::endl;
    }
    else{
        std::cout << str << ":";
        for (int i = 0; i < 2; i++){
            std::cout << " " << getArray()[i].first;
            std::cout << " " << getArray()[i].second;
        }
        std::cout << " [...]" << std::endl;
    }
}
void PmergeMe::DesplayNumbers(std::vector<int> arr, std::string str, int size){
    if (size <= 5)
    {
        std::cout << str << ": ";
        std::vector<int>::iterator it;
        for (it = arr.begin(); it != arr.end(); ++it){
            std::cout << " " << *it;
        }
        std::cout << std::endl;
    }
    else{
        std::cout << str << ": ";
        for (int i = 0; i < 4; i++){
            std::cout << " " << arr[i];
        }
        std::cout << " [...]" << std::endl;
    }
}