travel(e,w).
travel(w,e). 

transfer([X,Wolf,Goat,X],cabbage,[Y,Wolf,Goat,Y]) :- travel(X,Y).
transfer([X,Wolf,X,Cabbage],goat,[Y,Wolf,Y,Cabbage]) :- travel(X,Y).
transfer([X,Wolf,Goat,Cabbage],nothing,[Y,Wolf,Goat,Cabbage]) :- travel(X,Y).
transfer([X,X,Goat,Cabbage],wolf,[Y,Y,Goat,Cabbage]) :- travel(X,Y).

is_safe([X,_,X,_]).
is_safe([X,X,_,X]). 
answer([e,e,e,e],[]).

answer(State,[FirstMove|OtherMoves]) :- transfer(State, FirstMove, NextState), is_safe(NextState), answer(NextState, OtherMoves).
