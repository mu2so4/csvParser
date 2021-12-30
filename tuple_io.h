#ifndef SUPER_CSV_TUPLE_IO_H
#define SUPER_CSV_TUPLE_IO_H

#include <tuple>
#include <fstream>
#include <sstream>

template<std::size_t>
struct int_ {};

template<class Ch, class Tr, class Tuple, size_t Pos>
std::basic_ofstream<Ch, Tr> &print_tuple(std::basic_ofstream<Ch, Tr> &os, const Tuple &t, int_<Pos>) {
    os << std::get<std::tuple_size<Tuple>::value - Pos>(t) << '\t';
    return print_tuple(os, t, int_<Pos - 1>());
}

template<class Ch, class Tr, class Tuple>
std::basic_ofstream<Ch, Tr> &print_tuple(std::basic_ofstream<Ch, Tr> &os, const Tuple &t, int_<1>) {
    os << std::get<std::tuple_size<Tuple>::value - 1>(t);
    return os;
}

template<class Ch, class Tr, class... Args>
std::basic_ofstream<Ch, Tr> &operator<<(std::basic_ofstream<Ch, Tr> &os, const std::tuple<Args...> &t) {
    print_tuple(os, t, int_<sizeof ...(Args)>());
    return os;
}

template<class T>
std::istringstream &read_element(std::istringstream &is, T &a);

template<class T>
std::istringstream &read_element(std::istringstream &is, T &a) {
    std::string data;
    getline(is, data, ',');
    std::istringstream(data) >> a;
    if(!is)
        throw std::exception();
    return is;
}

template<>
std::istringstream &read_element(std::istringstream &is, std::string &a) {
    getline(is, a, ',');
    return is;
}


template<class Tuple, size_t Pos>
std::istringstream &read_tuple(std::istringstream &is, Tuple &t, int_<Pos>) {
    read_element(is, std::get<std::tuple_size<Tuple>::value - Pos>(t));
    return read_tuple(is, t, int_<Pos - 1>());
}

template<class Tuple>
std::istringstream &read_tuple(std::istringstream &is, Tuple &t, int_<1>) {
    read_element(is, std::get<std::tuple_size<Tuple>::value - 1>(t));
    return is;
}

template<class Ch, class Tr, class... Args>
std::basic_ifstream<Ch, Tr> &operator>>(std::basic_ifstream<Ch, Tr> &is, std::tuple<Args...> &t) {
    std::string str;
    getline(is, str);
    if(str.empty())
        return is;
    std::istringstream instr(str);
    read_tuple(instr, t, int_<sizeof ...(Args)>());

    return is;
}


#endif //SUPER_CSV_TUPLE_IO_H
