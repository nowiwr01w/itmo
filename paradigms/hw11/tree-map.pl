rand_list([], []).
rand_list([(X, Value) | Tail], Res) :- 
	rand_int(100, Y), rand_list(Tail, NewTail), Res = [(Y, X, Value) | NewTail].

merge(Treap1, Treap2, Treap) :-
	(Treap1 == nil, Treap2 == nil -> Treap = nil;
		Treap1 == nil -> Treap = Treap2;
			Treap2 == nil -> Treap = Treap1).
merge(tree((Y1, X1, Value1), L1, R1), tree((Y2, X2, Value2), L2, R2), Treap) :- 
	(Y1 > Y2 -> Treap = tree((Y1, X1, Value1), L1, NewR), merge(R1, tree((Y2, X2, Value2), L2, R2), NewR);
		Treap = tree((Y2, X2, Value2), NewL, R2), merge(tree((Y1, X1, Value1), L1, R1), L2, NewL)).

split(nil, Key, (nil, nil)).
split(tree((Y, X, Value), L, R), Key, (Treap1, Treap2)) :-
	(Key > X -> split(R, Key, (NewTreap1, NewTreap2)), Treap1 = tree((Y, X, Value), L, NewTreap1), Treap2 = NewTreap2;
		split(L, Key, (NewTreap1, NewTreap2)), Treap1 = NewTreap1, Treap2 = tree((Y, X, Value), NewTreap2, R)).
		
build_treap([], 	nil).
build_treap([Head | Tail], Treap) :- build_treap(Tail, TreapPart), merge(tree(Head, nil, nil), TreapPart, Treap).

tree_build(List, Tree) :- rand_list(List, RandomList), build_treap(RandomList, Tree).

map_get(tree((Y, Key, Value), L, R), Key, Value).
map_get(tree((Y, X, CurValue), L, R), Key, Value) :-
	(Key > X -> map_get(R, Key, Value);
		Key < X -> map_get(L, Key, Value)).

map_replace(nil, Key, Value, nil).
map_replace(tree((Y, X, CurValue), L, R), Key, Value, Res) :- 
	(Key > X -> map_replace(R, Key, Value, NewR), Res = tree((Y, X, CurValue), L, NewR);
		Key < X -> map_replace(L, Key, Value, NewL), Res = tree((Y, X, CurValue), NewL, R);
			Res = tree((Y, X, Value), L, R)).

map_put(Treap, Key, Value, Res) :-
	(map_replace(Treap, Key, Value, Try), Try == Treap -> 
		split(Treap, Key, (Treap1, Treap2)), rand_int(100, Y), 
		merge(Treap1, tree((Y, Key, Value), nil, nil), Treap3), merge(Treap3, Treap2, Res);
			map_replace(Treap, Key, Value, Res)).

map_remove(Treap, Key, Res) :- 
	split(Treap, Key, (Treap1, Treap2)), split(Treap2, Key + 1, (Treap3, Treap4)), merge(Treap1, Treap4, Res).

map_size(nil, 0).
map_size(tree((Y, X, Value), L, R), Size) :- map_size(L, SizeL), map_size(R, SizeR), Size is SizeL + SizeR + 1.