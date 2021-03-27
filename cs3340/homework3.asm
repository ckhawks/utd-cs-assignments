# Carter Hawks CS3340.502 CKH170000

.data
inputtext: .asciiz "Enter some text:"
in:	.space 80 # the buffer
exitstring: .asciiz "Goodbye :)"
out1:	.asciiz " words "
out2: 	.asciiz " characters\n"
goodbye: .asciiz " goodbye " # if I remove this line it stops working and I don't have time to figure out why
emptystring: .asciiz ""
words: .space 80
chars: .space 80

.text
main:
	j start
	
## Start Function Declaration	
	
count:	# i don't understand the usage of this
	sub $sp, $sp, 4
	sw $s1, ($sp)

	# load stuff for count function
	# $a0 - the string
	li $t1, 0 	# the register for length of the string (characters)
	li $t2, 0 	# the register for number of spaces in the string
	
loop:  	lb $t3, 0($a0)
	beqz $t3, done		# check if we hit the last character
	addi $a0, $a0, 1	# increment byte counter
	addi $t1, $t1, 1	# increment length of string counter
	bne $t3, ' ', loop 	# check if current is equal to a space
	addi $t2, $t2, 1	# increment space counter
	j loop
done:	
	add $v1, $zero $t1	# number of characters v1
	add $v0, $zero, $t2  	# load number of spaces into $v0
	addi $v0, $v0, 1	# add 1 to number of spaces to make it number of words
	
	# i still don't understand the usage of this
	lw $s1, ($sp)
	addiu $sp, $sp, 4
	
	# return back to the jal
	jr $ra
	
## End function declaration
	
start:

input:	# open input dialog 
	li  $v0, 54	# the syscall for the input dialog box
	la  $a0, inputtext	# the text to put there
	la  $a1, in 	# the output buffer
	li  $a2, 80	# the maximum number of characters 
	syscall
	
	# check the status codes of the input dialog
	beq $a1, -3, exit
	beq $a1, -2, exit
	
print:	# print out "in"
	li $v0, 4	# syscall for print asciiz
	la $a0, in	# print the string
	syscall
	
	# call the count function
	la $a0, in	# set the input string buffer
	jal count
	
	sw $v0, words
	sw $v1, chars
	
	# print out number of spaces
	li $v0, 1 		# syscall #1 - print integer
	lw $t0, words
	add $a0, $0, $t0	# load $t1 (characters number) into $a0
	syscall
	
	# print out " words "
	li $v0, 4
	la $a0, out1
	syscall
	
	# print out number of characters
	li $v0, 1 		# syscall #1 - print integer
	lw $t0, chars
	add $a0, $0, $t0	# load $t1 (characters number) into $a0
	syscall
	
	# print out " characters\n"
	li $v0, 4
	la $a0, out2
	syscall
	
	j start # jump back to the start
	
## EXIT ##	
	
exit:	# exit program dialog
	li $v0, 59
	la $a0, emptystring
	la $a1, exitstring
	syscall

	# print out goodbye
	#li $v0, 4
	#la $a0, goodbye
	#syscall

	# exit program
	li $v0, 10
	syscall
	
## SAMPLE OUTPUT ##
#### Sample run: 
## Sample input: What is up my dudes
## Sample output:
# 
# What is up my dudes
# 5 words 20 characters
# -- program is finished running --
#
