// Реализовать функцию печати условного ip-адреса.
// функция печати должна быть одной шаблонной функцией с частичными специализациями

#include <iostream>
#include <type_traits>
#include <vector>
#include <list>
#include <string>
#include <algorithm>

template<class T>
struct type_is{
    using type = T;
};

template<class T>
struct is_stl_container :type_is<T>{
    static const bool value = false;
};

template<>
struct is_stl_container<std::vector<int>> : type_is<std::vector<int>>{
    static const bool value = true;
};

template<>
struct is_stl_container<std::list<int>> : type_is<std::list<int>>{
    static const bool value = true;
};

template<>
struct is_stl_container<std::string> : type_is<std::string>{
    static const bool value = true;
};

template<class T>
    auto is_stl_container_v = is_stl_container<T>::value;


template<typename T>
void print_ip(std::enable_if_t<std::is_arithmetic_v<T>, T> const && arg ){
    std::vector<int> ipAddress;
    for(auto i = 0, bytes_shift = 8 ; i < sizeof(T) ; i++){
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


template<typename T>
void print_ip(std::enable_if_t<is_stl_container<T>::value,T> const && arg){
    if constexpr (std::is_same_v<T, std::string>){
        std::cout << arg << std::endl;
        return;
    }

    for(auto it = arg.begin(); it != arg.end(); it++){
        if(it != std::prev(arg.end()))
            std::cout << *it << ".";
        else
            std::cout << *it << std::endl;
    }

}

template<typename T>
void print_ip(std::enable_if_t<is_stl_container<T>::value,T> const && arg){

}
int main(){
    print_ip<char>(-1);
    print_ip<short>(0);
    print_ip<int>(2130706433);
    print_ip<long>(8875824491850138409);

    print_ip<std::vector<int>>(std::vector<int>{10,23,4,56,5});
    print_ip<std::list<int>>(std::list<int>{115,20,41,0});
    print_ip<std::string>(std::string{"10.10.20.20"});


    return 0;
}