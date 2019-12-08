#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <map>

//#define PRINT

using namespace std;

class MyMiniSearchEngine {
private:
    // default solution. OK to change but change index() accordingly if you do
    map<string, vector<vector<int>>> indexes;

    // cleanUpData returns a copy of the texts vector with all non alphabetic removed,
    // and all characters turned to lower cases
    unique_ptr<vector<string>> cleanUpData(const vector<string> &texts) {

        unique_ptr<vector<string>> data = make_unique<vector<string>>(texts);

        for (int i = 0; i < data->size(); ++i) {

            // remove none alphabet
            string *s = &(*data)[i];
            s->erase(remove_if(s->begin(), s->end(), [](char c) { return !isalpha(c) && !isspace(c); }), s->end());

            // convert to lower case
            for_each(s->begin(), s->end(), [](char &c) {
                c = ::tolower(c);
            });
        }

        return data;
    }

    // split the given string by white spaces
    // for example "hello world  Seattle" ==> ["hello", "world", "Seattle"]
    unique_ptr<vector<string>> splitByWhiteSpaces(const string &str) {
        vector<string> words;
        istringstream iss(str);
        for (std::string s; iss >> s;) {
            words.push_back(s);
#ifdef PRINT
            printf("'%s'\n", s.c_str());
#endif
        }
        return make_unique<vector<string>>(words);
    }

    // index generates the indexes based on the provided document texts
    // OK to change/rewrite based on design of the index
    void index(const vector<string> &texts) {

        // clean up data
        unique_ptr<vector<string>> pData = cleanUpData(texts);

        // each item of the vector is a document
        int numOfDoc = (*pData).size();
        for (int i = 0; i < numOfDoc; ++i) {

            cout << "Document " << i << ":" << endl;
            string doc = (*pData)[i];

            // split the document by white spaces
            unique_ptr<vector<string>> words = splitByWhiteSpaces(doc); // use 'words'
            /*
             *  Variable reference
             *  i = current document index
             *  j = current token in document.
             *
             */


            // homework: generate index for search
            int numOfWords = (*words).size();
            for (int j = 0; j < numOfWords; j++)
            {
                string currentWord = (*words)[j];
                // Check if the current word has been indexed. If not, created new entry.

                if(indexes.count(currentWord) == 0)
                {
                    cout << "[NEW]String '"<< currentWord <<"' does not exist. Make a new key. Document " << i << " For location " << j << endl;

                    // Build temp. vectors here to add to hashmap
                    vector<vector<int>> wordInDoc; // Temp vector to store the doc ID that contains string.
                    vector<int> wordLocation; // Temp vector to store locations of string in doc.

                    wordLocation.push_back(j); // Push location of string

                    vector<vector<int>>::iterator it = wordInDoc.begin(); // Create iterator for wordInDoc vector. Each index location represents doc ID.

                    wordInDoc.insert(it , wordLocation); //TODO change insertion
                    indexes.insert(pair<string, vector<vector<int>>>(currentWord, wordInDoc)); // Create new entry.


                }
                // If string exists. Append current location.
                else{

                    cout << "[EXIST]String '"<< currentWord <<"' exists in document "<< i <<". append location " << j << endl;

                    /*
                    vector<vector<int>> wordInDoc = indexes[currentWord];

                    vector<int> wordLocation = wordInDoc[i];

                    wordLocation.push_back(j);
                    */
                }

            }


        }
#ifdef PRINT
        printIndex();
#endif
    }

public:
    MyMiniSearchEngine() = delete;

    void printIndex() {
        for (auto it = indexes.begin(); it != indexes.end(); it++) {
            printf("[%s]:{", it->first.c_str());
            auto fileVector = it->second;
            for (int i = 0; i < fileVector.size(); i++) {
                printf("[");
                for (int j = 0; j < fileVector[i].size(); j++) {
                    if (j != 0) {
                        printf(",");
                    }
                    printf("%d", fileVector[i][j]);
                }
                printf("]");
            }
            printf("}\n");
        }
    }

    explicit MyMiniSearchEngine(const vector<string> &texts) {
        reload(texts);
    }

    void reload(const vector<string> &texts) {
        indexes.clear();
        index(texts);
    }

    // search(key) return all the document id where the given string appears
    // document is labelled as the integer index of the search engine constructor.
    // search key can have one or two words in all English alphabetic characters.
    // return pointer to an empty vector if search() finds no match in all files
    vector<int> search(const string &searchKey) {
        // homework
        return vector<int>(-1);   // place holder
    }
};

