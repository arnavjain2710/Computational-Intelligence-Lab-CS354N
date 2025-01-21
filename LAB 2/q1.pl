reverse([], []).
reverse([H|T], Rev) :- reverse(T, RT), append(RT, [H], Rev).

% reverse([1, 2, 3, 4], Rev).





