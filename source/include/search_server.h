#pragma once

#include "projects_source.h"
#include "inverted_index.h"

class SearchServer {
public:
    SearchServer(InvertedIndex& idx);

    vector<vector<RelativeIndex>> search(const vector<string>& queries_input);

private:
    InvertedIndex index;
};