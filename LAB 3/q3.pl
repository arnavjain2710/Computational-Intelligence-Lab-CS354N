% Define state transitions
move(walk(To), state(Current, floor, Box, Has), state(To, floor, Box, Has)) :- dif(Current, To), member(To, [door, window, middle]).
move(push_box(To), state(Pos, floor, Pos, Has), state(To, floor, To, Has)) :- dif(Pos, To), member(To, [door, window, middle]).
move(climb, state(Pos, floor, Pos, Has), state(Pos, on_box, Pos, Has)).
move(grasp, state(middle, on_box, middle, no), state(middle, on_box, middle, yes)).

% Initial and goal states
initial_state(state(door, floor, window, no)).
goal_state(state(_, _, _, yes)).

% Iterative deepening search
solve(Actions) :- between(1, 10, Limit), length(Actions, Limit), initial_state(Start), path(Start, Actions, [Start]).

path(State, [], _) :- goal_state(State).

path(State1, [Action|Actions], Visited) :- move(Action, State1, State2), \+ member(State2, Visited), path(State2, Actions, [State2|Visited]).

% Solution formatting
print_solution([]) :-  format('The monkey has grasped the banana!~n').
print_solution([A|As]) :-  format('Action: ~w~n', [A]), print_solution(As).

monkey_banana :- solve(Actions), print_solution(Actions), !.
monkey_banana :-  format('No solution found.~n').

% query:
% monkey_banana.














