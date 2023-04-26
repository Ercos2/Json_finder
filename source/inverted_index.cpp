#include "inverted_index.h"

void update(string str, string& modify_str, vector<bool>& end_vec) {
    ifstream file_stream(str);
    if (!file_stream.is_open())
        modify_str = "";
    else {
        while (!file_stream.eof()) {
            getline(file_stream, str);
            modify_str += " " + str;
        }
    }
    file_stream.close();
    update_mute.lock();
    end_vec.push_back(1);
    update_mute.unlock();
}

InvertedIndex::InvertedIndex() = default;

void InvertedIndex::update_document_base(vector<string> input_docs) {
    vector<string> vec_str(input_docs.size());
    vector<bool> end_vec;
    vector<thread> updates(input_docs.size());
    for (int a = 0; a < input_docs.size(); ++a) {
        //if ()
        thread update1(update, input_docs[a], ref(vec_str[a]), ref(end_vec));
        swap(update1, updates[a]);
    }
    while (true) {
        update_mute.lock();
        if (end_vec.size() >= input_docs.size()) {
            for (int a = 0; a < updates.size(); ++a) {
                docs.push_back(vec_str[a]);
                updates[a].join();
            }
            update_mute.unlock();
            break;
        } else
            update_mute.unlock();
    }
}

void InvertedIndex::get_words(vector<string>& words, const string &str) {
    string new_word;
    string temp_str = " " + str;
    for (int a = 0; a < temp_str.size(); ++a) {
        if (a > 0 && temp_str[a] != ' ' && temp_str[a - 1] == ' ') {
            while (temp_str[a] != ' ' && a < temp_str.size()) {
                new_word += temp_str[a];
                ++a;
            }
            words.push_back(new_word);
            new_word.clear();
        }
    }
}

string InvertedIndex::construct_str(vector<string> vec) {
    string str;
    for (int a = 0; a < vec.size(); ++a)
        if (a + 1 != vec.size()) str += vec[a] + " ";
        else str += vec[a];

    return str;
}

vector<Entry> InvertedIndex::get_word_count(const string& word) {
    int doc_num = 1;
    vector<string> vec_word;
    get_words(vec_word, word);
    vector<string> words;

    for (const auto& doc : docs) {
        if (doc == "") {
            ++doc_num;
            continue;
        }
        get_words(words, doc);
        for (int a = 0; a < words.size(); ++a) {
            for(const auto& temp_word : vec_word) {
                if (words[a] == temp_word) {
                    if (!freq_dictionary.contains(construct_str(vec_word))) {
                        Entry new_entry(doc_num, 1);
                        freq_dictionary[construct_str(vec_word)].push_back(new_entry);
                    } else {
                        bool flag = false;
                        for (const auto& entry: freq_dictionary[construct_str(vec_word)]) {
                            if (entry.doc_id == doc_num) {
                                Entry new_entry(entry.doc_id, (entry.count + 1));
                                freq_dictionary[construct_str(vec_word)].pop_back();
                                freq_dictionary[construct_str(vec_word)].push_back(new_entry);
                                flag = true;
                                break;
                            }
                        }
                        if (!flag) {
                            Entry new_entry(doc_num, 1);
                            freq_dictionary[construct_str(vec_word)].push_back(new_entry);
                        }
                    }
                }
            }
        }
        ++doc_num;
        words.clear();
    }
    if (!freq_dictionary.contains(word))
        throw non_word();
    return freq_dictionary[word];
}

map<std::string, vector<Entry>> InvertedIndex::get_dictionary() const {
    return freq_dictionary;
}

void InvertedIndex::set_docs(vector<string> new_docs) {
    docs = new_docs;
}