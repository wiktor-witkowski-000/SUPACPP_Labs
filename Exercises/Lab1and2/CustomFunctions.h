#include<vector>
#include <string>
#include <iostream>
#include <fstream>
#include<sstream>

#pragma once

template<typename... Args>
void print(Args&&... args)
{
    (std::cout << ... << args) << std::endl;
}

std::vector<std::pair<float, float>> ReadData(const std::string&);

void printnlines(const std::vector<std::pair<float,float>>&);

std::vector<float> magnitudevecpair(const std::vector<std::pair<float,float>>&);

std::string leastsquares(std::vector<std::pair<float, float>>&, std::vector<std::pair<float, float>>&);

float power(float, int);

std::vector<float> xpowery_recursion(const std::vector<std::pair<float,float>>&, size_t, std::vector<float>&);

std::vector<float> xpowery(const std::vector<std::pair<float,float>>&);

void savetofile(const std::vector<float>&, const std::string&);

void savetofile(const std::string&, const std::string&);

std::string makefilename(int);
