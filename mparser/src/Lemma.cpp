
#include "Form.h"
#include "Lemma.h"

Lemma::Lemma(int lemmaId,
             Form initialForm,
             std::vector<Form> forms)
        : lemma_id(lemmaId),
          initial_form(std::move(initialForm)),
          forms(std::move(forms)) {}

const std::vector<Form> &Lemma::getForms() const {
    return forms;
}

int Lemma::getId() const {
    return lemma_id;
}

std::string Lemma::str() {
    return /*"id: " + std::to_string(lemma_id) + ", "+*/  initial_form.str();
}

const Form &Lemma::getInitialForm() const {
    return initial_form;
}
