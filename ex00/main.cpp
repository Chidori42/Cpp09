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
#include <map>


int main(int ac, char **av){
    
    try{
        if (ac != 2)
            throw "Error: could not open file.";
        std::string file = av[1];
        std::ifstream inputfile(file);
        if (!inputfile)
            throw "Error: could not open file.";
        
        std::string line;
        std::map<std::string, std::string> data;
        while (std::getline(inputfile, line)){
            std::stringstream ss(line);
            int count = 0;
            std::string sep = "|";
            while (ss >> sep){
                // std::cout << ss << std::endl;
                count++;
            }
            if (count > 2)
                std::cout << "Invalid Separator" << " count = " << count<< std::endl;
            // std::cout << line << std::endl;
        }
        // std::map<int, std::string>   data;
        // data.insert({1, "hello"});
        // data.insert({2, "hello"});
        // data.insert({3, "hello"});
        // data.insert({4, "hello"});
        
        // std::map<int, std::string>::iterator it;
        // for(it = data.begin(); it != data.end(); ++it){
        //     std::cout << it->first << " : " << it->second << std::endl;
        // }
        
    }catch (const char *str){
        std::cout << str << std::endl;
    }
}