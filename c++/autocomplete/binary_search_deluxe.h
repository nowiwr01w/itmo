//
// Created by nowiwr01 on 30.05.2019.
//

#ifndef AUTOCOMPLETE_BINARY_SEARCH_DELUXE_H
#define AUTOCOMPLETE_BINARY_SEARCH_DELUXE_H

#include <algorithm>
#include "term.h"

class binary_search_deluxe {
public:
    template<typename F>
    static int first_index_of(const term *terms, unsigned size, const term &value, F cmp) {
        const term *first = std::lower_bound(terms, terms + size, value, cmp);
        return std::distance(terms, first);
    }

    template<typename F>
    int last_index_of(const term *terms, unsigned size, const term &value, F cmp) {
        const term *second = std::upper_bound(terms, terms + size, value, cmp);
        return std::distance(terms, second);
    }

    static binary_search_deluxe &create_new_object() {
        static binary_search_deluxe new_object;
        return new_object;
    }

private:
    binary_search_deluxe() = default;

    binary_search_deluxe(const binary_search_deluxe &obj) = default;

    binary_search_deluxe &operator=(const binary_search_deluxe &obj) = default;

};
#endif //AUTOCOMPLETE_BINARY_SEARCH_DELUXE_H
