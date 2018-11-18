.name "zork 2000"
.comment "That's'll folks!"

l1:		ld %656, r2
		ld %1, r3
		st r2, -49
		st r3, -49
		st r1, -55
		fork %:live
l2:		sti r1, %:live, %1
		and r2, %0, r2

live:	live %1
		zjmp %:live
