
	.global indepDivs
indepDivs:
        mov $1,%rax

        push %rbx
	push %rcx
	push %rdx
	push %rsi
	push %rdi
	push %rbp

        mov $1,%rbx
        mov $1,%rcx
        mov $1,%rsi
        mov $1,%rdi
        mov $1,%rbp
        mov $0,%rdx

	.rept 1000
	div %rax
	div %rbx
	div %rcx
	div %rsi
	div %rdi
	div %rbp
        mov $1,%rax
        mov $0,%rdx
	.endr

	pop %rbp
	pop %rdi
	pop %rsi
	pop %rdx
	pop %rcx
	pop %rbx

	mov $6000,%rax
	ret


	.global depDivs
depDivs:
	mov $1,%rax
        
        .rept 10000
	div %rax
	.endr

        mov $10000,%rax
        ret



	.global indepMuls
indepMuls:
        mov $1,%rax

        push %rbx
	push %rcx
	push %rdx
	push %rsi
	push %rdi
	push %rbp

	.rept 1000
	imul $1,%rax
	imul $1,%rbx
	imul $1,%rcx
	imul $1,%rdx
	imul $1,%rsi
	imul $1,%rdi
	imul $1,%rbp
	.endr

	pop %rbp
	pop %rdi
	pop %rsi
	pop %rdx
	pop %rcx
	pop %rbx

	mov $7000,%rax
	ret

	.global depMuls
depMuls:
	mov $1,%rax
	
        .rept 10000
	imul $1,%rax
	.endr

        mov $10000,%rax
	ret

	.global uncond
uncond:
	mov $1,%rax

        .rept 10000
        jmp 1f
1:
        .endr

        mov $10000,%rax
	ret

	.global condTaken
condTaken:
	mov $0,%rax
        cmp $0,%rax

        .rept 10000
        je 2f
2:
        .endr

        mov $10000,%rax
	ret

	.global condNotTaken
condNotTaken:
	mov $1,%rax
        cmp $0,%rax

        .rept 10000
        je 3f
3:
        .endr

        mov $10000,%rax
	ret

	.global indepLoads
indepLoads:
        push %rbx
	push %rcx
	push %rdx
	push %rsi
	push %rdi
	push %rbp

	.rept 1000
	mov x,%rax
	mov x,%rbx
	mov x,%rcx
        mov x,%rdx
        mov x,%rsi
	mov x,%rdi
	mov x,%rbp
	.endr

	pop %rbp
	pop %rdi
	pop %rsi
	pop %rdx
	pop %rcx
	pop %rbx

	mov $7000,%rax
	ret

	.global depLoads
depLoads:
        mov $x,%rax

	.rept 10000
	mov x(%rax),%rax
	.endr

        mov $10000,%rax
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

.data
        x: .quad 0
