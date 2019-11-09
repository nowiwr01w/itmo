//
// Created by iwann on 30.05.2019.
//

#include "term.h"

term::term() : term_str(""), weight(0) {}

term::term(std::string term, unsigned cur_weight) : term_str(std::move((term))), weight(cur_weight) {}

std::string term::to_string() const {
    return std::to_string(weight) + " " + term_str;
}

bool term::operator>(const term &cur_term) const {
    return term_str > cur_term.term_str;
}

bool term::operator<(const term &cur_term) const {
    return term_str < cur_term.term_str;
}

bool term::operator==(const term &cur_term) const {
    return term_str == cur_term.term_str;
}

bool term::operator!=(const term &cur_term) const {
    return term_str != cur_term.term_str;
}

std::ostream &operator<<(std::ostream &os, const term &cur_term) {
    os << cur_term.to_string();
    return os;
}

bool term::WeightFunctor::operator()(const term &left, const term &right) {
    return left.weight > right.weight;
}

term::PrefixFunctor::PrefixFunctor(int length) : pref_length(length) {}

bool term::PrefixFunctor::operator()(const term &left, const term &right) {
    return left.term_str.compare(0, pref_length, right.term_str, 0, pref_length) < 0;
}
