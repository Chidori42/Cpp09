#ifndef BITCOINEXCHANG_HPP
#define BITCOINEXCHANG_HPP

#include <iostream>
#include <cstring>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <algorithm> 
#include <string>
#include <map>
#include <stdlib.h>
class Data{
    private:
        std::map<std::string, double> array;
    public:
        Data();
        ~Data();
        Data(const Data &other);

        Data &operator=(const Data &other);

        std::map<std::string, double>getArray();
        void setArray(std::ifstream &server);

        std::string trimString(std::string str);
        double toFloat(const std::string str);
        double countAmount(double btc_price, double amount);
        bool divideString(std::string str, std::string &date, double &number);
        bool InvalidDate(std::string date);
        void DisplayData(std::string date, double amount, double res);
        void compareData(std::string inputFile);
        std::size_t getSize();
        void insertElemen(std::string str, double price);
};


#endif