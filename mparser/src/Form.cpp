
#include <sstream>
#include <iterator>
#include "Form.h"

const std::vector<std::string> &Form::getPropNames() const {
    return prop_names;
}

Form::Form(std::string word, std::vector<std::string> propNames) :
        word(std::move(word)), prop_names(std::move(propNames)) {

}

const std::string &Form::getWord() const {
    return word;
}

std::string Form::str() {
    std::stringstream stringstream;
    stringstream << word << ": ";

    std::copy(prop_names.begin(),
              prop_names.begin()+1,
              std::ostream_iterator<std::string>(stringstream, " "));

    return stringstream.str();
}
