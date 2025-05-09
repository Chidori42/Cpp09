/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:14:08 by ael-fagr          #+#    #+#             */
/*   Updated: 2025/05/07 16:55:30 by ael-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm> 
#include <string>
#include <map>

class Data{
    private:
        std::map<std::string, float> array;
    public:
        Data(){
        }
        ~Data(){

        }
        std::string trimString(std::string str) {
            str.erase(std::remove_if(str.begin(), str.end(), ::isspace), str.end());
            return (str);
        }
        float toFloat(const std::string& str) {
            std::istringstream iss(str);
            float result;
            iss >> result;
            return result;
        }
        std::map<std::string, float>getArray(){
            return (this->array);
        }
        std::size_t countAmount(float btc_price, float amount){
            return (btc_price * amount);
        }
        void divideString(std::string str, std::string &date, float &number){
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
                // std::cout << "date = " << date << " number = " << number << std::endl;
        }
        void DisplayData(std::string date, float amount, std::size_t res){
            std::cout << date << " => " << amount << " = " << res << std::endl;
        }
        void compareData(std::string inputFile){
            std::ifstream File(inputFile);
            if (!File)
                throw "Error: could not open file.";
            std::string line;
            while (std::getline(File, line)){
                std::string date;
                float number;
                divideString(line, date, number);
                std::map<std::string, float> array = getArray();
                std::map<std::string, float>::iterator it;
                for (it = array.begin() ; it != array.end(); ++it){
                    if (it->first == "2011-01-03"){
                        DisplayData(date, number, countAmount(it->second, number));
                        break;
                    }
                    // std::cout << "Was Here" << std::endl;
                }
                
            }
        }
        std::size_t getSize(){
            return (this->array.size());
        }
        void DisplayData() {
            std::map<std::string, float> array = getArray();
            std::map<std::string, float>::iterator it;
            for (it = array.begin() ; it != array.end(); ++it){
                std::cout << "key = " << it->first << ", value = " << it->second << std::endl;
            }
        }
        void setArray(std::ifstream &server){
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
        void insertElemen(std::string str, float price){
            this->array[str] = price;
        }
};



int main(int ac, char **av){
    try{
        Data myData;
        if (ac != 2)
            throw "Error: could not open file.";
        std::string inputFile = av[1];
        std::ifstream server("data.csv");
        if (!server)
            throw "Error: could not open file.";
        myData.setArray(server);
        myData.compareData(inputFile);
        // myData.DisplayData();
        std::cout << "size = " << myData.getSize() << std::endl;
        
    }catch (const char *str){
        std::cout << str << std::endl;
    }
}
        