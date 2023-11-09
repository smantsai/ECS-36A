/* This program checks if two words are anagrams. */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

/**
 * Sees if the two words have equal character sums
 * @param word1: the first word the user inputs
 * @param word2: the second word the user inputs
 * @return: a boolean, true if the sums are equal, false if unequal
 */
bool sumsEqual(char word1[], char word2[]) {
    int sumWord1 = 0;
    int sumWord2 = 0;
    for (int i = 0; i < strlen(word1); i++) {
        sumWord1 += tolower(word1[i]);
        sumWord2 += tolower(word2[i]);
    }

    if (sumWord1 == sumWord2) {
        return true;
    } else {
        return false;
    }
}

/**
 * Sees if the two words are anagrams or not.
 * @param word1: the first word the user inputs
 * @param word2: the second word the user inputs
 * @return: a boolean, true if the words are anagrams, otherwise return false
 */
bool checkWords(char word1[], char word2[]) {
    bool sums = sumsEqual(word1, word2);
    if (strlen(word1) == strlen(word2) && sums){ 
        for (int i = 0; i < strlen(word1); i++) { // checks every letter in word 1 is found in word2
            bool foundChar = false;
            for (int j = 0; j < strlen(word2); j++) {
                if (tolower(word1[i]) == tolower(word2[j])){
                    foundChar = true;
                    break;
                }
            }
            if (foundChar == false) {
                return false;
            }
        }
        for (int i = 0; i < strlen(word2); i++) { // checks every letter in word2 is found in word1
            bool foundChar = false;
            for (int j = 0; j < strlen(word1); j++) {
                if (tolower(word2[i]) == tolower(word1[j])){
                    foundChar = true;
                    break;
                }
            }
            if (foundChar == false) {
                return false;
            }
        }
    }
    else {
        return false;
    }

    return true;
}

/**
 * Tells the user if the two strings are anagrams
 * @param isAnagram: a boolean saying if the words are anagrams
 * @param wordA: the first word the user had input in earlier
 * @param wordB: the second word the user had put in
 * @return: nothing b/c function is void
 */
void printAnagram(bool isAnagram, char wordA[], char wordB[]) {
    if (isAnagram) {
        printf("%s is an anagram of %s", wordA, wordB);
    }
    else { 
        printf("%s is NOT an anagram of %s", wordA, wordB);
    }
}

int main() {
    char word1[21];
    char word2[21];
    bool isAnagram;

    printf("Please enter the first word: ");
    scanf("%s", word1);
    printf("Please enter the second word: ");
    scanf("%s", word2);

    isAnagram = checkWords(word1, word2);

    printAnagram(isAnagram, word1, word2);

}