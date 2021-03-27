# Carter Hawks CS3340.502 CKH170000
# Homework 6, due March 31 2019
.data
inputfile: 	.asciiz "input.txt"		# Input file name
unsortedtext: 	.asciiz "Unsorted array: "	# message for unsorted array
sortedtext:	.asciiz "Sorted array: "	# message for sorted array
meantext:	.asciiz "The mean is: "		# very mean bullying message
mediantext:	.asciiz "The median is: "	# median text
sdtext:		.asciiz "The standard deviation is: "	# you know what it is
buffer:  	.space 80			# Input buffer for file loading
size:	 	.word 20			# element length of array, hardcoded
fileerror: 	.asciiz "Error loading file."   # Error message for file loading
array: 		.space 20			# Extracted unsorted array
p: 		.space 20 			# Pointer for sorted array

.text
main:
	la $a0, inputfile
	la $a1, buffer
	jal func1
	bltz $v0, error
	j posterror
	
error:
	# print out error message
	li $v0, 4
	la $a0, fileerror
	syscall
posterror:

	la $a0, array	# Address of array
	li $a1, 20	# Predetermined length of array
	la $a2, buffer 	# Address of buffer start
	jal func2
	
	move $s0, $a0
	
	# Print new line character
	li $v0, 11
	li $a0, 10
	syscall
	
	# Print unsorted array text
	li $v0, 4
	la $a0, unsortedtext
	syscall
	
	move $a0, $s0
	la $a0, array
	jal func3
	
	# call selection sort function here
	jal func4
	
	# Print sorted array text
	li $v0, 4
	la $a0, sortedtext
	syscall
	
	la $a0, array
	jal func3
	
	# Call func5 calculate mean function
	la $a0, array
	lw $a1, size
	jal func5
	
	mov.s $f16, $f0
	move $a0, $s0
	
	# Print mean text
	li $v0, 4
	la $a0, meantext
	syscall
	
	# print float 
	li $v0, 2
	mov.s $f12, $f0
	syscall
	
	# Print new line character
	li $v0, 11
	li $a0, 10
	syscall
	
	
	# Call func6 to calculate median function
	la $a0, array
	lw $a1, size
	jal func6
	
	# protect v0
	move $s2, $v0
	
	# Print median text
	li $v0, 4
	la $a0, mediantext
	syscall
	
	beqz $v1, printfloat
	# v1 = 1, integer
	
	# print the integer
	li $v0, 1
	move $a0, $s2
	syscall
	j afterprintfloat
printfloat: 
	# v1 = 0, float
	# print float 
	li $v0, 2
	mov.s $f12, $f0
	syscall
	
afterprintfloat:
	
	# Print new line character
	li $v0, 11
	li $a0, 10
	syscall
	
	# Call func7 to calculate standard deviation function
	la $a0, array
	lw $a1, size
	#move $f16, $f16 
	jal func7
	
	
	# Print standard deviation text
	li $v0, 4
	la $a0, sdtext
	syscall
	
	# print float 
	li $v0, 2
	mov.s $f12, $f0
	syscall
	
	j exitfull

##########################################################################################
# Load file function
# Returns number of bytes read in $v0
# $a0 = address of input file 
# $a1 = address of buffer
func1: 
	# $s1 is going to hold address of buffer
	move $s1, $a1
	
	# Open File
	li	$v0, 13
	la	$a0, inputfile  # input file
	li	$a1, 0	   # open for read
	li	$a2, 0	   
	syscall
	
	# $s0 is going to hold file descriptor
	move $s0, $v0
	
	# Read file contents
	# Read from file
	move $a0, $s0   # file descriptor (?)
	li $v0, 14 	# 14 = read file
	move $a1, $s1 	# String buffer
	li $a2, 80 	# Max chararacters
	syscall
	
	# Close file
	li $v0, 16	# 16 = close file
	move $a0, $s0 	# File descriptor
	syscall 	

	# Return
	move $v0, $s0
	jr $ra

##########################################################################################
# Make the data not trash function
# Extract integers from input buffer and store into array
# $a0 = output array
# $a1 = array length (20)
# $a2 = buffer start
func2:
	move $s0, $a0

	# loop through buffer byte by byte
	# must be on or within 48-57 otherwise skip
	add $t1, $zero, $zero # t1 will act as our i = 0 incremental vALUE for counting the current byte we are on
	add $t3, $zero, $zero
loop2:	
	add $t2, $a2, $t1
	lb $t0, 0($t2)
	
	# print out byte for testing
	#li $v0, 1
	#move $a0, $t0
	#syscall
	
	# print out a space to accompany that shztuff
	#li $v0, 11
	#li $a0, 32
	#syscall
	
	# check if it is 0
	beq $t0, 0, exloop2
	
	# check if it is 10 
	bne $t0, 10, after10
	# t0 (current digit) is equal to ascii 10
	# save the integer we were working with as the next array element
	add $t8, $t3, $s0
	sb $t9, ($t8)
	
	addi $t3, $t3, 4 # t3 will act as our array index counter
	add $t9, $zero, $zero # reset value counter
	j nextbyte
after10:
	
	# check if it is within 48-57
	# ignore it
	blt $t0, 48, nextbyte
	bgt $t0, 57, nextbyte
	
	# WE GOT A DIGIT BOYS WOO
		
	# it has been determined that this is a usable number.
	subi $t0, $t0, 48 # convert ascii to decimal
	
	# if 
	bne $t0, 0, heck
	# if it IS equal to 0
	# this is the first digit or only digit, place value in t9
	add $t9, $t0, $zero # place decimal value in t9
	j nextbyte
heck:	
	# if it IS NOT equal to 0
	# this is the second digit, there is data before this , that means the data before this should be multiplied by 10 and then should add this digit to it
	addi $t8, $zero, 10
	mult $t9, $t8 # multiply t9 by 10 (t8)
	mfhi $t4 # this should be unused
	mflo $t5
	move $t9, $t5
	# add current digit to t9
	add $t9, $t9, $t0
	
nextbyte:
	addi $t1, $t1, 1 # go to the next byte by incrementing offset i
	#bgt $t1, $a1, exloop2
	j loop2
	
exloop2:
	jr $ra
	
##########################################################################################
# function to print array of ints
func3:
	move $s0, $a0 # $s0 is now the base address of the array
	add $t0, $zero, $zero
loop3:	bgt $t0, 76, end3 # if we have printed more than 20 INTS (76 = 4 * 20 - 4)
	
	# get the integer
	add $t2, $s0, $t0
	
	# print the integer
	li $v0, 1
	lb  $a0, ($t2)
	syscall
	
	# print a space
	li $v0, 11
	li $a0, 32
	syscall
	
	# increment to next element index
	addi $t0, $t0, 4
	j loop3
	
end3:
	# Print new line character
	li $v0, 11
	li $a0, 10
	syscall

	jr $ra

##########################################################################################

# selection sort
# swap current (starting, first) element with minimum remaining element in list
func4: 
li      $t5, 0		# t5 is k = 0

	la      $t7, size     
        lw      $t7, 0($t7)     # t7 = size
	
	addi    $t8, $t7, -1    # t8 = size - 1
	la	$t6, array	# t6 = array address

	# outerloop
outerloop: slt	$t0, $t5, $t8   # if k < size - 1  t0 = 1
	beq	$t0, $zero, breakouterloop # k >= (siz - 1)
	add	$t9, $zero, $t5 # t9 is min = k

	addi    $t1, $t5, 1     # t1 is j = k + 1
  
  	# inner loop 
  	# kinda like the elon musk hyperloop but not really that doesnt sort things
innerloop: slt  $t0, $t1, $t7   # if (j < size ) then t0 = 1
	beq	$t0, $zero, breakinnerloop

	add	$s3, $t9, $t9   # s3 = 2 * min
	add	$s3, $s3, $s3   # s3 = 4 * min
	add	$s3, $t6, $s3   # s3 is address of list[min]
	lw	$t2, 0($s3)     # t2 is list[min]

	add	$s0, $t1, $t1   # s0 = 2 * j
	add	$s0, $s0, $s0   # s0 = 4 * j
	add	$s0, $t6, $s0	# s0 is address of list[j]
	lw	$t3, 0($s0)     # t3 is list[j]

	slt	$t0, $t3, $t2   # if list[j] < list[min] t0 = 1
	beq	$t0, $zero, secondif # skip min = j & ++j and jump to secondIF
	add 	$t9, $zero, $t1 # min = j
	j secondif
	
	# second sorty boy
secondif: beq	$t9, $t5, incrementj # if min != k swap, else goto incrementJ

	# swap THOSE VALUES
	add	$s0, $t9, $t9   # s0 = 2 * min
	add	$s0, $s0, $s0   # s0 = 4 * min
	add	$s0, $s0, $t6   # s0 = address of list[min]
	lw	$t4, 0($s0)     # t4 is temp = list[min]


	add	$s1, $t5, $t5   # s1 = 2 * k
	add	$s1, $s1, $s1   # s1 = 4 * k
	add	$s1, $t6, $s1   # s1 = address of list[k]
	lw	$s3, 0($s1)     # s3 = list[k]


	sw	$s3, 0($s0)     # list[min] = list[k]

	sw	$t4, 0($s1)     # list[k] = temp 
	addi	$t1, $t1, 1	# ++j
	add	$t9, $zero, $t5 # t9 is min = k	 
	# end swap THOSE VALUES

	j innerloop	

incrementj: addi $t1, $t1, 1    # ++j
	j innerloop

breakinnerloop: 
	addi $t5, $t5, 1 # ++k
	j outerloop
	

breakouterloop: 
	jr $ra
	
##########################################################################################

# calculate mean
# a0 = array to mean
# a1 = array size
# returns: f register sp float value
func5: 
	add $t0, $zero, $zero # $t0 = the sum register
	add $t1, $zero, $zero # $t1 = the index counter register
loop5:	bge $t1, $a1, end5

	sll $t4, $t1, 2 	# fixed index counter offset = index counter * 4
	add $t3, $a0, $t4 	# index address = array start + fixed index counter offset
	lw $t2, ($t3)		# t2 (value) = word at index address
	add $t0, $t0, $t2 	# total sum = total sum + t2 (value)
	addi $t1, $t1, 1
	# add up all of the numbers
	# divide by 20 (single precision)
	j loop5
end5:	
	# do division
	# mean (sp fp) = total sum (t0) / array size (a1)
	mtc1 $t0, $f2
	mtc1 $a1, $f4
	div.s $f0, $f2, $f4
	mov.s $f0, $f0
	# return f register
	jr $ra

##########################################################################################

# calculate median
# a0 = array to median
# a1 = array size
# RETURNS
# v0 = if the length is odd, return middle value as v0
# f0 = if the length is even, return middle two values averaged as f0
# v1 = a flag determining whether a float or integer was returned 
func6: 
	addi $t0, $zero, 2
	rem $t9, $a1, $t0 
	beqz $t9, even
	# odd
	# return the middle number
	# determine the middle index
	div $t0, $a1, $t0
	
	sll $t0, $t0, 2
	add $t3, $a0, $t0
	lw $v0, ($t3)
	addi $v1, $zero, 1 # return v1 as 1 because it is odd returning v0
	jr $ra
even:
	div $t0, $a1, $t0 # $t0 = 10
	
	# index 10
	sll $t1, $t0, 2
	add $t2, $a0, $t1
	lw $t3, ($t2)
	add $t4, $zero, $t3
	
	subi $t0, $t0, 1
	# index 9
	sll $t1, $t0, 2
	add $t2, $a0, $t1
	lw $t3, ($t2)
	add $t4, $t4, $t3
	
	addi $t5, $zero, 2
	mtc1 $t4, $f1
	mtc1 $t5, $f3
	
	div.s $f0, $f1, $f3
	add $v1, $zero, $zero
	jr $ra	

##########################################################################################

# calculate standard deviation
# a0 = sorted array
# a1 = array length
# f16 = calculated mean
func7: 
	add.s $f12, $f31, $f31 # make sure that f12 = zero

	# top of fraction
	move $t1, $a0	# t1 = address of sorted array
	li $t8, 0	# lcv t8 is 0
loop7:	bge $t8, $a1, postsum	# if lcv (t8) is greater than or equal to array length, break to postsum
	lw $t0, ($t1)		# t0 = word at address t1
	mtc1 $t0, $f9		# convert int t0 to spfp f9
	cvt.s.w $f9, $f9
	sub.s $f10, $f9, $f16  #(ri - ravg)	#f10 = $f9 - $f16
	mul.s $f10, $f10, $f10 # square it	# f10 = $f10 * $f10
	add.s $f12, $f10, $f12 # $f12 = $f12 + $f10
	addi $t1, $t1, 4	# increment t1 address by 4 to next word
	addi $t8, $t8, 1	# increment lcv by 1
	j loop7
postsum:
	#bottom
	subi $t9, $a1, 1	# t9 =  array length - 1
	mtc1 $t9, $f6		# convert t9 to spfp
	cvt.s.w $f6, $f6
	
	div.s $f2, $f12, $f6 	# divide top by bottom
	sqrt.s $f0, $f2 	# sqrt of whole thing
	jr $ra
	
##########################################################################################

exitfull:
	# exit program safely
	li $v0, 10
	syscall
