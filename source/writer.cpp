#include "writer.h"

void Writer::write_json_in_file(std::string path, json json_str) {
    std::ofstream json_stream(path);
    json_stream << json_str;
    json_stream.close();
}