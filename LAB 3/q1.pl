
gcd(X, 0, X) :- X > 0.

gcd(X, Y, G) :- Y > 0, R is X mod Y, gcd(Y, R, G).              

% query:
% gcd(36, 63, G).
















