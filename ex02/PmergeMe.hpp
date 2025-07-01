#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <utility>
#include <climits>
#include <ctime>
#include <cmath>

class PmergeMe{
    private:
        std::vector<std::pair<long, long> > array;
    public:
        PmergeMe();
        ~PmergeMe();

        std::vector<std::pair<long, long> > getArray() const;
        void insertSort(std::vector<int>& , const std::vector<int>& );
        bool checkInteger(std::vector<std::string>, int &);
        void sortPairs(void);
        void sortLargElements(int);
        void Desplaytime(long, std::size_t);
        void DesplayNumbers(std::vector<int>, std::string , int );
        void DesplayNumbers(std::string , int );
        void insertSort(std::vector<int>& , std::vector<int>& );
};
#endif