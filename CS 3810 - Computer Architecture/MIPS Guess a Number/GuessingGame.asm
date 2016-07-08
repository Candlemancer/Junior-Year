# Jonathan Petersen
# A01236750
# Guess a Number Game

.data

welcome:	.asciiz		"Guess a number between 1 and 100: "
tooLow:		.asciiz 	"Too low, guess again: "
tooHigh:	.asciiz 	"Too high, guess again: "
correct1:	.asciiz		"Correct! It took you "
correct2:	.asciiz 	" guess to find "
period:		.asciiz 	"."
again:		.asciiz 	"Would you like to play again? (Y/N): "
goodbye:	.asciiz 	"Goodbye!"
endl:		.asciiz		"\n"

.text

start:
# Print the Welcome Message
li	$v0	4
la	$a0	welcome
syscall

#Setup the counter
li	$t5	0

# Generate a random number
li	$v0	41
li	$a0	0
syscall
# Mod by 100
li	$a1	100
div	$a0	$a1
mfhi	$a0
abs	$a0	$a0
#Store in $t1
move	$t1	$a0

# Test Print
# li	$v0	1
# move	$a0	$t1
# syscall

loop:
# Increment counter
add	$t5	$t5	1

# Read in the guess
li	$v0	5
syscall
move	$t0	$v0

# Compare guess with random number
blt	$t0	$t1	less
bgt	$t0	$t1	more
j	endloop

less:
li	$v0	4
la	$a0	tooLow
syscall
j	loop

more:
li	$v0	4
la	$a0	tooHigh
syscall
j	loop

endloop:

# Print out the congratulation message
li	$v0	4
la	$a0	correct1
syscall

li	$v0	1
move	$a0	$t5
syscall

li	$v0	4
la	$a0	correct2
syscall

li	$v0	1
move	$a0	$t1
syscall

li	$v0	4
la	$a0	period
syscall

li	$v0	4
la	$a0	endl
syscall

# Print the play again message
li	$v0	4
la	$a0	again
syscall

# Load in the answer
li	$v0	12
syscall
move	$t4	$v0

li	$v0	4
la	$a0	endl
syscall

# Play again iff input = Y
beq	$t4	89	start

# Print the goodbye Message
li	$v0	4
la	$a0	goodbye
syscall

# End the Program
li	$v0	10
syscall










