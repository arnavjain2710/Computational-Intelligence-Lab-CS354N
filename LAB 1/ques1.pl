lives(british, red).
lives(diplomat, yellow).
lives(norwegian, 1).
lives(doctor, X) :- near(X, Y), owns(Z, fox), lives(Z, Y).
lives(norwegian, X) :- near(X, blue).

owns(spanish, dog).
owns(sculptor, snails).

drinks(X, coffee) :- lives(X, green).
drinks(ukrainian, tea).
drinks(X, milk) :- middle(X).
drinks(violinist, orangejuice).

right(green, white).
horse(X) :- near(X, diplomat), owns(X, horse).
same(japanese, acrobat).

% assuming 5 houses , to get the middle house index
house(1).
house(2).
house(3).
house(4).
house(5).
middle(3).

% near can be used with index as well as other variables
near(norwegian, blue).
near(X,Y):- near(Y,X).
near(X, Y) :- X is Y - 1.
near(X, Y) :- X is Y + 1.

% queries - 
% drinks(X, water), owns(X, zebra).
% drinks(X, water).
% owns(X, zebra).











