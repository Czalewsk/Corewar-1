.name "C and X tests"
.comment "Don't worry, it's ok"

l2:		sti r1, %:live, %1
l3:		sti r1, %:live, %1

live:	live %1
		ld %1, r5
		sti r5, %:live, %50
		sti r1, %:live, %54
		zjmp %:live
