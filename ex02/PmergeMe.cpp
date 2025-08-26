#include "PmergeMe.hpp"


PmergeMe::PmergeMe(){
    this->size = 0;
}
PmergeMe::~PmergeMe(){

}

PmergeMe::PmergeMe(const PmergeMe &other){
    this->v_array = other.v_array;
    this->d_array = other.d_array;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
    if (this != &other){
        this->v_array = other.v_array;
        this->d_array = other.d_array;
    }
    return (*this);
}

int PmergeMe::getSize() const{
    return (this->size);
}
void PmergeMe::setSize(int size){
    this->size = size;
}
std::vector<std::pair<long, long> > PmergeMe::getVarray() const{
    return (this->v_array);
}

bool ComparePairFirst(long a, long b){
    return (a > b);
}
std::vector<int> PmergeMe::getVectorGreaters(){
    std::vector<int> my_vect;
    std::vector<std::pair<long, long> >::iterator it;
    for (it = this->v_array.begin(); it != this->v_array.end(); ++it){
        int value = static_cast<int>(it->first);
        my_vect.push_back(value);
    }
    return (my_vect);
}
std::vector<int> PmergeMe::getVectorLowest(){
    std::vector<int> my_vect;
    std::vector<std::pair<long, long> >::iterator it;
    for (it = this->v_array.begin(); it != this->v_array.end(); ++it){
        if (it->second != LONG_MAX)
        {
            int value = static_cast<int>(it->second);
            my_vect.push_back(value);
        }
    }
    return (my_vect);
}

void PmergeMe::sortVectorPairs(void){
    std::vector<std::pair<long, long> >::iterator it;
    for (it = this->v_array.begin(); it != this->v_array.end(); ++it){
        if (!ComparePairFirst (it->first, it->second) && it->second != LONG_MAX){
            std::swap(it->first, it->second);
        }
    }
}

void PmergeMe::makePairs(){
    std::vector<int>::iterator it;
    for (size_t i = 0; (i + 1) < this->tmp_rray.size(); i += 2){ 
        this->v_array.push_back(std::make_pair(this->tmp_rray[i], this->tmp_rray[i + 1]));
        this->d_array.push_back(std::make_pair(this->tmp_rray[i], this->tmp_rray[i + 1]));
    }
    if ((this->tmp_rray.size() % 2))
    {
        this->v_array.push_back(std::make_pair(this->tmp_rray[this->tmp_rray.size() - 1], LONG_MAX));
        this->d_array.push_back(std::make_pair(this->tmp_rray[this->tmp_rray.size() - 1], LONG_MAX));
    }
}
bool PmergeMe::checkInteger(std::vector<std::string> vec){
    for (size_t i = 0; i < vec.size(); i++)
    {
        int number;
        std::istringstream iss1(vec[i]);
        if (!(iss1 >> number) || !(iss1.eof())){
            return (1);
        }
        if (number < 0){
            return (1);
        }
        this->tmp_rray.push_back(number);
        setSize(getSize() + 1);
    }
    return (0);
}


void PmergeMe::swapPairs(std::pair<long, long> &p1, std::pair<long, long> &p2){
    std::pair<long, long> tmp;
    tmp = p1;
    p1 = p2;
    p2 = tmp;
}

void PmergeMe::vectorMerge(int left, int middle, int right) {
    int number1 = middle - left + 1;
    int number2 = right - middle;

    std::vector<std::pair<long, long> > leftV(number1), rightV(number2);

    for (int i = 0; i < number1; i++) {
        leftV[i] = this->v_array[left + i];
    }
    for (int i = 0; i < number2; i++) {
        rightV[i] = this->v_array[middle + 1 + i];
    }

    int i = 0, j = 0, k = left;

    while (i < number1 && j < number2) {
        if (leftV[i].first <= rightV[j].first) {
            this->v_array[k] = leftV[i];
            i++;
        } else {
            this->v_array[k] = rightV[j];
            j++;
        }
        k++;
    }

    while (i < number1) {
        this->v_array[k] = leftV[i];
        i++;
        k++;
    }

    while (j < number2) {
        this->v_array[k] = rightV[j];
        j++;
        k++;
    }
}

void PmergeMe::vectorMergeSort(int left, int right){
    if (left >= right){
        return ;
    }
    int middel = left + (right - left) / 2;

    vectorMergeSort(left, middel);
    vectorMergeSort(middel + 1, right);
    vectorMerge(left, middel, right);
}

int PmergeMe::Jacobsthal(int k) {
    if (k == 0)
        return 0;
    else if (k == 1) 
        return 1;
    return Jacobsthal(k - 1) + 2 * Jacobsthal(k - 2);
}
std::vector<int> PmergeMe::vectorJacobsthal(int size) {
    std::vector<int> indices;
    int k = 2;

    while (true) {
        int index = Jacobsthal(k);

        if (index >= size)
            break;

        indices.push_back(index);
        ++k;
    }

    std::reverse(indices.begin(), indices.end());
    return indices;
}

void PmergeMe::insertVectorNumber(std::vector<int>& main_chain, const std::vector<int>& pend_chain, int index){
    int value = pend_chain[index];
    std::vector<int>::iterator pos = std::lower_bound(main_chain.begin(), main_chain.end(), value);
    main_chain.insert(pos, value);
}

void PmergeMe::vectorInsertSort(std::vector<int>& main_chain, std::vector<int>& pend_chain) {
    if (pend_chain.empty())
        return;
    
    int size = static_cast<int>(pend_chain.size());
    std::vector<int> indices = vectorJacobsthal(size);
    std::vector<bool> inserted(size, false); 
    
    for (std::size_t i = 0; i < indices.size(); i++) {
        int index = indices[i];
        if (index < size && !inserted[index]) {
            insertVectorNumber(main_chain, pend_chain, index);
            inserted[index] = true;
        }
    }
    
    for (int i = 0; i < size; i++) {
        if (!inserted[i]) {
            insertVectorNumber(main_chain, pend_chain, i);
            inserted[i] = true;
        }
    }
}

void PmergeMe::Desplaytime(double time, std::size_t size){ 
    std::cout << "Time to process a range of " << size 
        << " elements with std::[..] : " << std::fixed << std::setprecision(5) << time << " us" << std::endl;
}

void PmergeMe::DesplayNumbers(std::string str){
    if (getSize() <= 5)
    {
        std::cout << str << ":";
        std::vector<std::pair<long, long> >::iterator it;
        for (it = this->v_array.begin(); it != this->v_array.end(); ++it){
            std::cout << " " << it->first;
            if (it->second != LONG_MAX){
                std::cout << " " << it->second;
            }
        }
        std::cout << std::endl;
    }
    else{
        int i;
        std::cout << str << ":";
        for (i = 0; i < 2; i++){
            std::cout << " " << getVarray()[i].first;
            if (getVarray()[i].second != LONG_MAX){
                std::cout << " " << getVarray()[i].second;
            }
        }
        std::cout << " [...]" << std::endl;
    }
}
void PmergeMe::DesplayNumbers(std::vector<int> arr, std::string str){
    if (getSize() <= 5)
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
void PmergeMe::vectorGenerate(PmergeMe &obj){
    clock_t start = clock(); 
    obj.sortVectorPairs();
    obj.vectorMergeSort(0, getVarray().size() - 1);
    std::vector<int> mainchain = getVectorGreaters();
    std::vector<int> pendchain = getVectorLowest();
    obj.vectorInsertSort(mainchain, pendchain);
    clock_t end = clock();
    double duration_us = (static_cast<double>((end - start)) / CLOCKS_PER_SEC) * 1000000;
    
    obj.DesplayNumbers(mainchain, "After");
    Desplaytime(duration_us, getSize());
}






std::deque<std::pair<long, long> > PmergeMe::getDarray() const{
    return (this->d_array);
}
void PmergeMe::dequeinsertSort(std::deque<int>& main_chain, const std::deque<int>& pend_chain){
    int size = static_cast<int>(pend_chain.size());
    std::deque<int> indices =  dequeJacobsthal(size - 1);
    for (std::size_t i = 0; i < indices.size(); i++){
        int index = indices[i];
        if (index < size){
            insertDequeNumber(main_chain, pend_chain, index);
        }
    }
    for (std::size_t i = 0; i < pend_chain.size(); i++){
        if (std::find(indices.begin(), indices.end(), i) == indices.end()){
            insertDequeNumber(main_chain, pend_chain, i);
        }
    }
}

void PmergeMe::sortDequePairs(void){
    std::deque<std::pair<long, long> >::iterator it;
    for (it = this->d_array.begin(); it != this->d_array.end(); ++it){
        if (!ComparePairFirst (it->first, it->second) && it->second != LONG_MAX){
            std::swap(it->first, it->second);
        }
    }

}

void PmergeMe::insertDequeNumber(std::deque<int> &main_chain, const std::deque<int> &pend_chain, int index){
    int value = pend_chain[index];
    std::deque<int>::iterator pos = std::lower_bound(main_chain.begin(), main_chain.end(), value);
    main_chain.insert(pos, value);
}

void PmergeMe::dequeInsertSort(std::deque<int>& main_chain, std::deque<int>& pend_chain){
    int size = static_cast<int>(pend_chain.size());
    std::deque<int> indices =  dequeJacobsthal(size - 1);
    for (std::size_t i = 0; i < indices.size(); i++){
        int index = indices[i];
        if (index < size){
            insertDequeNumber(main_chain, pend_chain, index);
        }
    }
    for (std::size_t i = 0; i < pend_chain.size(); i++){
        if (std::find(indices.begin(), indices.end(), i) == indices.end()){
            insertDequeNumber(main_chain, pend_chain, i);
        }
    }
}
std::deque<int> PmergeMe::getDequeLowest(){
    std::deque<int> my_vect;
    std::deque<std::pair<long, long> >::iterator it;
    for (it = this->d_array.begin(); it != this->d_array.end(); ++it){
        if (it->second != LONG_MAX)
        {
            int value = static_cast<int>(it->second);
            my_vect.push_back(value);
        }
    }
    return (my_vect);
}
std::deque<int> PmergeMe::getDequeGreaters(){
    std::deque<int> my_vect;
    std::deque<std::pair<long, long> >::iterator it;
    for (it = this->d_array.begin(); it != this->d_array.end(); ++it){
        int value = static_cast<int>(it->first);
        my_vect.push_back(value);
    }
    return (my_vect);
}

void PmergeMe::dequeMerge(int left, int middle, int right) {
    int number1 = middle - left + 1;
    int number2 = right - middle;

    std::deque<std::pair<long, long> > leftV(number1), rightV(number2);

    for (int i = 0; i < number1; i++) {
        leftV[i] = this->v_array[left + i];
    }
    for (int i = 0; i < number2; i++) {
        rightV[i] = this->v_array[middle + 1 + i];
    }

    int i = 0, j = 0, k = left;

    while (i < number1 && j < number2) {
        if (leftV[i].first <= rightV[j].first) {
            this->v_array[k] = leftV[i];
            i++;
        } else {
            this->v_array[k] = rightV[j];
            j++;
        }
        k++;
    }

    while (i < number1) {
        this->v_array[k] = leftV[i];
        i++;
        k++;
    }

    while (j < number2) {
        this->v_array[k] = rightV[j];
        j++;
        k++;
    }
}

void PmergeMe::dequeMergeSort(int left, int right){
    if (left >= right){
        return ;
    }
    int middel = left + (right - left) / 2;

    dequeMergeSort(left, middel);
    dequeMergeSort(middel + 1, right);
    dequeMerge(left, middel, right);
}

std::deque<int> PmergeMe::dequeJacobsthal(int size){
    std::deque<int> indices;
    int k = 1;

    while (true) {
        int index = Jacobsthal(k);

        if (index >= size)
            break;

        indices.push_back(index);
        ++k;
    }

    std::reverse(indices.begin(), indices.end());
    return indices;
}
void PmergeMe::dequeGenerate(PmergeMe &obj){
    clock_t start = clock(); 
    obj.sortDequePairs();
    obj.dequeMergeSort(0, getDarray().size() - 1);
    std::deque<int> mainchain = getDequeGreaters();
    std::deque<int> pendchain = getDequeLowest();
    obj.dequeinsertSort(mainchain, pendchain);
    clock_t end = clock(); 
    double duration_us = static_cast<double>((end - start)) / CLOCKS_PER_SEC * 1000000;
    Desplaytime(duration_us, getSize());
}