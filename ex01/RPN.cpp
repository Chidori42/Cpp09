#include "RPN.hpp"

RPN::RPN(){

}
RPN::~RPN(){
    
}
RPN::RPN(const RPN &other){
    this->mystack = other.mystack;
}

RPN &RPN::operator=(const RPN &other)
{
    if (this != &other){
        this->mystack = other.mystack;
    }
    return (*this);
}
std::stack<int> RPN::getMystack() const{
    return (this->mystack);
}
bool isoperator(char c){
    return (c == '+' || c == '-' || c == '*' || c == '/');
}
void RPN::parsInput(std::string &input){
    for (std::size_t i = 0; i < input.length(); i++){
        if (!isdigit(input[i]) && !isspace(input[i]) && !isoperator(input[i])){
            throw std::runtime_error("");
        }
        else if (isoperator(input[i]) && isoperator(input[i + 1])){
            throw std::runtime_error("");
        }
    }
}
int RPN::clculateValue(std::string &input){
    std::stringstream ss(input);
    std::string str;
    char sep = ' ';
    while (std::getline(ss, str, sep)){
        if (str == "+" || str == "-" || str == "*" || str == "/"){
            if (getMystack().size() < 2){
                throw std::runtime_error("");
            }
            double count = 0;
            char c = str[0];
            double first_element = mystack.top();
            mystack.pop();
            double secound_element = mystack.top();
            mystack.pop();
            switch (c){
                case '+':
                    count = secound_element + first_element; break;
                case '-':
                    count = secound_element - first_element; break;
                case '*':
                    count = secound_element * first_element; break;
                case '/':
                    if (first_element == 0){
                        throw std::runtime_error("");
                    }
                    count = secound_element / first_element; break;
                default:
                    throw std::runtime_error("");
            }
            if (count > INT_MAX || count < INT_MIN)
                throw std::runtime_error("");
            mystack.push(count);
        }
        else
            mystack.push(std::atoi(str.c_str()));
    }
    if (mystack.size() != 1)
        throw std::runtime_error("");
    int result = mystack.top();
    mystack.pop();
    return (result);
}