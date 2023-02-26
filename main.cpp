#include "projects_source.h"

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
