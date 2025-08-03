#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <utility>
#include <climits>
#include <ctime>
#include <cmath>

class PmergeMe{
    private:
        std::vector<std::pair<long, long> > v_array;
        std::deque<std::pair<long, long> > d_array;
        std::vector<int> tmp_rray;
        int size;
    public:
        PmergeMe();
        ~PmergeMe();
        PmergeMe(const PmergeMe &other);
        PmergeMe &operator=(const PmergeMe &other);


        int getSize() const;
        void setSize(int size);
        int Jacobsthal(int k);
        void Desplaytime(double, std::size_t);
        void makePairs();
        void swapPairs(std::pair<long, long> &, std::pair<long, long> &);
        
        std::vector<std::pair<long, long> > getVarray() const;
        bool checkInteger(std::vector<std::string>);
        void sortVectorPairs(void);
        void insertVectorNumber(std::vector<int>&, const std::vector<int>&, int);
        void DesplayNumbers(std::vector<int>, std::string);
        void DesplayNumbers(std::string);
        void vectorInsertSort(std::vector<int>& , std::vector<int>& );
        std::vector<int> getVectorLowest();
        std::vector<int> getVectorGreaters();
        std::vector<int> vectorJacobsthal(int);
        void vectorGenerate(PmergeMe &obj);


        std::deque<std::pair<long, long> > getDarray() const;
        void dequeinsertSort(std::deque<int>& , const std::deque<int>& );
        void sortDequePairs(void);
        void insertDequeNumber(std::deque<int>&, const std::deque<int>&, int);
        void dequeInsertSort(std::deque<int>& , std::deque<int>& );
        std::deque<int> getDequeLowest();
        std::deque<int> getDequeGreaters();
        std::deque<int> dequeJacobsthal(int);
        void dequeGenerate(PmergeMe &obj);
        
};
#endif