#pragma once

#include "projects_source.h"
#include "threadPool.h"
#include <condition_variable>

static std::mutex update_mute;
static std::mutex count_mute;

void update(std::string str, std::string& modify_str, std::vector<bool>& end_vec);

class InvertedIndex {
public:
    InvertedIndex();

    void update_document_base(std::vector<std::string> input_docs);

    void get_words(std::vector<std::string>& words, const std::string &str);

    std::vector<Entry> get_word_count(const std::string& word);

    std::map<std::string, std::vector<Entry>> get_dictionary() const;

    void set_docs(std::vector<std::string> new_docs);
private:
    std::vector<std::string> docs;
    std::map<std::string, std::vector<Entry>> freq_dictionary;
};