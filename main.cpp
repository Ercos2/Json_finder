#include "inverted_index.h"
#include "search_server.h"
#include "converter_JSON.h"

int main() {
    std::vector<std::string> paths;
    std::vector<std::string> requests;
    Converter_JSON convert;
    InvertedIndex interted;

    std::string config_path = "../JSON/config.json";
    std::string requests_path = "../JSON/requests.json";
    std::string answers_path = "../JSON/answers.json";

    try{
        convert.is_json_key_correct(config_path, "config");
        std::cout << "key \"config\" in config is correct\n";
        convert.is_json_key_correct(config_path, "files");
        std::cout << "key \"files\" in config is correct\n";
        convert.is_json_key_correct(requests_path, "requests");
        std::cout << "requests is correct\n";
    }
    catch (const my_exception_with_str &x) {
        std::cout << x.what();
        return 1;
    }

    paths = convert.get_str_vec_by_key(config_path, "files");
    requests = convert.get_str_vec_by_key(requests_path, "requests");

    interted.update_document_base(paths);
    for (const auto& req : requests) {
        try { interted.get_word_count(req); }
        catch (const non_word &x) { std::cout << x.what(); }
    }
    SearchServer search(interted);

    std::vector<std::vector<RelativeIndex>> search_result = search.search(requests);

    convert.write_answers(answers_path, search_result);

    return 0;
}
