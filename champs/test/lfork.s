.name "zxork"
.comment "I'M ALIIIIVE"

lds: live %1 
	lfork %:lds14
lds1: live %1 
	lfork %:lds1
lds2: live %1 
	lfork %:lds1
lds3: live %1 
	lfork %:lds1
	and r1, %0, r1
	zjmp %:lds1
lds4: live %1 
	lfork %1
lds5: live %1 
	lfork %513
lds6: live %1 
	lfork %:lds
lds7: live %1
	lfork %2011
lds8: live %1 
	lfork %-2011
lds9: live %1 
	lfork %-513
lds11: live %1 
	lfork %:lds
lds12: live %1 
	lfork %:lds
lds13: live %1 
	lfork %:lds
lds14:
	lfork %:lds4
