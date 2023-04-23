#pragma once

#include "projects_source.h"

class Converter_JSON {
    string name;
    size_t max_str;
    vector<string> paths;
    vector<string> requests;
public:
    Converter_JSON();

    void correct_config();

    vector<string> get_vector(json json_array);
    vector<string> get_text_documents();
    int get_responses_limit();
    vector<string> get_requests();

    void correct_request();
    json construct_result_func(int request_num, vector<RelativeIndex> vec_result);
    void put_answers(vector<vector<RelativeIndex>>answers);
};