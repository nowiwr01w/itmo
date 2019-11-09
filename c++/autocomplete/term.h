//
// Created by iwann on 30.05.2019.
//

#ifndef AUTOCOMPLETE_TERM_H
#define AUTOCOMPLETE_TERM_H

#include <string>

class term {

public:
    term();

    term(std::string term, unsigned cur_weight);

    bool operator>(const term &cur_term) const;

    bool operator<(const term &cur_term) const;

    bool operator==(const term &cur_term) const;

    bool operator!=(const term &cur_term) const;

    std::string to_string() const;

    friend std::ostream &operator<<(std::ostream &os, const term &cur_term);

    struct WeightFunctor {
        bool operator()(const term &left, const term &right);
    };

    struct PrefixFunctor {
        explicit PrefixFunctor(int length);

        bool operator()(const term &left, const term &right);

    private:
        int pref_length;
    };

    static WeightFunctor by_reverse_weight_order() {
        return WeightFunctor();
    }

    static PrefixFunctor by_prefix_order(int length) {
        return PrefixFunctor(length);
    }

    term(term &&t) = default;

    term(const term &t) = default;

    term &operator=(term &&t) = default;

    term &operator=(const term &t) = default;

private:
    unsigned weight;
    std::string term_str;
};

#endif //AUTOCOMPLETE_TERM_H
