#pragma once

#include "projects_source.h"

class non_config : public std::exception {
public:
    const char* what() const noexcept override {
        return "config file is missing!\n";
    }
};

class non_config_key : public std::exception {
public:
    const char* what() const noexcept override {
        return "config file is empty!\n";
    }
};

class non_request : public std::exception {
public:
    const char* what() const noexcept override {
        return "request file is missing!\n";
    }
};

class non_request_key : public std::exception {
public:
    const char* what() const noexcept override {
        return "request file is empty!\n";
    }
};

class non_word : public std::exception {
    const std::string word;
public:
    non_word(std::string new_word) : word("word \"" + new_word + "\" not found!\n") {}; 
    const char* what() const noexcept override {
        //word = string("word " + word + " not found!\n");
        return word.c_str();
        //return "word "  word << " not found!\n";
    }
};