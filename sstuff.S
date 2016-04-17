
	.global depDivs
depDivs:
	mov $1,%rax

        ret


	.global indepDivs
indepDivs:
	mov $1,%rax
        ret



	.global indepMuls
indepMuls:
	mov $1,%rax
	ret

	.global depMuls
depMuls:
	mov $1,%rax
	ret

	.global uncond
uncond:
	mov $1,%rax
	ret

	.global condTaken
condTaken:
	mov $1,%rax
	ret

	.global condNotTaken
condNotTaken:
	mov $1,%rax
	ret

	.global depLoads
depLoads:
	mov $1,%rax
	ret

	.global indepLoads
indepLoads:
	mov $1,%rax
	ret


	.globl indepAdds
indepAdds:
        push %rbx
	push %rcx
	push %rdx
	push %rsi
	push %rdi
	push %rbp

	.rept 1000
	add $1,%rax
	add $1,%rbx
	add $1,%rcx
	add $1,%rdx
	add $1,%rsi
	add $1,%rdi
	add $1,%rbp
	.endr

	pop %rbp
	pop %rdi
	pop %rsi
	pop %rdx
	pop %rcx
	pop %rbx

	mov $7000,%rax
	ret

	.globl depAdds
depAdds:
        mov $0,%rax

	.rept 10000
	add $1,%rax
	.endr

	ret

