//
// Created by iwann on 30.05.2019.
//

#ifndef AUTOCOMPLETE_AUTOCOMPLETE_H
#define AUTOCOMPLETE_AUTOCOMPLETE_H

#pragma once

#include "term.h"
#include "binary_search_deluxe.h"
#include <vector>
#include <algorithm>

class autocomplete {
public:
    autocomplete();

    autocomplete(const term *cur_terms, size_t cur_size);

    autocomplete(autocomplete const &other);

    autocomplete &operator=(autocomplete const &other);

    int number_of_matches(const std::string &prefix);

    std::vector<term> all_matches(const std::string &prefix);

    ~autocomplete();

private:
    std::pair<int, int> getBounds(const std::string &prefix);

    term *terms;
    unsigned size;
    binary_search_deluxe &bsd;
};

#endif //AUTOCOMPLETE_AUTOCOMPLETE_H
