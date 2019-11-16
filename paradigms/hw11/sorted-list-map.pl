map_get([(H1, H2) | T], Key, Value) :- H1 = Key, H2 = Value, !.
map_get([(H1, H2) | T], Key, Value) :- H1 < Key, map_get(T, Key, Value).

map_put([], Key, Value, [(Key, Value)]).
map_put([(Key, H2) | T], Key, Value, [(Key, Value) | T]).
map_put([(H1, H2) | T], Key, Value, [(Key, Value), (H1, H2) | T]) :- H1 > Key.
map_put([(H1, H2) | T], Key, Value, [(H1, H2) | R1]) :- H1 < Key, map_put(T, Key, Value, R1).

map_remove([], Key, []).
map_remove([(H1, H2) | Result], H1, Result).
map_remove([(H1, H2) | T], Key, [(H1, H2) | T]) :- H1 > Key.
map_remove([(H1, H2) | T], Key, [(H1, H2) | R1]) :- H1 < Key, map_remove(T, Key, R1).

map_floorKey([(H1, H2)], Key, Result) :- Key >= H1, Result is H1, !.
map_floorKey([(H1, H2), (H3, H4) | R], Key, Result) :- Key >= H1, H3 >  Key, Result is H1, !.
map_floorKey([(H1, H2) | T], Key, Result) :- Key > H1, map_floorKey(T, Key, Result).