#ifndef ENDGAME_EXCEPTION_SOURCE_H
#define ENDGAME_EXCEPTION_SOURCE_H

#include "projects_source.h"

class non_config : public exception {
public:
    const char* what() const noexcept override {
        return "config file is missing!\n";
    }
};

class non_config_key : public exception {
public:
    const char* what() const noexcept override {
        return "config file is empty!\n";
    }
};

class non_request : public exception {
public:
    const char* what() const noexcept override {
        return "request file is missing!\n";
    }
};

class non_request_key : public exception {
public:
    const char* what() const noexcept override {
        return "request file is empty!\n";
    }
};

class non_word : public exception {
public:
    const char* what() const noexcept override {
        return "word not found!\n";
    }
};

#endif //ENDGAME_EXCEPTION_SOURCE_H
