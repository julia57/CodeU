//CodeU: Assignment_3
//
//  Created by Julia Semavina on 8.06.2017
//
//  problem specification:
//      Given a grid of letters and a dictionary, find all the words from the dictionary that can be
//      formed in the grid.
//
//  idea:
//      We start building words from every cell of the grid. So, at first we have words of the length=1. If the word
//      is prefix, we add one letter (from the North, South, East, West, N-W, N-E, S-W, S-E) if it is possible. Now we
//      have words of the length=2.
//      But this way if the input grid consists of the same items and input dictionary contains a very long string
//      of the same item (like "aaaaaaaa...aaa"), the complexity is SizeOfGrid*(C^MaxLength).
//      To avoid this we have SamePaths, which is map<int index_in_grip, string word>. So if in some case we find
//      path, which pair of index_in_grip and word already is in SamePath, we do not continue this path.
//
//  comments:
//      register is ignored
//


#include <iostream>
#include <set>
#include <map>
#include "word.h"


void WordsFromPrefix(int index, std::string prefix, int NumberOfColumns, int NumberOfRows, char * Grid,
                     Dictionary &TheDictionary,
                     std::set<std::string> &Answer, std::set<std::pair<int, std::string>> &SamePaths) {
    if (SamePaths.find(std::pair<int, std::string>(index, prefix)) != SamePaths.end()) { //already checked
        return;
    }
    SamePaths.insert(std::pair<int, std::string>(index, prefix));
    if(TheDictionary.is_word(prefix)) { // Word from the dictionary
        Answer.insert(prefix);
    }
    if(TheDictionary.is_prefix(prefix)) { // continue searching
        int x = index % NumberOfColumns;
        int y = index / NumberOfColumns;
        if (x != 0) { // West
            WordsFromPrefix(index - 1, prefix + Grid[index - 1], NumberOfColumns, NumberOfRows, Grid,
                            TheDictionary, Answer, SamePaths);
        }
        if (x != 0 && y != 0) { // North-West
            WordsFromPrefix(index - 1 - NumberOfColumns, prefix + Grid[index - 1 - NumberOfColumns],
                            NumberOfColumns, NumberOfRows, Grid, TheDictionary, Answer, SamePaths);
        }
        if (x != 0 && y != NumberOfRows - 1) { // South-West
            WordsFromPrefix(index - 1 + NumberOfColumns, prefix + Grid[index - 1 + NumberOfColumns],
                            NumberOfColumns, NumberOfRows, Grid, TheDictionary, Answer, SamePaths);
        }
        if (x != NumberOfColumns - 1) { // East
            WordsFromPrefix(index + 1, prefix + Grid[index + 1], NumberOfColumns, NumberOfRows, Grid,
                            TheDictionary, Answer, SamePaths);
        }
        if (x != NumberOfColumns - 1 && y != 0) { // North-East
            WordsFromPrefix(index + 1 - NumberOfColumns, prefix + Grid[index + 1 - NumberOfColumns], NumberOfColumns,
                            NumberOfRows, Grid, TheDictionary, Answer, SamePaths);
        }
        if (x != NumberOfColumns - 1 && y != NumberOfRows - 1) { // South-East
            WordsFromPrefix(index + 1 + NumberOfColumns, prefix + Grid[index + 1 + NumberOfColumns], NumberOfColumns,
                            NumberOfRows, Grid, TheDictionary, Answer, SamePaths);
        }
        if (y != 0) { //North
            WordsFromPrefix(index - NumberOfColumns, prefix + Grid[index - NumberOfColumns],
                            NumberOfColumns, NumberOfRows, Grid, TheDictionary, Answer, SamePaths);
        }
        if (y != NumberOfRows - 1) { // South
            WordsFromPrefix(index + NumberOfColumns, prefix + Grid[index + NumberOfColumns],
                            NumberOfColumns, NumberOfRows, Grid, TheDictionary, Answer, SamePaths);
        }
    }
}


std::set<std::string> WordsFound(int NumberOfRows, int NumberOfColumns, char* Grid,
                                 Dictionary &TheDictionary) {
    // launch search from every cell
    std::set<std::string> Answer;
    std::string word1 = "";
    std::set<std::pair<int, std::string>> SamePaths;
    for(int i = 0; i < NumberOfColumns*NumberOfRows; ++i) {
        word1 = Grid[i];
        WordsFromPrefix(i, word1, NumberOfColumns, NumberOfRows, Grid, TheDictionary, Answer, SamePaths);
    }
    return Answer;
}


int main() {
    // input data
    std::cout << "Let's make a grid" << std::endl;
    std::cout << "Enter the number of rows: ";
    int NumberOfRows;
    std::cin >> NumberOfRows;
    std::cout << std::endl << "Enter the number of columns: ";
    int NumberOfColumns;
    std::cin >> NumberOfColumns;
    std::cout << std::endl;
    std::cout << "Now enter the grid" << std::endl;
    char* Grid = new char[NumberOfRows * NumberOfColumns];
    for(int i = 0; i < NumberOfRows; ++i) {
        for (int j = 0; j < NumberOfColumns; ++j) {
            std::cin >> Grid[i*NumberOfColumns+j];
        }
    }
    std::cout << "Enter the number of words in the dictionary: ";
    int NumberOfWordsInTheDictionary;
    std::cin >> NumberOfWordsInTheDictionary;
    std::cout << std::endl;
    std::cout << "Enter the words from the dictionary" << std::endl;
    Dictionary TheDictionary;
    std::string word;
    for(int i = 0; i < NumberOfWordsInTheDictionary; ++i) {
        std::cin >> word;
        TheDictionary.insert(word);
    }

    // solution
    std::set<std::string> Answer = WordsFound(NumberOfRows, NumberOfColumns, Grid, TheDictionary);
    for(const std::string &ans: Answer) {
        std::cout << ans << " ";
    }


    delete[] Grid;
    return 0;
}
