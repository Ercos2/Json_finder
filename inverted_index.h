#ifndef ENDGAME_INVERTED_INDEX_H
#define ENDGAME_INVERTED_INDEX_H

#include "projects_source.h"

mutex update_mute;

void update(string str, string& modify_str, vector<bool>& end_vec) {
    ifstream file_stream(str);
    while (!file_stream.eof()) {
        getline(file_stream, str);
        modify_str += " " + str;
    }
    file_stream.close();
    update_mute.lock();
    end_vec.push_back(1);
    update_mute.unlock();
}

class InvertedIndex {
public:
    InvertedIndex() = default;

    void UpdateDocumentBase(vector<string> input_docs) {
        //docs.clear();
        vector<string> vec_str(input_docs.size());
        vector<bool> end_vec;
        vector<thread> updates(input_docs.size());
        for (int a = 0; a < input_docs.size(); ++a) {
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

    void get_words(vector<string>& words, const string &str) {
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

    string construct_str(vector<string> vec) {
        string str;
        for (int a = 0; a < vec.size(); ++a)
            if (a + 1 != vec.size()) str += vec[a] + " ";
            else str += vec[a];

        return str;
    }

    vector<Entry> GetWordCount(const string& word) {
        int doc_num = 1;
        vector<string> vec_word;
        get_words(vec_word, word);
        vector<string> words;
        for (auto doc : docs) {
            get_words(words, doc);
            for (int a = 0; a < words.size(); ++a) {
                for(auto temp_word : vec_word) {
                    if (words[a] == temp_word) {
                        if (!freq_dictionary.contains(construct_str(vec_word))) {
                            Entry new_entry(doc_num, 1);
                            freq_dictionary[construct_str(vec_word)].push_back(new_entry);
                        } else {
                            bool flag = false;
                            for (auto entry: freq_dictionary[construct_str(vec_word)]) {
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
    /*
    void output_map() {
        for (auto it_req = freq_dictionary.begin(); it_req != freq_dictionary.end(); ++it_req) {
            for (auto entry : it_req->second) {
                cout << it_req->first << " " << entry.doc_id << " " << entry.count << "\n";
            }
        }
    }
    */
    map<std::string, vector<Entry>> get_dictionary() const {
        return freq_dictionary;
    }

private:
    vector<string> docs; // список содержимого документов
    map<std::string, vector<Entry>> freq_dictionary; // частотный словарь
};

#endif //ENDGAME_INVERTED_INDEX_H
