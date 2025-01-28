% Defining all the valid knight moves on an NxN board
jump(N, X/Y, U/V) :-
    member((Dx, Dy), [(2,1), (2,-1), (-2,1), (-2,-1), (1,2), (1,-2), (-1,2), (-1,-2)]),
    U is X + Dx, V is Y + Dy,
    U > 0, U =< N, V > 0, V =< N.

% Knight's Tour 
knight_tour(N, Path) :-
    N2 is N * N,
    start_position(N, Start), % Define the starting position
    knight_tour_helper(N, N2, [Start], Path).

% Base case: If all squares are visited, return the path
knight_tour_helper(_, 1, Path, Path).

% Recursive case
knight_tour_helper(N, MovesLeft, [Current | Visited], Path) :-
    MovesLeft > 1,
    jump(N, Current, Next),   % Find a valid knight move
    \+ member(Next, Visited), % Ensure the square is not visited
    MovesLeft1 is MovesLeft - 1,
    knight_tour_helper(N, MovesLeft1, [Next, Current | Visited], Path).

% Define the starting position (top-left corner)
start_position(_, 1/1).


% query:
% knight_tour(5, Path).










