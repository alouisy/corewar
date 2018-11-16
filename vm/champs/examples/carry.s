.name "tester"
.comment "test ldi"

ld %0, r2
zjmp %3
ldi %-4, %0, r4
zjmp %0
