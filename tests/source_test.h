#include <gtest/gtest.h>
#include "projects_source.h"
#include "search_server.h"
#include "inverted_index.h"

#include <iostream>

void output_entry_vec(std::vector<Entry> word_count);

void output_entry_vec_vec(std::vector<std::vector<Entry>> result);

void TestInvertedIndexFunctionality(
        const std::vector<std::string>& docs,
        const std::vector<std::string>& requests,
        const std::vector<std::vector<Entry>>& expected
);

void output_vec_vec(std::vector<std::vector<RelativeIndex>> vec_vec);