#pragma once

#include "projects_source.h"

class my_exception_with_str : public std::exception {
protected:
    const std::string what_str;
public:
    my_exception_with_str(std::string new_what_str) : what_str(new_what_str){};
    const char* what() const noexcept override {
        return what_str.c_str();
    }
};

class non_file : public my_exception_with_str {
public:
    non_file(std::string new_file_type) : my_exception_with_str(new_file_type + " file is missing!\n") {}
};

class non_key : public my_exception_with_str {
public:
    non_key(std::string new_file_type) : my_exception_with_str("key \"" + new_file_type + "\" is missing!\n") {}
};

class non_word : public my_exception_with_str {
public:
    non_word(std::string word) : my_exception_with_str("word \"" + word + "\" not found!\n") {}; 
};