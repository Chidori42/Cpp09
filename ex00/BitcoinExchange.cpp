
#include "BitcoinExchange.hpp"
Data::Data(){
}
Data::~Data(){
}
Data::Data(const Data &other){
    this->array = other.array;
}
Data &Data::operator=(const Data &other){
    if (this != &other){
        this->array = other.array;
    }
    return (*this);
}
std::string Data::trimString(std::string str) {
    str.erase(std::remove_if(str.begin(), str.end(), ::isspace), str.end());
    return (str);
}

double Data::toFloat(const std::string str) {
    char *endp = NULL;
    double result = strtod(str.c_str(), &endp);

    std::string v = "exchange_rate";
    if (strlen(endp) == 0 || str == v){
        return result;
    }
    throw std::runtime_error("");
}
std::map<std::string, double> Data::getArray(){
    return (this->array);
}
double Data::countAmount(double btc_price, double amount){
    return (btc_price * amount);
}
bool isLeapYear(int year){
    return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}
int countCharacter(std::string str, char c){
    int res = 0;
    for (size_t i = 0; i < str.length(); i++)
    {
        if (str[i] == c){
            res++;
        }
    }
    return res;
}
bool Data::divideString(std::string str, std::string &date, double &number){
    try{
        std::stringstream ss(str);
        char sep = '|';
        std::string divider;
        int count = 0;
        while (std::getline(ss, divider, sep)){
            if (count == 0){
                date = trimString(divider);
            }
            else if(count == 1){
                number = toFloat(divider);
            }
            count++;
        }
        if (countCharacter(str, '|') > 1)
            throw std::runtime_error("");
    }catch (std::exception &e){
        return (false);
    }
    return (true);
}
bool Data::InvalidDate(std::string date){
    std::stringstream ss(date);
    int count = 0;
    char sep = '-';
    std::string divider;
    int Year;
    int Month;
    int Day;
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
    if (Month > 12 || Month < 1){
        return (true);
    }
    int daysMonths[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (isLeapYear(Year)){
        daysMonths[1] = 29;
    }
    if (Day < 1 || Day > daysMonths[(Month - 1)]){
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
        if (!divideString(line, date, number) || InvalidDate(date)){
            std::cout << "Error: bad input => " << date << std::endl;
            continue;
        }    
        else if (number < 0){
            std::cout << "Error: not a positive number." << std::endl;
            continue;
        }
        else if(number > 1000){
            std::cout << "Error: too large a number." << std::endl;
            continue;
        }
        std::map<std::string, double>::iterator it = array.lower_bound(date);
        if (it != array.end()) {
            if (it->first == date)
                DisplayData(date, number, countAmount(it->second, number));
            else if (it != array.begin())
            {
                --it;
                DisplayData(date, number, countAmount(it->second, number));
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