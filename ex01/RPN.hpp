#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <cstdlib>
#include <sstream>
#include <stack>

class RPN{
    private:
        std::stack<int> mystack;
    public:
        RPN();
        ~RPN();
        
        std::stack<int> getMystack() const;
        int clculateValue(std::string &input);
        void parsInput(std::string &input);
};


#endif