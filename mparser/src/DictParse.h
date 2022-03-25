#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include <optional>
#include "Dict.h"

class DictParse {
public:
    explicit DictParse(std::istream &istream);

    DictParse();

    DictParse(const DictParse &rhs);

    DictParse(DictParse &&rhs) noexcept;

    DictParse &operator=(const DictParse &other);

    DictParse &operator=(DictParse &&other) noexcept;

    DictParse &operator+=(const DictParse &rhs);

    DictParse operator+(const DictParse &rhs) const;

    std::string str(int limit, std::set<std::string> &props) const;

    void setDict(Dict *corpaDict);

    int countWords();

private:
    void readWords(std::istream &istream);

    void countWordsFreq();

private:
    Dict *dict = nullptr;
    std::vector<std::string> tokens;
    std::unordered_map<std::string, int> wordToCount;

    void stripWords();

};