#ifndef ENDGAME_SEARCH_SERVER_H
#define ENDGAME_SEARCH_SERVER_H

#include "projects_source.h"

class SearchServer {
public:
    SearchServer(InvertedIndex& idx) : index(idx) { }

    vector<vector<RelativeIndex>> search(const vector<string>& queries_input) {
        bool iter_flag = false;
        vector<vector<RelativeIndex>> relative_vec_vec;
        for (auto queri : queries_input) {
            vector<string> words;
            vector<RelativeIndex> relative_vec;
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
        for (int a = 0; a < relative_vec_vec.size(); ++a) {
            sort(relative_vec_vec[a].begin(), relative_vec_vec[a].end());
            float absolut = relative_vec_vec[a][0].rank;
            for (int b = 0; b < relative_vec_vec[a].size(); ++b)
                if (absolut != 0) relative_vec_vec[a][b].rank /= absolut;
                else relative_vec_vec[a][b].rank /= (absolut + 1);
        }
        return relative_vec_vec;
    }

private:
    InvertedIndex index;
};

#endif //ENDGAME_SEARCH_SERVER_H
