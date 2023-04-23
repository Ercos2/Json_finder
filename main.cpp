#include "inverted_index.h"
#include "search_server.h"
#include "converter_JSON.h"

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
    paths = convert.get_text_documents();
    requests = convert.get_requests();

    interted.update_document_base(paths);
    for (const auto& req : requests) {
        try { interted.get_word_count(req); }
        catch (const non_word &x) { cout << x.what(); }
    }
    SearchServer search(interted);

    vector<vector<RelativeIndex>> search_result = search.search(requests);

    convert.put_answers(search_result);

    return 0;
}
