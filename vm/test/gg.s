.name "zxork"
.comment "I'M ALIIIIVE"

lds: live %1 
	fork %510
	and r1, %0, r1
	zjmp %:lds
