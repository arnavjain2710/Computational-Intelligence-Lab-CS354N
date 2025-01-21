text(0,zero).
text(1,one).
text(2,two).
text(3,three).
text(4,four).
text(5,five).
text(6,six).
text(7,seven).
text(8,eight).
text(9,nine).

hyphen(0) :- !.
hyphen(Q) :- Q > 0, write('-'). 

full_words(0) :- !, write(zero), nl.
full_words(N) :- integer(N), N > 0, full_words1(N), nl.

full_words1(0) :- !.
full_words1(N) :- N > 0, Q is N // 10, R is N mod 10, full_words1(Q), text(R,RW), hyphen(Q), write(RW).