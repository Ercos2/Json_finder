#include "source_test.h"

void output_entry_vec(std::vector<Entry> word_count) {
    for (auto word : word_count) {
        std::cout << word.doc_id << " " << word.count << "\n";
    }
    std::cout << "//////////////////////////////\n";
}

void output_entry_vec_vec(std::vector<std::vector<Entry>> result) {
    for (auto word_count : result) {
        for (auto word: word_count) {
            std::cout << word.doc_id << " " << word.count << "\n";
        }
        std::cout << "/////////\n";
    }
    std::cout << "//////////////////////////////\n";
}

void output_vec_vec(std::vector<std::vector<RelativeIndex>> vec_vec) {
    std::cout << "vec_vec size " << vec_vec.size() << "\n";
    for(const auto& vec : vec_vec) {
        std::cout << "vec size " << vec.size() << "\n";
        for (const auto& rel : vec) {
            std::cout << "{" << rel.doc_id << ", " << rel.rank << "},\n";
        }
    }
}

void TestInvertedIndexFunctionality(
        const std::vector<std::string>& docs,
        const std::vector<std::string>& requests,
        const std::vector<std::vector<Entry>>& expected
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
        catch (const non_word &x) { std::cout << x.what(); }
    }
    //output_entry_vec_vec(result);
    //output_entry_vec_vec(expected);
    ASSERT_EQ(result, expected);
}