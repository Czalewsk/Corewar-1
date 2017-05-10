.name "C and X tests"
.comment "Don't worry, it's ok"

lol:	ld %0, r2
		ld %1, r2 
		zjmp %:lol
