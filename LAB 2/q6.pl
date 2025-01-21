my_flatten([],[]):- !.
my_flatten(A,[A]) :- \+ is_list(A).
my_flatten([A|A1],C1) :- my_flatten(A,B), my_flatten(A1,B1), append(B,B1,C1).

% query:
% my_flatten([a, [b, [c, d], e]], X).
% my_flatten([a, [b, [c, d], e, [x , y , z , p]]], X).
