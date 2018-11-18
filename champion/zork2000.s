.name "zork 2000"
.comment "That's'll folks!"

		live %1
l1:		ld %656, r2
		ld %1, r3
		st r2, -505
		st r3, -505
		st r1, -511
		fork %511
		st r2, -490
		st r3, -490
		st r1, -496
		st r2, -100
		st r3, -100
		st r1, -106
l2:		sti r1, %:live, %1
		and r2, %0, r2

live:	live %1
		zjmp %:live
