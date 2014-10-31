# Jonathan Petersen
# A01236750
# MIPS Calculator Assignment
# Use the Stack to pass arguments


.data

equationPrompt:		.asciiz		"Equation: "
answerPrompt:		.asciiz		"Answer: "
inputString:		.space		16
endl:			.asciiz		"\n"


.text

###############################
# Main
###############################

# Create Space for the three arguments.
	sub	$sp	$sp	12

runLoop:
# Print the equation prompt
	li	$v0	4
	la	$a0	equationPrompt
	syscall

# Read in the input
	jal	getInput

# Switch based on operation
	la	$ra	endSwitch
	lw	$t0	4($sp)
	beq	$t0	0x2B	addition
	beq	$t0	0x2D	subtraction
	beq	$t0	0x2A	multiplication
	beq	$t0	0x2F	division
	beq	$t0	0x21	factorial
endSwitch:
	move	$t0	$v0

# Print the result prompt
	li	$v0	4
	la	$a0	answerPrompt
	syscall

# Print the result
	li	$v0	1
	move 	$a0	$t0
	syscall
	
# Print an endl
	li	$v0	4
	la	$a0	endl
	syscall
	
	j	runLoop
endLoop:

# Close the program
	li	$v0	10
	syscall
###############################


###############################
# Get Input
###############################
getInput:

# Read in the string
	li	$v0	8
	la	$a0	inputString
	li	$a1	16
	syscall

# Parse the input
	li	$t0	0
	li	$t1	0
	li	$a0	0
parseLoop:
	#Load a character
	lbu	$t0	inputString($a0)
	beq	$t0	0	endParse	# Null
	beq	$t0	0x0A	endParse	# Endl
	beq	$t0	0x20	nextChar	# Space
	beq	$t0	0x2B	op		# +
	beq	$t0	0x2D	op		# -
	beq	$t0	0x2A	op		# *
	beq	$t0	0x2F	op		# /
	beq	$t0	0x21	op		# !
	beq	$t0	0x51	endLoop		# Q
	beq	$t0	0x71	endLoop		# q
	beq	$t0	0x45	endLoop		# E
	beq	$t0	0x65	endLoop		# e
	blt	$t0	0x30	endParse	# Error low
	bgt	$t0	0x39	endParse	# Error high

	# Convert Ascii to numberic value
	sub	$t0	$t0 	48

	# Move the decimal place and add the new digit
	mul	$t1	$t1	10
	add	$t1	$t1	$t0

	b	nextChar

op:
	# Reinitialize the number
	sw	$t1	0($sp)
	li	$t1	0

	# Store the operator
	sw	$t0	4($sp)

nextChar:
	addi	$a0	$a0	1
	b	parseLoop
endParse:
	sw	$t1	8($sp)

	# Go home drunk, you're kid
	jr	$ra
###############################


###############################
# Addition
###############################
addition:
	lw	$t0	0($sp)
	lw	$t1	8($sp)
	
	add	$v0	$t0	$t1
	
	jr	$ra
###############################


###############################
# Subtraction
###############################
subtraction:
	lw	$t0	0($sp)
	lw	$t1	8($sp)	

	sub	$v0	$t0	$t1

	jr	$ra
###############################


###############################
# Multiplication
###############################
multiplication:
	lw	$t0	0($sp)
	lw	$t1	8($sp)

	mul	$v0	$t0	$t1

	jr	$ra
###############################


###############################
# Division
###############################
division:
	lw	$t0	0($sp)
	lw	$t1	8($sp)

	beq	$t1	0	divisionByZero
	div	$v0	$t0	$t1

	jr	$ra
	
divisionByZero:
	li	$v0	0
	jr	$ra
###############################


###############################
# Factorial
###############################
factorial:
	# Load the value
	lw	$t0	0($sp)
	subi	$t1	$t0	1
	
	beq	$t1	1	endRecursion
	
	sub	$sp	$sp	12
	sw	$t1	0($sp)
	sw	$ra	4($sp)
	sw	$t0	8($sp)
	jal	factorial
endRecursion:

	lw	$v0	8($sp)
	lw	$ra	4($sp)
	lw	$v1	0($sp)
	mul	$v0	$v0	$v1
	
	addi	$sp	$sp	12
	sw	$v0	0($sp)

	jr	$ra
###############################
