#include "Interpreter.h"
/*

    vector<string> Lexer::lexer(string input) {
        int i = 0;
        string word;
        bool firstBlank = true;
        bool hasPath = false;
        vector<string> words;

        // pass over input
        while (i < input.size()) {
            // case " set flag that -,/ etc. aren't operators
            if (input[i] == '"') {
                hasPath = true;
            }
            // mark end line with ;
            if (input[i] == '\n') {
                if (word != "") {
                    words.push_back(word);
                    word = "";
                }
                words.push_back(";");
                firstBlank = true;
                hasPath = false;
                // operators
            } else if (input[i] == '+' || input[i] == '*' || input[i] == '(' || input[i] == ')') {
                if (word != "") {
                    words.push_back(word);
                    word = "";
                }
                words.push_back(string(1, input[i]));
                // more operators
            } else if (input[i] == '=' || input[i] == '<' || input[i] == '>') {
                // ==, <=, >=
                if (input[i + 1] == '=') {
                    if (word != "") {
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
                    if (word != "") {
                        words.push_back(word);
                        word = "";
                    }
                    words.push_back(string(1, input[i]));
                }
                // operator !=
            } else if (input[i] == '!') {
                if (input[i + 1] == '=') {
                    if (word != "") {
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
            } else if (!hasPath && (input[i] == '/' || input[i] == '-')) {
                if (word != "") {
                    words.push_back(word);
                    word = "";
                }
                words.push_back(string(1, input[i]));
                // blanks
            } else if (input[i] == ' ' || input[i] == '\t') {
                if (firstBlank && word != "") {
                    words.push_back(word);
                    word = "";
                    firstBlank = false;
                }
                //regular chars
            } else {
                word += input[i];
                firstBlank = true;
            }
            i++;
        }
        // add last word
        if(word!="") {
            words.push_back(word);
        }
        return words;
    }
};
 */