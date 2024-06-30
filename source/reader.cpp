#include "reader.h"

json Reader::read_json_by_key(std::string path, std::string key) {
    json jfile;
    std::ifstream json_stream(path);
    json_stream >> jfile;

    json_stream.close();
    return jfile[key];
}

int Reader::read_max_responses(std::string path) {
    json jfile;
    std::ifstream json_stream(path);
    json_stream >> jfile;
    json_stream.close();
    return jfile["config"].contains("max_responses") ? (int)jfile["config"]["max_responses"] : 5;
}

int Reader::is_key_in_json(std::string path, std::string key) {
    json jfile;
    std::ifstream json_stream(path);
    if (!json_stream.is_open()) {
        json_stream.close();
        return 2;
    }
    json_stream >> jfile;
    if (!jfile.contains(key)) {
        json_stream.close();
        return 1;
    }
    return 0;
}

bool Reader::is_file_exist(std::string path) {
    std::ifstream json_stream(path);
        if (!json_stream.is_open()) {
            std::cout << "File " << path << " open error.\n";
            json_stream.close();
            return 1;
        }
        else {
            std::cout << "File " << path << " opened\n";
            json_stream.close();
            return 0;
        }
}