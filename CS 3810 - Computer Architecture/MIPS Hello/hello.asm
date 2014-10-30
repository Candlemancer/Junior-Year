# Jonathan Petersen
# A01236750
# MIPS Hello World Assignment

.data

string:	.asciiz	"Hello World! My name is Jonathan Petersen and my major is Computer Science!"
	
.text

#syscall executes the command specified by $v0 and passes in the argument in $a0
li	$v0	4
la	$a0	string
syscall

#syscall 10 exits the program.
li	$v0	10
syscall

