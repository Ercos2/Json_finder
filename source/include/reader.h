#pragma once

#include "projects_source.h"

class Reader {
public:
    int read_max_responses(std::string path);
    json read_json_by_key(std::string path, std::string key);

    int is_key_in_json(std::string path, std::string key);
    bool is_file_exist(std::string path);
};