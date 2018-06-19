//
//  main.cpp
//  HelloCpp
//
//  Created by Hilton Pintor Bezerra Leite on 11/06/2018.
//  Copyright © 2018 Voxar labs. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
using namespace std;

string hideLetters(string word) {
    string hidden = "";
    for (int i = 0; i < word.length(); i++) {
        hidden += "*";
    }
    return hidden;
}

string checkLetter(char guess, string word, string& hiddenWord) {
    for (int i = 0; i < word.length(); i++) {
        if (word[i] == guess) {
            hiddenWord[i] = guess;
        }
    }
    
    return hiddenWord;
}

bool finishedGame(string hiddenWord) {
    for (int i = 0; i < hiddenWord.length(); i++) {
        if (hiddenWord[i] == '*') {
            return false;
        }
    }
    
    return true;
}


int main() {
    
    string word = "potato";
    string hidden = hideLetters(word);
    vector<char> guesses;
    bool playing = true;
    
    while (playing) {
        cout << "The word is: " << hidden << endl;
        
        cout << "Enter a letter: ";
        char guess;
        cin >> guess;
        
        checkLetter(guess, word, hidden);
        
        if (finishedGame(hidden)) {
            playing = false;
            cout << word << endl;
            cout << "Congratulations, you won!" << endl;
        }
     }
    
    return 0;
}

