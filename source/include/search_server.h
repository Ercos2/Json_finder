#pragma once

#include "projects_source.h"
#include "inverted_index.h"

class SearchServer {
public:
    SearchServer(InvertedIndex& idx);

    std::vector<std::vector<RelativeIndex>> search(const std::vector<std::string>& queries_input);
private:
    InvertedIndex index;
};