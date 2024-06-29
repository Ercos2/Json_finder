#include "search_server.h"

SearchServer::SearchServer(InvertedIndex& idx) : index(idx) { }

std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string>& queries_input) {
    bool iter_flag = false;
    std::vector<std::vector<RelativeIndex>> relative_vec_vec;
    //*
    for (const auto& queri : queries_input) {
        std::vector<std::string> words;
        std::vector<RelativeIndex> relative_vec;
        if (index.get_dictionary().contains(queri)) {
            for (int a = 0; a < index.get_dictionary()[queri].size(); ++a) {
                RelativeIndex new_relative(index.get_dictionary()[queri][a].doc_id,
                                           index.get_dictionary()[queri][a].count);
                relative_vec.push_back(new_relative);
            }
            relative_vec_vec.push_back(relative_vec);
            relative_vec.clear();
        }
        else {
            if (!iter_flag) {
                RelativeIndex new_relative(0, 0);
                relative_vec.push_back(new_relative);
                relative_vec_vec.push_back(relative_vec);
                relative_vec.clear();
                iter_flag = true;
            }
        }
        iter_flag = false;
    }
    for (auto& p_relative_vec : relative_vec_vec) {
        sort(p_relative_vec.begin(), p_relative_vec.end());
        double absolut = p_relative_vec[0].rank;
        for (auto& p_relative : p_relative_vec)
            if (absolut != 0) p_relative.rank /= absolut;
            else p_relative.rank /= (absolut + 1);
    }
    return relative_vec_vec;
}