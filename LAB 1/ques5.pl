parent(chester,irvin). 
parent(chester,clarence). 
parent(chester,mildred). 
parent(irvin,ron).
parent(irvin,ken). 
parent(clarence,shirley). 
parent(clarence,sharon).
parent(clarence,charlie). 
parent(mildred,mary).

ancestor(X, Y):- parent(X, Y).
ancestor(X, Y):- parent(X, Z), ancestor(Z, Y).


% queries - 
% parent(chester,mildred).
% parent(X,ron).
% parent(clarence,charlie). 





