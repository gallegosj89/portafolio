% nl significa New Line

count_to_10(10) :- write(10),nl.
count_to_10(X) :-
   write(X),nl,
   Y is X + 1,
   count_to_10(Y).

count_down(L, H) :-
   between(L, H, Y),
   Z is H - Y,
   write(Z), nl.

count_up(L, H) :-
   between(L, H, Y),
   Z is L + Y,
   write(Z), nl.