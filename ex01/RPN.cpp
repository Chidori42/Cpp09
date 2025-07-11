#include "RPN.hpp"

RPN::RPN(){

}
RPN::~RPN(){
    
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
            throw std::runtime_error("Invalid input");
        }
        else if (isoperator(input[i]) && isoperator(input[i + 1])){
            throw std::runtime_error("Duplicate operator");
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
                throw std::runtime_error("Invalid Operands");
            }
            char c = str[0];
            int count = 0;
            int first_element = mystack.top();
            mystack.pop();
            int secound_element = mystack.top();
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
                        throw std::runtime_error("Division by zero");
                    }
                    count = secound_element / first_element; break;
                default:
                    throw std::runtime_error("Invalid syntax");
            }
            mystack.push(count);
        }
        else
            mystack.push(std::atoi(str.c_str()));
    }
    if (mystack.size() != 1)
        throw std::runtime_error("Invalid syntax");
    int result = mystack.top();
    mystack.pop();
    return (result);
}