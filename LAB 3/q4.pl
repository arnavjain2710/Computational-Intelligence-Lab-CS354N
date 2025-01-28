% Check if the given board is a valid solution
safe([]).
safe([X|Xs]) :- safe(Xs), no_attack(X, Xs, 1).

% Ensuring that no two queens are attacking each other
no_attack(_, [], _).
no_attack(X, [Y|Ys], N) :- 
    X =\= Y,                 % Not in the same row
    X =\= Y + N,             % Not in the same diagonal ( \ )
    X =\= Y - N,             % Not in the same diagonal ( / )
    N1 is N + 1,
    no_attack(X, Ys, N1).

% Generate a permutation of [1..N] and check if it is a valid solution
queens(N, Solution) :- 
    numlist(1, N, List),      % Generate [1,2,...,N]
    permutation(List, Solution), 
    safe(Solution).

solve_queens(Solution) :- 
    queens(8, Solution).


% query:
% solve_queens(Solution).

















