reverse([],A,A).
reverse([H|T],A,Acc) :- reverse(T,A,[H|Acc]).
palindrome(L):- reverse(L, L, []).

% query:
% palindrome([1, 2, 3, 2, 1]).
% palindrome([1, 2, 3, 2]).