
#include "BitcoinExchange.hpp"
Data::Data(){
}
Data::~Data(){
}
std::string Data::trimString(std::string str) {
    str.erase(std::remove_if(str.begin(), str.end(), ::isspace), str.end());
    return (str);
}
double Data::toFloat(const std::string& str) {
    std::istringstream iss(str);
    double result;
    iss >> result;
    return result;
}
std::map<std::string, double> Data::getArray(){
    return (this->array);
}
double Data::countAmount(double btc_price, double amount){
    return (btc_price * amount);
}
void Data::divideString(std::string str, std::string &date, double &number){
    std::stringstream ss(str);
        int count = 0;
        char sep = '|';
        std::string divider;
        while (std::getline(ss, divider, sep)){
            if (count == 0){
                date = trimString(divider);
            }
            else if(count == 1){
                number = toFloat(divider);
            }
            count++;
        }
}
bool Data::InvalidDate(std::string date){
    std::stringstream ss(date);
    int count = 0;
    char sep = '-';
    std::string divider;
    double Year;
    double Month;
    double Day;
    while (std::getline(ss, divider, sep)){
        if (count == 0){
            Year = toFloat(divider);
        }
        else if(count == 1){
            Month = toFloat(divider);
        } 
        else if(count == 2){
            Day = toFloat(divider);
        }
        count++;
    }
    if (Year < 0 || Month > 12 || Month < 1 || Day < 1 || Day > 31){
        return (true);
    }
    return (false);
}
void Data::DisplayData(std::string date, double amount, double res){
    std::cout << date << " => " << amount << " = " << res << std::endl;
}
void Data::compareData(std::string inputFile){
    std::ifstream File(inputFile.c_str());
    if (!File){
        throw std::runtime_error("Error: could not open file.");
    }
    
    std::string line;
    std::string header = "date | value";

    if (!std::getline(File, line) || line != header){
        throw std::runtime_error("Error: Invalid File Header");
    }
    while (std::getline(File, line)){
        std::string date;
        double number;
        divideString(line, date, number);
        if (InvalidDate(date)){
            std::cout << "Error: bad input => " << date << std::endl;
            continue;
        }
        else if (number < 0){
            std::cout << "Error: not a positive number." << std::endl;
            continue;
        }
        else if(number > __INT_MAX__){
            std::cout << "Error: too large a number." << std::endl;
            continue;
        }
        std::map<std::string, double>::iterator it = array.lower_bound(date);
        if (it != array.end()) {
            if (it->first == date)
                DisplayData(it->first, number, countAmount(it->second, number));
            else if (it != array.begin())
            {
                --it;
                DisplayData(it->first, number, countAmount(it->second, number));
            }
            else
                std::cout << "Error: no btc yet in this date" << std::endl;
        } else {
            std::cout << "Error: no earlier date found" << std::endl;    
        }
    }
}
std::size_t Data::getSize(){
    return (this->array.size());
}
void Data::setArray(std::ifstream &server){
    std::string line;

    while (std::getline(server, line)){
        std::stringstream ss(line);
        int count = 0;
        char sep = ',';
        std::string str;
        std::string btc_date ;
        std::string btc_price ;
        while (std::getline(ss, str, sep)){
            if (count == 0){
                btc_date = str;
            }
             else if (count == 1){
                btc_price = str;
            }
            count++;
        }
        insertElemen(btc_date, toFloat(btc_price));
        if (count > 2)
            std::cout << "Invalid Separator" << " count = " << count<< std::endl;
    }
}
void Data::insertElemen(std::string str, double price){
    this->array[str] = price;
}