#include "inverted_index.h"

InvertedIndex::InvertedIndex() = default;

std::string update(std::string path) {
    std::string modify_str = "";
    std::ifstream file_stream(path);
    if (!file_stream.is_open())
        modify_str = "";
    else {
        while (!file_stream.eof()) {
            std::string temp_str;
            getline(file_stream, temp_str);
            modify_str += " " + temp_str;
        }
    }
    file_stream.close();
    return modify_str;
}

void InvertedIndex::update_document_base(std::vector<std::string> input_docs) {
    ThreadPool pool;
    int finish = 0;
    std::condition_variable cv;
    docs = std::vector<std::string>(input_docs.size(), "");

    auto new_update{ [&](std::string& input_doc, std::string& doc){
        pool.enqueue([&]{
                doc = update(input_doc);
                update_mute.lock();
                ++finish;
                update_mute.unlock();
                cv.notify_all();
            });
    }};

    for (int a = 0; a < input_docs.size(); ++a) 
        new_update(input_docs[a], docs[a]);
        
    std::unique_lock<std::mutex> lk(update_mute);
    cv.wait(lk, [&](){return finish == input_docs.size();});
}

void InvertedIndex::get_words(std::vector<std::string>& words, const std::string &str) {
    std::string new_word;
    std::string temp_str = " " + str;
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

std::vector<Entry> InvertedIndex::get_word_count(const std::string& string_words) {
    std::vector<std::string> vector_words;
    get_words(vector_words, string_words);
    std::vector<std::string> words;
    std::vector<Entry> temp_vec;

    for (size_t doc_num = 0; doc_num < docs.size(); ++doc_num) {
        if (docs[doc_num] == "") 
            continue;
        get_words(words, docs[doc_num]);
        for (const auto &word : words) {
            for(const auto& temp_word : vector_words) {
                if (word == temp_word) {
                    if (temp_vec.empty()) {
                        temp_vec.push_back({doc_num + 1, 1});
                    } else {
                        bool flag = false;
                        for (const auto& entry: temp_vec) {
                            if (entry.doc_id == doc_num + 1) {
                                temp_vec.pop_back();
                                temp_vec.push_back({entry.doc_id, (entry.count + 1)});
                                flag = true;
                                break;
                            }
                        }
                        if (!flag) {
                            temp_vec.push_back({doc_num + 1, 1});
                        }
                    }
                }
            }
        }
        words.clear();
    }

    if (temp_vec.empty())
        throw non_word(string_words);

    count_mute.lock();
    freq_dictionary[string_words] = temp_vec;
    count_mute.unlock();

    return freq_dictionary[string_words];
}

std::map<std::string, std::vector<Entry>> InvertedIndex::get_dictionary() const {
    return freq_dictionary;
}

void InvertedIndex::set_docs(std::vector<std::string> new_docs) {
    docs = new_docs;
}