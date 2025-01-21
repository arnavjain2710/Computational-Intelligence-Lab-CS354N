prime(2).
prime(3).
prime(N) :- integer(N), N > 3, N mod 2 =\= 0, \+ has_factor(N,3).  

has_factor(N,L) :- N mod L =:= 0.
has_factor(N,L) :- L * L < N, L2 is L + 2, has_factor(N,L2).

next_prime(P,P1) :- P1 is P + 2, prime(P1), !.
next_prime(P,P1) :- P2 is P + 2, next_prime(P2,P1).

goldbach(4,[2,2]) :- !.
goldbach(N,L) :- N mod 2 =:= 0, N > 4, goldbach(N,L,3).
goldbach(N,[P,Q],P) :- Q is N - P, prime(Q), !.
goldbach(N,L,P) :- P < N, next_prime(P,P1), goldbach(N,L,P1).