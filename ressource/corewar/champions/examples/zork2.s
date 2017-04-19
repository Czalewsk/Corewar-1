.name "zork"
.comment "I'M ALIIIIVE"

l2:		sti r1,  %1, %0
		and r1, %0, r1
		fork %15

live:	live %1
		zjmp %:live
