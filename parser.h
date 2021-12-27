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
        public:
            std::tuple<Args...> currentRow;

            explicit Iterator(std::ifstream *in):
            input(in) {
                if(in != nullptr)
                    (*in) >> currentRow;
            }

            ~Iterator() = default;

            Iterator(const Iterator &it);

            Iterator(Iterator &&it) noexcept;

            Iterator &operator=(const Iterator &it);

            Iterator &operator=(Iterator &&it) noexcept;

            void swap(Iterator &b);

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
    CSVParser<Args...>::Iterator::Iterator(const CSVParser::Iterator &it) {
        input->close();
        input = it.input;
        position = it.position;
        currentRow = it.currentRow;
    }

    template<class... Args>
    CSVParser<Args...>::Iterator::Iterator(CSVParser::Iterator &&it) noexcept {
        input->close();
        input = it.input;
        position = it.position;
        currentRow = std::move(it.currentRow);
    }

    template<class... Args>
    typename CSVParser<Args...>::Iterator &CSVParser<Args...>::Iterator::operator=(const CSVParser::Iterator &it) {
        if (&it != this) {
            input->close();
            input = it.input;
            position = it.position;
            currentRow = it.currentRow;
        }
        return *this;
    }

    template<class... Args>
    typename CSVParser<Args...>::Iterator &CSVParser<Args...>::Iterator::operator=(CSVParser::Iterator &&it) noexcept {
        if (&it != this) {
            input->close();
            input = it.input;
            position = it.position;
            currentRow = std::move(it.currentRow);
        }
        return *this;
    }


    template<class... Args>
    void CSVParser<Args...>::Iterator::swap(typename CSVParser<Args...>::Iterator &b) {
        std::swap(input, b.input);
        std::swap(input, b.input);
        std::swap(position, b.position);
    }

    template<class... Args>
    bool CSVParser<Args...>::Iterator::operator==(const typename CSVParser<Args...>::Iterator &b) const {
        return input == b.input;
    }

    template<class... Args>
    bool CSVParser<Args...>::Iterator::operator!=(const typename CSVParser<Args...>::Iterator &b) const {
        return input != b.input;
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
