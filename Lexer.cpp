//
// Created by yedaya on 12/25/18.
//


#include "Lexer.h"
using namespace std;

vector<string> Lexer::lexer(string input) {
    
    bool isFirstBlank = true;
    bool isPath = false;
    string word;
    vector<string> words;

    int i = 0;
    // pass blanks at the beginning
    while (i < input.size() && 
    (input[i] == ' ' || input[i] == '\t' || input[i] == '\n')) {
        ++i;
    }

    // pass over input
    while (i < input.size()) {
        // case " set flag that -,/ etc. aren't operators
        if (input[i] == '"') {
            isPath = true;
        }
        // mark end line with ;
        if (input[i] == '\n') {
            if (!word.empty()) {
                words.push_back(word);
                word = "";
                words.push_back(";");
            }
            isFirstBlank = true;
            isPath = false;
            // operators
        } else if (input[i] == '+' || input[i] == '*' 
        || input[i] == '(' || input[i] == ')' || input[i] == ',') {
            if (!word.empty()) {
                words.push_back(word);
                word = "";
            }
            words.push_back(string(1, input[i]));
            // more operators
        } else if (input[i] == '=' || input[i] == '<' || input[i] == '>') {
            // ==, <=, >=
            if (input[i + 1] == '=') {
                if (!word.empty()) {
                    words.push_back(word);
                    word = "";
                }
                word += input[i];
                word += input[i+1];
                words.push_back(word);
                word = "";
                i++;
                // =, <, >
            } else {
                if (!word.empty()) {
                    words.push_back(word);
                    word = "";
                }
                words.push_back(string(1, input[i]));
            }
            // operator !=
        } else if (input[i] == '!') {
            if (input[i + 1] == '=') {
                if (!word.empty()) {
                    words.push_back(word);
                    word = "";
                }
                word += input[i];
                word += input[i + 1];
                words.push_back(word);
                word = "";
                i++;
            }
            // case not in path, /,- are operators
        } else if (!isPath && (input[i] == '/' || input[i] == '-')) {
            if (!word.empty()) {
                words.push_back(word);
                word = "";
            }
            words.push_back(string(1, input[i]));
            // blanks
        } else if (input[i] == ' ' || input[i] == '\t') {
            if (isFirstBlank && !word.empty()) {
                words.push_back(word);
                word = "";
                isFirstBlank = false;
            }
            //regular chars
        } else {
            word += input[i];
            isFirstBlank = true;
        }
        i++;
    }
    // add last word
    if(!word.empty()) {
        words.push_back(word);
    }
    // remove double ";"
    for (int j = 1; j < words.size(); ++j) {
        if (words[j - 1] == ";" && words[j] == ";") {
            words[j - 1] = "";
        }
    }

    return words;
}