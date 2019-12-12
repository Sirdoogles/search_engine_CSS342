#include "gtest/gtest.h"
#include <vector>
#include "search_engine.h"

using namespace std;

vector<string> testTexts() {
    return vector<string>{
            "hello world", // Doc 0
            "hello", // Doc 1
            "world", // Doc 2
            "world world hello", // Doc 3
            "seattle rains hello abc world", // Doc 4
            "sunday hello world fun", // Doc 5
    };
}

TEST(search_engine, single_word_search) {

    MyMiniSearchEngine engine(testTexts());
    engine.printIndex();

    vector<int> result = engine.search("seattle");
    ASSERT_EQ(result.size(), 1);
    ASSERT_EQ(result[0], 4);

    result = engine.search("Seattle");
    ASSERT_EQ(result.size(), 1);
    ASSERT_EQ(result[0], 4);
}

TEST(search_engine, double_word_search) {

    MyMiniSearchEngine engine(testTexts());

    vector<int> result = engine.search("hello world");
    ASSERT_EQ(result.size(), 2);
    ASSERT_EQ(result, vector<int>({0, 5}));
}

TEST(search_engine, triple_word_search) {

    MyMiniSearchEngine engine(testTexts());

    vector<int> result = engine.search("rains hello abc");
    ASSERT_EQ(result.size(), 1);
    ASSERT_EQ(result, vector<int>({4}));

    result = engine.search("rains Hello abc");
    ASSERT_EQ(result.size(), 1);
    ASSERT_EQ(result, vector<int>({4}));
}

TEST(search_engine, no_search_result) {

    MyMiniSearchEngine engine(testTexts());

    vector<int> result = engine.search("hello team");
    ASSERT_EQ(result.size(), 0);
}
