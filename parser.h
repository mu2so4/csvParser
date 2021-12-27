#ifndef SUPER_CSV_PARSER_H
#define SUPER_CSV_PARSER_H

#include <fstream>
#include "tuple_io.h"

namespace csv {

    template<class... Args>
    class CSVParser {
    public:
        class Iterator {
            std::ifstream *input;
            size_t position = 0;
            std::tuple<Args...> currentRow;
        public:

            explicit Iterator(std::ifstream *in):
            input(in) {
                if(in != nullptr)
                    (*in) >> currentRow;
            }

            ~Iterator() = default;

            bool operator==(const Iterator &b) const;

            bool operator!=(const Iterator &b) const;

            Iterator &operator++();

            std::tuple<Args...> &operator*();
        };

    private:
        std::ifstream *input;

    public:
        CSVParser(std::ifstream &in, int skipCount);


        Iterator begin();

        Iterator end();
    };

    template<class... Args>
    CSVParser<Args...>::CSVParser(std::ifstream &in, int skipCount) {
        std::tuple<Args ...> row;
        std::string str;
        for (int index = 0; index < skipCount; index++)
            getline(in, str);
        input = &in;
    }

    template<class... Args>
    bool CSVParser<Args...>::Iterator::operator==(const typename CSVParser<Args...>::Iterator &b) const {
        if(input == b.input)
            return true;
        return position == b.position;
    }

    template<class... Args>
    bool CSVParser<Args...>::Iterator::operator!=(const typename CSVParser<Args...>::Iterator &b) const {
        if(input != b.input)
            return true;
        return position != b.position;
    }

    template<class... Args>
    typename CSVParser<Args...>::Iterator &CSVParser<Args...>::Iterator::operator++() {
        if(input == nullptr)
            return *this;
        (*input) >> currentRow;
        if(input->eof()) {
            input = nullptr;
            position = -1;
            return *this;
        }
        position++;
        return *this;
    }

    template<class... Args>
    std::tuple<Args...> &CSVParser<Args...>::Iterator::operator*() {
        return currentRow;
    }

    template<class... Args>
    typename CSVParser<Args...>::Iterator CSVParser<Args...>::begin() {
        return Iterator(input);
    }

    template<class... Args>
    typename CSVParser<Args...>::Iterator CSVParser<Args...>::end() {
        return Iterator(nullptr);
    }
}
#endif //SUPER_CSV_PARSER_H
