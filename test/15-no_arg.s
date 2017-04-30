.name "zork"
.comment "I'M ALIIIIVE"

l2:		sti r0, %:live, %1
		and

live:	live %1
		zjmp %:live