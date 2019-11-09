//
// Created by iwann on 30.05.2019.
//

#include <vector>
#include "autocomplete.h"

autocomplete::autocomplete() : terms(nullptr), size(0), bsd(binary_search_deluxe::create_new_object()) {};

autocomplete::autocomplete(const term *cur_terms, unsigned cur_size) : size(cur_size),
                                                                       bsd(binary_search_deluxe::create_new_object()) {
    terms = new term[size];
    for (unsigned i = 0; i < size; ++i) {
        terms[i] = cur_terms[i];
    }
    std::sort(terms, terms + size);
}

std::vector<term> autocomplete::all_matches(std::string const &prefix) {
    std::pair<int, int> bounds = getBounds(prefix);
    std::vector<term> matches(bounds.second - bounds.first);
    for (int i = bounds.first; i < bounds.second; ++i) {
        matches[i - bounds.first] = terms[i];
    }
    std::sort(matches.begin(), matches.begin() + bounds.second - bounds.first, term::by_reverse_weight_order());
    return matches;
}

int autocomplete::number_of_matches(std::string const &prefix) {
    std::pair<int, int> bounds = getBounds(prefix);
    return bounds.second - bounds.first;
}

std::pair<int, int> autocomplete::getBounds(std::string const &prefix) {
    auto cmp_by_prefix = term::by_prefix_order(prefix.size());
    term key(prefix, 0);
    int left = bsd.first_index_of(terms, size, key, cmp_by_prefix);
    int right = bsd.last_index_of(terms, size, key, cmp_by_prefix);
    return std::make_pair(left, right);
}

autocomplete::autocomplete(autocomplete const &other) : autocomplete(other.terms, other.size) {}

autocomplete &autocomplete::operator=(autocomplete const &other) {
    autocomplete tmp(other);
    std::swap(tmp.terms, terms);
    std::swap(tmp.size, size);
    return *this;
}

autocomplete::~autocomplete() {
    delete[] terms;
}