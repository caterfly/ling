#pragma once

#include "Form.h"

class Lemma {
private:
    int lemma_id;
    Form initial_form;
public:
    const Form &getInitialForm() const;

private:
    std::vector<Form> forms;

public:
    Lemma(int lemmaId, Form initialForm, std::vector<Form> forms);

    const std::vector<Form> &getForms() const;

    int getId() const;

    std::string str();
};