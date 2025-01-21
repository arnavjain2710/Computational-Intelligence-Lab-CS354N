combination(0, _, []).

combination(K, [H|T], [H|Comb]) :- K > 0 , K1 is K - 1, combination(K1, T, Comb). 

combination(K, [_|T], Comb) :- K > 0, combination(K, T, Comb).  

% query:
% combination(3,[a,b,c,d,e,f],L).
