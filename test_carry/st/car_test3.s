.name "C and X tests"
.comment "Don't worry, it's ok"

ld %0, r3
lol:	st r2, r2
		zjmp %:lol
