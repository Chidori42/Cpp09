#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <cstdlib>
#include <climits>
#include <sstream>
#include <stack>

class RPN{
    private:
        std::stack<int> mystack;
    public:
        RPN();
        ~RPN();
        RPN(const RPN &other);

        RPN &operator=(const RPN &other);
        
        std::stack<int> getMystack() const;
        int clculateValue(std::string &input);
        void parsInput(std::string &input);
};


#endif