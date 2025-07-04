#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>
#include <sstream>
#include <utility>
#include <climits>
#include <ctime>
#include <cmath>

class PmergeMe{
    private:
        std::vector<std::pair<long, long> > v_array;
        std::deque<std::pair<long, long> > d_array;
        int size = 0;
    public:
        PmergeMe();
        ~PmergeMe();

        int getSize() const;
        void setSize(int size);
        int getIndex(int k);
        void Desplaytime(long, std::size_t);
        void swapPairs(std::pair<long, long> &, std::pair<long, long> &);
        
        std::vector<std::pair<long, long> > getVarray() const;
        bool checkInteger(std::vector<std::string>);
        void sortVectorPairs(void);
        void sortVectorLargElements(int);
        void insertVectorNumber(std::vector<int>&, const std::vector<int>&, int);
        void DesplayNumbers(std::vector<int>, std::string);
        void DesplayNumbers(std::string);
        void vectorInsertSort(std::vector<int>& , std::vector<int>& );
        std::vector<int> getVectorLowest();
        std::vector<int> getVectorGreaters();
        std::vector<int> vectorJacobsthal(int);
        void merge(int, int, int);
        void mergeSort(int, int);
        void vectorGenerate(PmergeMe &obj);


        std::deque<std::pair<long, long> > getDarray() const;
        void dequeinsertSort(std::deque<int>& , const std::deque<int>& );
        void sortDequePairs(void);
        void sortDequeLargElements(int);
        void insertDequeNumber(std::deque<int>&, const std::deque<int>&, int);
        void dequeInsertSort(std::deque<int>& , std::deque<int>& );
        std::deque<int> getDequeLowest();
        std::deque<int> getDequeGreaters();
        std::deque<int> dequeJacobsthal(int);
        void dequeGenerate(PmergeMe &obj);
        
};
#endif