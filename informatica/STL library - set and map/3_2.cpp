#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <cctype>
#include <algorithm>

// Функция для разделения текста на предложения
std::vector<std::string> splitTextIntoSentences(const std::string& text) {
    std::vector<std::string> sentences;
    size_t start = 0;
    for (size_t i = 0; i <= text.size(); ++i) {
        if (i == text.size() || text[i] == '.' || text[i] == '!' || text[i] == '?') {
            if (start < i) {
                sentences.emplace_back(text.substr(start, i - start));
            }
            start = i + 1;
        }
    }
    return sentences;
}

// Функция для определения типа предложения
bool isDeclarativeSentence(const std::string& sentence) {
    if (sentence.back() == '.') {
        return true;
    }
    return false;
}

// Функция для извлечения слов из предложения
std::vector<std::string> extractWordsFromSentence(const std::string& sentence) {
    std::vector<std::string> words;
    std::string currentWord;
    for (char c : sentence) {
        if (std::isalpha(c)) {
            currentWord += std::tolower(c);
        } else if (!currentWord.empty()) {
            words.push_back(currentWord);
            currentWord.clear();
        }
    }
    if (!currentWord.empty()) {
        words.push_back(currentWord);
    }
    return words;
}

// Основная функция для нахождения слов, встречающихся только в повествовательных предложениях
std::set<std::string> findUniqueWordsInDeclarativeSentences(const std::string& text) {
    std::vector<std::string> sentences = splitTextIntoSentences(text);
    std::set<std::string> declarativeWords;
    std::set<std::string> otherWords;
    for (const std::string& sentence : sentences) {
        if (isDeclarativeSentence(sentence)) {
            for (const std::string& word : extractWordsFromSentence(sentence)) {
                declarativeWords.insert(word);
            }
        } else {
            for (const std::string& word : extractWordsFromSentence(sentence)) {
                otherWords.insert(word);
            }
        }
    }
    std::set<std::string> uniqueWords;
    for (const std::string& word : declarativeWords) {
        if (otherWords.find(word) == otherWords.end()) {
            uniqueWords.insert(word);
        }
    }
    return uniqueWords;
}

int main() {
    std::string text = "Привет! Как дела? Я рад тебя видеть. Сегодня отличная погода.";
    std::set<std::string> uniqueWords = findUniqueWordsInDeclarativeSentences(text);
    for (const std::string& word : uniqueWords) {
        std::cout << word << " ";
    }
    std::cout << std::endl;
    return 0;
}
