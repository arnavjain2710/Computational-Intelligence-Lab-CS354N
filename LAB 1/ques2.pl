happy(X) :- parent(X, _).
hastwochildren(X) :- parent(X, Y), parent(X,Z) , Y\=Z ,sister(Z, Y).
grandchild(X, Y) :- parent(Y, Z), parent(Z, X).  % X is grandchild of Y
aunt(X, Y) :- sister(X, Z), parent(Z, Y). % X is aunt of Y