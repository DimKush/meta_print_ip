// Реализовать функцию печати условного ip-адреса.
// функция печати должна быть одной шаблонной функцией с частичными специализациями

#include <iostream>
#include <type_traits>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <tuple>

template<class T>
struct type_is{
    using type = T;
};

template<class T>
struct is_stl_container :type_is<T>{
    static constexpr bool value = false;
};

template<>
struct is_stl_container<std::vector<int>> : type_is<std::vector<int>>{
    static constexpr bool value = true;
};

template<>
struct is_stl_container<std::list<int>> : type_is<std::list<int>>{
    static constexpr bool value = true;
};

template<>
struct is_stl_container<std::string> : type_is<std::string>{
    static constexpr bool value = true;
};

template<typename T>
struct is_tuple_type : type_is<T>{
    static constexpr bool value = false;
};

template<typename ... Args>
struct is_tuple_type<std::tuple<Args...>> : type_is<std::tuple<Args...>>{
    static constexpr bool value = false;
};

template<typename T, typename ... Args>
struct is_tuple_type<std::tuple<T, Args...>> : type_is<std::tuple<T, Args...>>{
    static constexpr bool value = false;
};

template<typename T, typename ... Args>
struct is_tuple_type<std::tuple<T,T, Args...>> : type_is<std::tuple<T,T, Args...>>{
    static constexpr bool value = false;
};

template<typename T, typename ... Args>
struct is_tuple_type<std::tuple<T,T,T, Args...>> : type_is<std::tuple<T,T,T, Args...>>{
    static constexpr bool value = false;
};

template<typename T>
struct is_tuple_type<std::tuple<T,T,T,T>> : type_is<std::tuple<T,T,T,T>>{
    static constexpr bool value = true;
};


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
void print_ip(std::enable_if_t<is_tuple_type<T>::value, T> const && arg){
        std::cout << std::get<0>(arg) << ".";
        std::cout << std::get<1>(arg) << ".";
        std::cout << std::get<2>(arg) << ".";
        std::cout << std::get<3>(arg) << "\n";
}

int main(){
    print_ip<char>(-1);
    print_ip<short>(0);
    print_ip<int>(2130706433);
    print_ip<long>(8875824491850138409);

    print_ip<std::vector<int>>(std::vector<int>{10,23,4,56,5});
    print_ip<std::list<int>>(std::list<int>{115,20,41,0});
    print_ip<std::string>(std::string{"10.10.20.20"});

    print_ip<std::tuple<char, char, char, char>>(std::make_tuple('1','2','4','5'));
    print_ip<std::tuple<int, int, int, int>>(std::make_tuple(12,233,44,66));
    print_ip<std::tuple<std::string, std::string, std::string, std::string>>(std::make_tuple("155","100","10","20"));
    return 0;
}