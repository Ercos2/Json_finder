#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <thread>
#include <mutex>
#include <nlohmann/json.hpp>
//#include "nlohmann/json.hpp"

using json = nlohmann::json;
//using namespace std;

struct RelativeIndex{
    size_t doc_id;
    float rank;
    RelativeIndex(size_t new_doc_id, float new_rank) : doc_id(new_doc_id), rank(new_rank) {};
    bool operator ==(const RelativeIndex& other) const { //overload for correct work with tests
        return (doc_id == other.doc_id && rank == other.rank);
    }
    bool operator <(const RelativeIndex& other) const { //overload for correct operation with the sort function
        return rank > other.rank; //sorting should go in the opposite direction
    }
};

struct Entry {
public:
    size_t doc_id, count;
    Entry(){};
    Entry(size_t new_doc_id, size_t new_count) {
        doc_id = new_doc_id;
        count = new_count;
    }

    bool operator ==(const Entry& other) const {
        return (doc_id == other.doc_id &&
                count == other.count);
    }
};

#include "exception_source.h"
//#include "inverted_index.h"
//#include "converter_JSON.h"
//#include "search_server.h"
