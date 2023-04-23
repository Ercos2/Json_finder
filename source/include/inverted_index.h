#pragma once

#include "projects_source.h"

static mutex update_mute;

void update(string str, string& modify_str, vector<bool>& end_vec);

class InvertedIndex {
public:
    InvertedIndex();

    void update_document_base(vector<string> input_docs);

    void get_words(vector<string>& words, const string &str);

    string construct_str(vector<string> vec);

    vector<Entry> get_word_count(const string& word);

    map<std::string, vector<Entry>> get_dictionary() const;

    void set_docs(vector<string> new_docs);
private:
    vector<string> docs;
    map<std::string, vector<Entry>> freq_dictionary;
};