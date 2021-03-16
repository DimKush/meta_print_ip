//
// Created by dim on 3/15/21.
//
#include <vector>
#include <algorithm>
#include <iostream>
#include <list>
#include <type_traits>

template<typename isDecType>
  struct type_is{
      using type = isDecType;
};

template<typename T>
struct is_dec : type_is<T> {};

template<>
 struct is_dec<int> : type_is<int>{
     using type = int;
 };

template<>
struct is_dec<long> : type_is<long>{};

template<>
struct is_dec<short> : type_is<short>{};

template<>
struct is_dec<char> : type_is<char>{};


template<int num, typename T>
struct check_type : type_is<T>{};

template<typename T>
struct check_type<1,T> : type_is<is_dec<T>>{};


template<typename T, typename dec_type = check_type<1,T>>
void print_ip(dec_type arg){
    std::vector<int> ipAddress;
    for(auto i = 0, bytes_shift = 8 ; i < sizeof(typename is_dec<T>::type) ; i++){
        if(i == 0)
            ipAddress.emplace_back(arg & 0xFF);
        else{
            ipAddress.emplace_back((arg >> bytes_shift) & 0xFF);
            bytes_shift += 8;
        }
    }

    std::reverse(ipAddress.begin(),ipAddress.end());

    for(auto i = 0; i < ipAddress.size(); i++){
        std::cout << ipAddress.at(i);

        if(i < ipAddress.size() - 1)
            std::cout << ".";
    }

    std::cout << std::endl;
}


//template<typename T, typename container_type = check_type<2,T>>
//void print_ip(container_type arg){}



int main(){
    print_ip<char>(-1);
    print_ip<short>(0);
    print_ip<int>(2130706433);
    print_ip<long>(8875824491850138409);
    //print_ip<char*>("8875824491850138409");
    //print_ip<std::vector<int>>(std::vector<int>{10,23,4,56,5});

    return 0;
}