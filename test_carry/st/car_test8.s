.name "C and X tests"
.comment "Don't worry, it's ok"

lol:	st r2, 0 
		st r2, -5 
		zjmp %:lol
