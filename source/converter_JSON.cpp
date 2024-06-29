#include "converter_JSON.h"
//#include <filesystem>

Converter_JSON::Converter_JSON() = default;

void Converter_JSON::correct_config() {
    json jfile;
    std::ifstream json_stream("../JSON/config.json");
    if (!json_stream.is_open()) {
        json_stream.close();
        throw non_config();
    }
    json_stream >> jfile;
    if (!jfile.contains("config")) {
        json_stream.close();
        throw non_config_key();
    }
}

std::vector<std::string> Converter_JSON::get_vector(json json_array) {
    for(const auto& json_str : json_array) {
        std::ifstream json_stream(json_str);
        if (!json_stream.is_open()) {
            
            //cout << json_str << "\n";
            std::cout << "File " << json_str << " open error.\n";
            paths.push_back(" ");
        }
        else {
            std::cout << "File " << json_str << " opened\n";
            paths.push_back(json_str);
        }
        json_stream.close();
    }
    return paths;
}

std::vector<std::string> Converter_JSON::get_text_documents() {
    paths.clear();
    json jfile;
    std::ifstream json_stream("../JSON/config.json");
    json_stream >> jfile;

    jfile["config"].contains("max_responses") ? max_str = jfile["config"]["max_responses"] : max_str = 5;

    json_stream.close();
    return get_vector(jfile["files"]);
}

int Converter_JSON::get_responses_limit() {
    return max_str;
}

void Converter_JSON::correct_request() {
    json jfile;
    std::ifstream json_stream("../JSON/requests.json");
    if (!json_stream.is_open()) {
        json_stream.close();
        throw non_request();
    }
    json_stream >> jfile;
    if (!jfile.contains("requests")) {
        json_stream.close();
        throw non_request_key();
    }
}
std::vector<std::string> Converter_JSON::get_requests() {
    requests.clear();
    json jfile;
    std::ifstream json_stream("../JSON/requests.json");
    json_stream >> jfile;

    json_stream.close();
    for(auto json_str : jfile["requests"]) {
        requests.push_back(json_str);
    }
    return requests;
}

json Converter_JSON::construct_result_func(int request_num, std::vector<RelativeIndex> vec_result) {
    json result;
    json json_pair;
    if (vec_result.size() > 1) {
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

void Converter_JSON::put_answers(std::vector<std::vector<RelativeIndex>>answers) {
    std::ofstream answers_stream("../JSON/answers.json");
    json json_answers;

    for (int a = 0; a < answers.size(); ++a) {
        json_answers["answers"].push_back(construct_result_func(a, answers[a]));
    }
    answers_stream << json_answers;
    answers_stream.close();
}