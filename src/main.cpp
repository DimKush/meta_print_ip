//
// Created by dim on 3/15/21.
//
#include <vector>
#include <algorithm>
#include <iostream>
#include <list>

template<typename isDecType>
  struct is_dec{
      using type = isDecType;
};

template<>
 struct is_dec<int>{
     using type = int;
 };

template<>
struct is_dec<long>{
    using type = long;
};

template<>
struct is_dec<short>{
    using type = short;
};

template<>
struct is_dec<char>{
    using type = unsigned char;
};



template<typename T>
void print_ip(typename is_dec<T>::type arg){
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




int main(){
    print_ip<char>(-1);
    print_ip<short>(0);
    print_ip<int>(2130706433);
    print_ip<long>(8875824491850138409);

    return 0;
}