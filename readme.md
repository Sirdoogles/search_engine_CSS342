## Implement a mini text search engine (100pt)

Use folder ```mini_search_engine```.

Ready to take on google yet? Well, let's give it a try.

### TL;DR
- write index() and search()
- index(...) takes a list of strings and generate indexes
- search(...) finds single word as well as phrase of words
- must pass provided tests
- do not use string comparison to scan each doc to do search
- suggestive reading/idea [here](http://www.ardendertat.com/2011/05/30/how-to-implement-a-search-engine-part-1-create-index/). this is also what my solution is based on

### The Idea

This project will produce a text search engine that can search a single word or phrase made up of multiple words from the given texts. For example, given the following documents:

 - document 0: "hello world"
 - document 1: "hello"
 - document 2: "world"
 - document 3: "world world hello"
 - document 4: "seattle rains hello abc world"
 - document 5: "sunday hello world fun"
 
Each document is represented by a string in the code. 
 
The search engine works by firstly cleaning up data (removing non-alphabetical character) and generating indexes from all the documents. Indexing collects, parses, and stores data to facilitate fast and accurate search. Once indexes are generate, text keywords can be searched by calling 

```c++
vector<int> MyMiniSearchEngine::search(const string &searchKey)
```

This function returns a vector of document Id that contains the searched term. For example:

- search("seattle") --> \[4\]
- search("Seattle") --> \[4\]
- search("hello world") --> \[0, 5\]
- search("bothell") --> \[\]

Here the number in the result vector are document id, 0 to 5 for the documents example above. 

Note that this search engine is not case sensitive. All words in the documents will be converted to lower case and search will be conducted also in lower case. And non-alphabetical character will be removed. Utility functions for these purpose are already provided in the code. 

Also note that a phrase kehyword like "hello world" only matches documents that have this phase as a whole, here 0, and 5. Document 3 has both "hello" and "world" but in the opposite order, so it is not a match. 

### The Cogs

Before you say "just use string comparision with the keyword on each doc", keep in mind that search engines usually deal with very large documents and see lots of repeated searches. String comparison is usually O(N) complexity with N being the size of documnets. However with an indexing (or hashing) based algorithm, the complexity can be largely reduced. The idea is to have a hash table data structure where key is each word in all the docs, and value is a vector of all the documents that contain that word. For example:

- "hello" : \[0, 1, 3, 5\]
- "seattle" : \[4\].

This way, if "hello" is searched, we can quickly return in O(1) time that it appears in document 0, 1, 3, and 5.

With this single layer of structure, it is still hard to search phrase because words in a phrase matters in a search, and therefore the information of where each word appears in documents also need to be kept in the indexes. This part will be designed and implemented by you. [Here](http://www.ardendertat.com/2011/05/30/how-to-implement-a-search-engine-part-1-create-index/) is an example solution if you need some help or inspiration. 

**If each search is done by scanning in all documents by string comparsion, a 50pt penalty will take place plus any test failure**

### Mad Pointers
This project is designed to use unique_ptr ONLY. We are sick of "new" and "delete" and "seg fault" and memory leak anyway right? This is your chance to experience C++ in its modern term. ***Use raw pointers at your own risk.***

### The Sweat and Tears

Once you have the design, please implement the following function in src/search_engine.h:
```c++
vector<int> void MyMiniSearchEngine::index(const vector<string> &texts)
```
and 
```c++
vector<int> MyMiniSearchEngine::search(const string &searchKey)
```

As the name suggested, index(...) takes the given vector of strings (each representing a document), and create the indexes. search(...) then searches the searchKey in the indexes, and return a vector of document Ids that contain searchKey, empty vector if no match. 

### Testing is Believing

A set of tests are provided in test/unit_tests.cpp. Once the project is done, all thest should pass like the following:
```bash
[==========] Running 4 tests from 1 test case.
[----------] Global test environment set-up.
[----------] 4 tests from search_engine
[ RUN      ] search_engine.single_word_search
[       OK ] search_engine.single_word_search (0 ms)
[ RUN      ] search_engine.double_word_search
[       OK ] search_engine.double_word_search (0 ms)
[ RUN      ] search_engine.triple_word_search
[       OK ] search_engine.triple_word_search (0 ms)
[ RUN      ] search_engine.no_search_result
[       OK ] search_engine.no_search_result (1 ms)
[----------] 4 tests from search_engine (1 ms total)

[----------] Global test environment tear-down
[==========] 4 tests from 1 test case ran. (1 ms total)
[  PASSED  ] 4 tests.
```

**Your work on the mini_search_engine is mostly judged by the successful pass of these tests. Each failing test will cost 20 pts, and 20 more towards the design and code. Feel free to add a text file to describe your design briefly.**
