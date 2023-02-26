#include "projects_source.h"
//*
#include "gtest/gtest.h"

TEST(sample_test_case, sample_test) {
    EXPECT_EQ(1, 1);
}
//*/
/*
void output(vector<string> str_vec) {
    for (auto str : str_vec) {
        std::cout << str << "\n";
    }
}
/*
void output_vec_vec(vector<vector<RelativeIndex>> vec_vec) {
    cout << "vec_vec size " << vec_vec.size() << "\n";
    for(auto vec : vec_vec) {
        cout << "vec size " << vec.size() << "\n";
        for (auto rel : vec) {
            cout << rel.doc_id << " " << rel.rank << "\n";
        }
    }
}
 */

int main() {
    vector<string> paths;
    vector<string> requests;
    Converter_JSON convert;
    InvertedIndex interted;

    try {
        convert.correct_config();
        convert.correct_request();
    }
    catch (const non_config &x) {
        cout << x.what();
        return 1;
    }
    catch (const non_config_key &x) {
        cout << x.what();
        return 1;
    }
    catch (const non_request &x) {
        cout << x.what();
    }
    catch (const non_request_key &x) {
        cout << x.what();
    }
    paths = convert.GetTextDocuments();
    requests = convert.get_requests();

    interted.UpdateDocumentBase(paths);
    for (auto req : requests) {
        try { interted.GetWordCount(req); }
        catch (const non_word &x) { cout << x.what(); }
    }
    SearchServer search(interted);

    vector<vector<RelativeIndex>> search_result = search.search(requests);

    convert.putAnswers(search_result);

    return 0;
}
