#pragma once

#include "projects_source.h"

class Writer {
public:
    void write_json_in_file(std::string path, json new_json);
};