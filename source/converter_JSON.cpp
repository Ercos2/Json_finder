#include "converter_JSON.h"

Converter_JSON::Converter_JSON() = default;

void Converter_JSON::is_json_key_correct(std::string path, std::string key) {
    int flag = reader.is_key_in_json(path, key);
    if (flag == 2) 
        throw non_file(path);
    else if (flag == 1)
        throw non_key(key);
}

std::vector<std::string> Converter_JSON::get_str_vec_by_key(std::string path, std::string key) {
    std::vector<std::string> str_vec;
    json json_array = reader.read_json_by_key(path, key);
    if (key == "files") 
        for(const auto& json_str : json_array) 
            reader.is_file_exist(json_str) ? str_vec.push_back(" ") : str_vec.push_back(json_str); 
    else 
        for(const auto& json_str : json_array) 
            str_vec.push_back(json_str);
    return str_vec;
}

int Converter_JSON::get_responses_limit() {
    return reader.read_max_responses("../JSON/config.json");
}

json Converter_JSON::construct_result_func(int request_num, std::vector<RelativeIndex> vec_result) {
    json result;
    json json_pair;
    if (vec_result.size() > 1) {
        int max_str = get_responses_limit();
        for (int a = 0; a < vec_result.size() && a < max_str; ++a) {
            json_pair["relevance"].push_back({"docid", vec_result[a].doc_id});
            json_pair["relevance"].push_back({"rank", vec_result[a].rank});
        }
    }
    else {
        json_pair.push_back({"docid", vec_result[0].doc_id});
        json_pair.push_back({"rank", vec_result[0].rank});
    }

    if (vec_result[0].rank == 0) {
        result["request" + std::to_string(request_num)] = {"result", "false"};
        return result;
    } else {
        result["request" + std::to_string(request_num)] = {{"result", "true"}, json_pair};
        return result;
    }
}

void Converter_JSON::write_answers(std::string path, std::vector<std::vector<RelativeIndex>>answers) {
    json json_answers;
    for (int a = 0; a < answers.size(); ++a) {
        json_answers["answers"].push_back(construct_result_func(a, answers[a]));
    }
    writer.write_json_in_file(path, json_answers);
}