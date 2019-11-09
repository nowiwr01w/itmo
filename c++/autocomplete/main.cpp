#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include "term.h"
#include "binary_search_deluxe.h"
#include "autocomplete.h"

struct Comp {
    bool operator() (const term & t1, const term & t2) const {
        return t1 < t2;
    }
};

int main() {
    //binary_search_deluxe k; cannot create

    term a0;
    std::cout << a0.to_string() << "\n";

    term a1("There is a hell", 8);
    term a2("Believe me", 7);
    term a3("I've seen it", 2);
    term a4("There is a fail", 5);
    term a5("Let's keep it in secret", 4);
    term a6("Crucify me", 3);
    term a7("I wanna you approve this task", 6);
    term a8("Please, God", 1);

    term array[8] = {a1, a2, a3, a4, a5, a6, a7, a8};

    std::sort(array, array + 8, term::by_prefix_order(5));

    std::cout << "==========Sorting massive==========\n";
    for (term j : array) {
        std::cout << j << "\n";
    }

    std::cout << "==========Now binary search on key: " << a2 << " ==========\n";
    int ind = binary_search_deluxe::first_index_of(array, 10, a2, term::by_prefix_order(4));
    std::cout << ind << " " << array[ind] << "\n";

    std::cout << "==========Now binary search on key with lambda: " << a2 << " ==========\n";
    auto cmp = [](const term & t1, const term & t2) { return t1 < t2; };
    ind = binary_search_deluxe::first_index_of(array, 10, a2, cmp);
    std::cout << ind << " " << array[ind] << "\n";

    std::cout << "==========Now binary search on key with functor: " << a2 << " ==========\n";
    ind = binary_search_deluxe::first_index_of(array, 10, a2, Comp());
    std::cout << ind << " " << array[ind] << "\n";

    std::cout << "========================================" << "\n";

    std::cout << a1.to_string() << "\n" << a2.to_string() << "\n" << a3.to_string() << "\n";
    std::cout << std::boolalpha << (a1 < a2) << " " << (a2 < a3) << " " << (a1 < a3) << " " << (a2 < a1) << "\n";

    std::vector<term> ts;
    ts.push_back(a1);
    ts.push_back(a2);
    ts.push_back(a3);
    ts.push_back(term("Nobody told me that world is gonna roll me", 10));
    std::sort(ts.begin(), ts.end(), term::by_reverse_weight_order());
    std::sort(ts.begin(), ts.end(), term::by_prefix_order(4));
    for (term i : ts) {
        std::cout << i.to_string() << "\n";
    }

    std::cout << "==========TESTING AUTOCOMPLETE==========\nArray c:\n";
    term c[8] = { a1, a2, a3, a4, a5, a6, a7, a8 };
    for (term i : c) {
        std::cout << i << "\n";
    }

    autocomplete autocomplete1(c, 8);
    std::cout << "==========NUM MATCHES==========\n";
    std::cout << "I: " << autocomplete1.number_of_matches("I") << " L: " << autocomplete1.number_of_matches("L") << " T: " << autocomplete1.number_of_matches("T") << "\n";



    return 0;
}