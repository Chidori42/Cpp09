/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:14:08 by ael-fagr          #+#    #+#             */
/*   Updated: 2025/07/13 20:11:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int ac, char **av){
    try{
        Data myData;
        if (ac != 2)
            throw std::runtime_error("Error: could not open file.");
        std::string inputFile = av[1];
        std::ifstream server("data.csv");
        if (!server)
            throw std::runtime_error("Error: could not open file.");
        myData.setArray(server);
        myData.compareData(inputFile);
        
    }catch (std::exception &e){
        std::cout << e.what() << std::endl;
    }
}
        