#include <iostream>
#include <string>
#include "src/Dict.h"
#include "src/DictParse.h"
#include <filesystem>
#include <fstream>


int main() {
    system("chcp 65001");

    Dict dict("../dict/dict.opcorpora.xml");
    std::string path("../res");

    std::vector<DictParse> texts;

    for (const auto &entry: std::filesystem::directory_iterator(path)) {
        std::fstream f(entry.path(), std::ios::in);
        texts.emplace_back(f);
    }

    DictParse result;
    result.setDict(&dict);
    for (auto &text: texts) {
        result += text;
    }
    std::streambuf *bak;
    std::ofstream file;

    file.open("../out/out.txt");
    bak = std::cout.rdbuf();

    std::cout.rdbuf(file.rdbuf());


    std::cout << result.str(result.countWords());
    std::cout.rdbuf(bak);
    return 0;
}