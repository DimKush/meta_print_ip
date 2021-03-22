# meta_print_ip
> Build machine : sysname='Linux', nodename='pop-os', release='5.8.0-7630-generic', machine='x86_64'
> compilers: gcc6, g++6
> Build system: Cmake v3.14

[![Build Status](https://travis-ci.org/DimKush/meta_print_ip.svg?branch=main)](https://travis-ci.org/github/DimKush/meta_print_ip)

## The main purpose

Sample C++ program to print ip addresses with types: int, char, long, short, std::vector<int>, std::list<int>, std::string and different tuple variations. The main idea is to use SFINAE method. The compiler uses different variations of function print_ip wich depends from type .
