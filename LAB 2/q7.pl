compress([],[]).
compress([H], [H]).
compress([H,H|T], X) :- compress([H|T],X).
compress([H|T], [H|X]) :- compress(T, X).

% query:
% compress([a,a,a,a,b,c,c,a,a,d,e,e,e,e],X).


