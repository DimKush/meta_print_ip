#include <iostream>
#include <type_traits>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <tuple>

#include "meta.h"

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
