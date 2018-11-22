.name "zork 2000"
.comment "That's'll folks!"

l1:		live %1
		ld %656, r2
		ld %1, r3
		ld %0, r4
		aff r3
		fork %:reset
		ld %2, r5
		aff r5
l6:		live %1
		sub r5, r3, r5
		aff r5
		zjmp %:l6
		aff r16
		aff r16
		zjmp %:l6
reset:
