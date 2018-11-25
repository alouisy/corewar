.name "fork"
.comment "I'M ALIIIIVE"

lds: live %1 
	fork %:lds4
lds4: ld %1, r4 
	ld %18, r3
ld:	live %1
	sub r3, r4, r3
	zjmp %:ld2
	fork %:ld
	and r2, r2, r2
	zjmp %:ld
ld2:
	and r2, r2, r2
	zjmp %:ld2
