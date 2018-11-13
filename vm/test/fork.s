.name "zxork"
.comment "I'M ALIIIIVE"

lds: live %1 
	fork %:lds14
lds1: live %1 
	fork %:lds1
lds2: live %1 
	fork %:lds1
lds3: live %1 
	fork %:lds1
	and r1, %0, r1
	zjmp %:lds1
lds4: live %1 
	fork %1
lds5: live %1 
	fork %513
lds6: live %1 
	fork %:lds
lds7: live %1
	fork %511
lds8: live %1 
	fork %-511
lds9: live %1 
	fork %-513
lds10: live %1 
	fork %4095
lds11: live %1 
	fork %:lds
lds12: live %1 
	fork %:lds
lds13: live %1 
	fork %:lds
lds14: live %1 
	fork %:lds4
