#pragma once

#include "projects_source.h"

class Converter_JSON {
    std::string name;
    size_t max_str;
    std::vector<std::string> paths;
    std::vector<std::string> requests;
public:
    Converter_JSON();

    void correct_config();

    std::vector<std::string> get_vector(json json_array);
    std::vector<std::string> get_text_documents();
    int get_responses_limit();
    std::vector<std::string> get_requests();

    void correct_request();
    json construct_result_func(int request_num, std::vector<RelativeIndex> vec_result);
    void put_answers(std::vector<std::vector<RelativeIndex>>answers);
};