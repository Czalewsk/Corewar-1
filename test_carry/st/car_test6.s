.name "C and X tests"
.comment "Don't worry, it's ok"

ld %0, r3
lol:	st r1, 0 
		zjmp %:lol
