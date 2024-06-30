#pragma once

#include "reader.h"
#include "writer.h"

class Converter_JSON {
    Reader reader;
    Writer writer;
public:
    Converter_JSON();

    void is_json_key_correct(std::string path, std::string key);

    int get_responses_limit();
    std::vector<std::string> get_str_vec_by_key(std::string path, std::string key);

    json construct_result_func(int request_num, std::vector<RelativeIndex> vec_result);
    void write_answers(std::string path, std::vector<std::vector<RelativeIndex>>answers);
};