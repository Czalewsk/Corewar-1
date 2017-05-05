.name "zork"
.comment "I'M ALIIIIVE"

l2:		sti r0, %:live, %1
live:	and r1, %0, r1

live:	live %1
		zjmp %:live