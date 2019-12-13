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
                indexes.insert(pair<string, vector<vector<int>>>(currentWord, vector<vector<int>>(numOfDoc))); // Create new entry.
                indexes[currentWord][i].push_back(j);

            }
        }
#ifdef PRINT
        printIndex();
#endif
    }

    vector<int> intersection(vector<int> v1, vector<int> v2)
    {
        vector<int> intersectVector;

        set_intersection(v1.begin(),v1.end(),v2.begin(),v2.end(),back_inserter(intersectVector));
        return intersectVector;
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
        unique_ptr<string> s = make_unique<string>(searchKey);
        // Converts input key to lowercase. This makes it case-insensitive.
        for_each(s->begin(), s->end(), [](char &c) {
            c = ::tolower(c);
        });
        vector<int> docResult;
        // Split *s by white spaces if input has more than 1 word.
        unique_ptr<vector<string>> words = splitByWhiteSpaces(*s);
        int numOfSearch = (*words).size();
        if(numOfSearch == 1) // Runs if it is a single word search.
        {
            string current = (*words)[0];
            vector<vector<int>> wordLocations = indexes[current];

            int wlSize = wordLocations.size();

            for(int i = 0; i < wlSize; i++)
            {
                if(!wordLocations[i].empty())
                {
                    docResult.push_back(i);
                }
            }
        }
        // Runs if it is multi-word search.
        else{

            vector<int> intersectDoc = search((*words)[0]);

            // Find the documents which contains all of the terms.
            for(int i = 1; i < numOfSearch; i++)
            {
                vector<int> tempIntersect = search((*words)[i]);
                intersectDoc = intersection(intersectDoc, tempIntersect);
            }
            // intersectDoc vector now contains the doc ID's that may be sutible for a search hit.

            int intersectDocSize = intersectDoc.size();

            // Iterates for each document that contains all terms.
            for (int j = 0; j < intersectDocSize; j++)
            {
                int currentDoc = intersectDoc[j]; // Stores the desired doc ID.

                string firstTerm = (*words)[0]; // Stores the first term of the search query.
                vector<vector<int>> wordLocations = indexes[firstTerm]; // Selects the documents associated with the first term of the query.
                vector<int> wordPositionsInDoc = wordLocations[currentDoc]; // Select the vector associated with the desired document.

                // Iterates for the other search terms beyond the first.
                for(int k = 1; k < numOfSearch; k++)
                {
                    string tempTerm = (*words)[k]; // Stores the current term. (Must be beyond the first).
                    vector<vector<int>> wordLocationsTemp = indexes[tempTerm]; // Selects the documents associated with the current term of the query.
                    vector<int> wordPositionsInDocTemp = wordLocationsTemp[currentDoc];

                    for(int l = 0; l < wordPositionsInDocTemp.size(); l++)
                    {
                        wordPositionsInDocTemp[l] = wordPositionsInDocTemp[l] - k; // Subtract each int in the vector by k.
                    }

                    wordPositionsInDoc = intersection(wordPositionsInDoc, wordPositionsInDocTemp); // Intersect the temp vector with the first one.
                }

                // If the vector is not empty, then match found,
                if(!wordPositionsInDoc.empty())
                {
                    docResult.push_back(currentDoc);
                }
            }
        }
        return docResult;
    }
};

