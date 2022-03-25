
#include <sstream>
#include "DictParse.h"

DictParse::DictParse(std::istream &inputStream) {
    readWords(inputStream);
    stripWords();
    countWordsFreq();
    toLower();
}

void DictParse::readWords(std::istream &inputStream) {
    std::string word;
    while (!inputStream.eof()) {
        inputStream >> word;
        tokens.push_back(std::move(word));
    }
}

void DictParse::countWordsFreq() {
    for (auto &word: tokens) {
        if (!wordToCount.contains(word)) {
            wordToCount[word] = 0;
        }
        wordToCount[word]++;
    }
}

DictParse &DictParse::operator+=(const DictParse &rhs) {
    std::for_each(rhs.wordToCount.begin(), rhs.wordToCount.end(), [this](auto &it) {
        if (!this->wordToCount.contains(it.first)) {
            this->wordToCount[it.first] = 0;
        }
        this->wordToCount[it.first] += it.second;
    });
    tokens.insert(tokens.end(), rhs.tokens.begin(), rhs.tokens.end());
    return *this;
}

DictParse DictParse::operator+(const DictParse &rhs) const {
    DictParse lhs = *this;
    lhs += rhs;
    return lhs;
}

DictParse::DictParse(DictParse &&rhs) noexcept {
    *this = std::move(rhs);
}

DictParse::DictParse(const DictParse &rhs) = default;

DictParse &DictParse::operator=(const DictParse &rhs) {
    this->wordToCount = rhs.wordToCount;
    this->dict = rhs.dict;
    this->tokens = rhs.tokens;
    return *this;
};

DictParse &DictParse::operator=(DictParse &&rhs) noexcept {
    wordToCount = std::move(rhs.wordToCount);
    tokens = std::move(rhs.tokens);
    this->dict = rhs.dict;
    return *this;
}

std::string DictParse::str(int limit, std::set<std::string> &props) const {
    std::vector<std::pair<std::string, int>> v;
    v.resize(wordToCount.size());
    std::copy(wordToCount.begin(), wordToCount.end(), v.begin());
    std::sort(v.begin(), v.end(), [](auto &left, auto &right) {
        return left.second > right.second;
    });
    int i = 0;
    std::stringstream result;
    for (auto &[word, count]: v) {
        std::stringstream stringstream;
        if (i > limit) {
            break;
        }
        stringstream << word << ": " << count << ", lemmas - ";
        if (dict == nullptr) {
            continue;
        }
        auto lemmasIdSet = dict->getWordLemmas(word);
        if (lemmasIdSet.size() == 0) {
            stringstream << "Cannot find lemmas";
            continue;
        }
        Lemma first_lemma = dict->getLemma(*lemmasIdSet.begin());
        if (!props.empty()) {
            std::set<std::string> intersect;
            std::set<std::string> lemmasPropSet(first_lemma.getInitialForm().getPropNames().begin(),
                                                first_lemma.getInitialForm().getPropNames().end());
            std::set_intersection(props.begin(), props.end(),
                                  lemmasPropSet.begin(), lemmasPropSet.end(),
                                  std::inserter(intersect, intersect.begin()));
            if (intersect.empty()) {
                continue;
            }
        }

        for (auto id: lemmasIdSet) {
            stringstream << " " << dict->getLemma(id).str();
        }

        i++;

        stringstream << std::endl;
        result << stringstream.str();
    }
    return result.str();
}

void DictParse::setDict(Dict *corpaDict) {
    this->dict = corpaDict;
}

void DictParse::stripWords() {
    for (auto &s: tokens) {
        for (int i = s.length() - 1; i >= 0; i--) {
            if (::ispunct(s[i])) {
                s.erase(i, 1);
            }
        }
    }
}


int DictParse::countWords() {
    return tokens.size();
}


DictParse::DictParse() = default;
