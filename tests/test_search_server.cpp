#include "source_test.h"

TEST(TestCaseSearchServer, TestSimple) {
    const std::vector<std::string> docs = {
            "milk milk milk milk water water water",
            "milk water water",
            "milk milk milk milk milk water water water water water",
            "americano cappuccino"
    };
    const std::vector<std::string> request = {"milk water", "sugar"};
    const std::vector<std::vector<RelativeIndex>> expected = {
            {
                    {3, 1},
                    {1, 0.7},
                    {2, 0.3}
            },
            {       {0, 0}
            }
    };
    InvertedIndex idx;
    idx.set_docs(docs);
    for (auto word : request) {
        try {
            //idx.get_word_count(word);
            //output_entry_vec(idx.get_word_count(word));
            idx.get_word_count(word);
            //result.push_back(word_count);
        }
        catch (const non_word &x) { std::cout << x.what(); }
    }
    //idx.update_document_base(docs);
    //output_entry_vec(idx.get_dictionary());
    SearchServer srv(idx);
    std::vector<std::vector<RelativeIndex>> result = srv.search(request);
    //output_vec_vec(result);
    ASSERT_EQ(result, expected);
}
TEST(TestCaseSearchServer, TestTop5) {
    const std::vector<std::string> docs = {
            "london is the capital of great britain",
            "paris is the capital of france",
            "berlin is the capital of germany",
            "rome is the capital of italy",
            "madrid is the capital of spain",
            "lisboa is the capital of portugal",
            "bern is the capital of switzerland",
            "moscow is the capital of russia",
            "kiev is the capital of ukraine",
            "minsk is the capital of belarus",
            "astana is the capital of kazakhstan",
            "beijing is the capital of china",
            "tokyo is the capital of japan",
            "bangkok is the capital of thailand",
            "welcome to moscow the capital of russia the third rome",
            "amsterdam is the capital of netherlands",
            "helsinki is the capital of finland",
            "oslo is the capital of norway",
            "stockholm is the capital of sweden",
            "riga is the capital of latvia",
            "tallinn is the capital of estonia",
            "warsaw is the capital of poland",
    };
    const std::vector<std::string> request = {"moscow is the capital of russia"};
    const std::vector<std::vector<RelativeIndex>> expected = {
            {
                    {8, 1},
                    {15, 1},
                    {12, 0.666667},
                    {22, 0.666667},
                    {21, 0.666667}
            }
    };
    InvertedIndex idx;
    idx.set_docs(docs);
    for (auto word : request) {
        try {
            //output_entry_vec(idx.get_word_count(word));
            idx.get_word_count(word);
        }
        catch (const non_word &x) { std::cout << x.what(); }
    }
    SearchServer srv(idx);
    std::vector<std::vector<RelativeIndex>> result = srv.search(request);
    //output_vec_vec(result);
    ASSERT_EQ(result[0][0], expected[0][0]);
    ASSERT_EQ(result[0][1], expected[0][1]);
}
