# Carter Hawks CS3340.502 CKH170000
# Homework 5, due March 8 2019

.data
# int height = 0
height: 	.word 0
# int weight = 0
weight: 	.word 0
# double bmi = 0
bmi:		.double 0.0
# string name
name: 		.asciiz ""

nameprompt: 	.asciiz "What is your name? "
heightprompt: 	.asciiz "Please enter your height in inches: "
weightprompt: 	.asciiz "Now enter your weight in pounds (round to the nearest whole number): "
yourbmiprompt: 	.asciiz ", your bmi is: "

underweight: 	.asciiz "This is considered underweight. \n"
under: 		.double 18.5
normalweight:	.asciiz "This is a normal weight. \n"
normal:		.double 25.0
overweight: 	.asciiz "This is considered overweight. \n"
over: 		.double 30.0
obeseweight: 	.asciiz "This is considered obese. \n"

newline:	.asciiz "\n"


.text

	# prompt user for their data
	
	# var: nameprompt, input into name
	li $v0, 4
	la $a0, nameprompt
	syscall
	
	# get user input and write into name variable
	li $v0, 8
	la $a0, name
	li $a1, 20
	syscall

	# var: heightprompt, input into height
	li $v0, 4
	la $a0, heightprompt
	syscall
	
	# user types in INPUT VALUE height
	li $v0, 5
	syscall
	sw $v0, height

	# var: weightprompt, input into weight
	li $v0, 4
	la $a0, weightprompt
	syscall
	
	# user types in INPUT VALUE height
	li $v0, 5
	syscall
	sw $v0, weight

	# Calculate the BMI
	lw $t0, weight
	lw $t2, height
	l.s $f12, bmi
	
	li $t4, 703
	mult $t0, $t4
	mflo $t0
	
	mult $t2, $t2
	mflo $t2
	
	mtc1 $t0, $f0
	mtc1 $t2, $f2
	
	div.d $f12, $f0, $f2
	# weight = weight * 703
	# height = height * height
	# bmi = (double) weight / height


	# i cannot get this stupid name to print on the same line as the rest of this sentence. i have been trying for a while :(
	# print out name
	li $v0, 4
	la $a0, name
	syscall
	
	# print result 
	li $v0, 4
	la $a0, yourbmiprompt
	syscall
	
	# print out BMI
	li $v0, 3
	syscall
	
	# print newline
	li $v0, 4
	la $a0, newline
	syscall

	# Output the Results	
# bmi < 18.5 	underweight
	l.d $f6, under
	c.le.d $f12, $f6
	bc1f Normal
	
	# print text
	li $v0, 4
	la $a0, underweight
	syscall
	
	j end
Normal:
	# bmi < 25 	normalweight
	l.d $f6, normal
	c.le.d $f12, $f6
	bc1f Over
	
	# print text
	li $v0, 4
	la $a0, normalweight
	syscall
	
	j end
Over:  
# bmi < 30	overweight
	l.d $f6, over
	c.le.d $f12, $f6
	bc1f Obese

	# print text
	li $v0, 4
	la $a0, overweight
	syscall
	
	j end
Obese:
# else		obeseweight
	# print text
	li $v0, 4
	la $a0, obeseweight
	syscall
	
	j end
end:
	# exit program safely
	li $v0, 10
	syscall