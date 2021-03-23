//
// Created by dim on 3/22/21.
//

#ifndef META_PRINT_IP_META_H
#define META_PRINT_IP_META_H

#include <iostream>
#include <type_traits>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <tuple>


/**
 * @brief Metafunction type_is
 *
 * All of the metafunctions are inherited from this structure.
 *
 * @param template<class T> type
 *
 * @return Type of object.
 */
template<class T>
struct type_is{
    using type = T;
};

/**
 * @brief Metafunction is_stl_container
 *
 * Implementation for stl containers.
 *
 * @param template<class T> type
 *
 * @return Type of object.
 */

template<class T>
struct is_stl_container :type_is<T>{
    static constexpr bool value = false;
};

/**
 * @brief Metafunction is_stl_container
 *
 * implementation for stl std::vector<int>.
 *
 * @param template<class T> type
 *
 * @return Type = std::vector<int>.
 */

template<>
struct is_stl_container<std::vector<int>> : type_is<std::vector<int>>{
    static constexpr bool value = true;
};

/**
 * @brief Metafunction is_stl_container
 *
 * implementation for stl std::list<int>.
 *
 * @param template<class T> type
 *
 * @return Type = std::list<int>.
 */

template<>
struct is_stl_container<std::list<int>> : type_is<std::list<int>>{
    static constexpr bool value = true;
};

/**
 * @brief Metafunction is_stl_container
 *
 * implementation for stl std::string.
 *
 * @param template<class T> type
 *
 * @return Type = std::string.
 */

template<>
struct is_stl_container<std::string> : type_is<std::string>{
    static constexpr bool value = true;
};

/**
 * @brief Metafunction is_tuple_type
 *
 * Implementation for std::tuple. Check that all types in std::tuple will be same.
 *
 * @param template<class T> type
 *
 * @return Type of object.
 */


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
void print_ip(T arg);

/**
 * @brief Function print_ip
 *
 * Print ip as arithmetic value.
 *
 * @param std::enable_if_t<std::is_arithmetic_v<T>, T> const && arg
 *
 */


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

/**
 * @brief Function print_ip
 *
 * Print ip as stl container.
 *
 * @param std::enable_if_t<is_stl_container<T>::value,T> const && arg
 *
 */

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

/**
 * @brief Function print_ip
 *
 * Print ip as tuple.
 *
 * @param std::enable_if_t<is_tuple_type<T>::value, T> const && arg
 *
 */

template<typename T>
void print_ip(std::enable_if_t<is_tuple_type<T>::value, T> const && arg){
    std::cout << std::get<0>(arg) << ".";
    std::cout << std::get<1>(arg) << ".";
    std::cout << std::get<2>(arg) << ".";
    std::cout << std::get<3>(arg) << "\n";
}

#endif //META_PRINT_IP_META_H
