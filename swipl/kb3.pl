can_cook(priya).
can_cook(jasmin).
can_cook(timoteo).

like(priya,jasmin) :- can_cook(jasmin).
like(priya,timoteo) :- can_cook(timoteo).