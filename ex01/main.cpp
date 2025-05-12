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

#include "RPN.hpp"

int main(int ac, char **av){
    try{
        RPN OBJ;
        if (ac != 2)
            throw "Invalid Number Of Parameters";
        std::string input = av[1];
        OBJ.parsInput(input);
        int res = OBJ.clculateValue(input);
        std::cout << res << std::endl;
    }catch (const char *str){
        std::cout << "Error: " << str << std::endl;
    }
}
        