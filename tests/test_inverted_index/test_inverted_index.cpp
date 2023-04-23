#include <gtest/gtest.h>
#include "projects_source.h"
#include "search_server.h"
#include "inverted_index.h"

using namespace std;
#include <iostream>

void output_entry_vec(vector<Entry> word_count) {
    for (auto word : word_count) {
        cout << word.doc_id << " " << word.count << "\n";
    }
    cout << "//////////////////////////////\n";
}

void output_entry_vec_vec(vector<vector<Entry>> result) {
    for (auto word_count : result) {
        for (auto word: word_count) {
            cout << word.doc_id << " " << word.count << "\n";
        }
        cout << "/////////\n";
    }
    cout << "//////////////////////////////\n";
}

void TestInvertedIndexFunctionality(
        const vector<string>& docs,
        const vector<string>& requests,
        const std::vector<vector<Entry>>& expected
) {
    std::vector<std::vector<Entry>> result;
    InvertedIndex idx;
    idx.set_docs(docs);
    for(auto& request : requests) {
        try {
            std::vector<Entry> word_count = idx.get_word_count(request);
            output_entry_vec(word_count);
            result.push_back(word_count);
        }
        catch (const non_word &x) { cout << x.what(); }
    }
    //output_entry_vec_vec(result);
    ASSERT_EQ(result, expected);
}
TEST(TestCaseInvertedIndex, TestBasic) {
    const vector<string> docs = {
            "london is the capital of great britain",
            "big ben is the nickname for the Great bell of the striking clock"
    };
    const vector<string> requests = {"london", "the"};
    const vector<vector<Entry>> expected = {
            {
                    {1, 1}
            }, {
                    {1, 1}, {2, 3}
            }
    };
    TestInvertedIndexFunctionality(docs, requests, expected);
}
TEST(TestCaseInvertedIndex, TestBasic2) {
    const vector<string> docs = {
            "milk milk milk milk water water water",
            "milk water water",
            "milk milk milk milk milk water water water water water",
            "americano cappuccino"
    };
    const vector<string> requests = {"milk", "water", "cappuccino"};
    const vector<vector<Entry>> expected = {
            {
                    {1, 4}, {2, 1}, {3, 5}
            }, {
                    {1, 3}, {2, 2}, {3, 5}
            }, {
                    {4, 1}
            }
    };
    TestInvertedIndexFunctionality(docs, requests, expected);
}
TEST(TestCaseInvertedIndex, TestInvertedIndexMissingWord) {
    const vector<string> docs = {
            "a b c d e f g h i j k l",
            "statement"
    };
    const vector<string> requests = {"m", "statement"};
    const vector<vector<Entry>> expected = {
            {
                    {2, 1}
            }
    };
    TestInvertedIndexFunctionality(docs, requests, expected);
}
