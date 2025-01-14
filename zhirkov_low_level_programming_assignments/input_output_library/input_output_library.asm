section .data

character_buffer db 0; buffer to hold the character

decimal_format db '0123456789'

section .text



; ASCII symbols
%define SPACE_SYM   0x20
%define TAB_SYM     0x9
%define NEWLINE_SYM 0xA
%define NULL_SYM    0x0

; System calls
%define SYS_READ 0
%define SYS_WRITE 1
%define SYS_EXIT  60

; File descriptors
%define STDIN_FILE_DESCRIPTOR 0
%define STDOUT_FILE_DESCRIPTOR 1


global exit
global string_length
global print_null_terminated_string_to_stdout
global print_character_to_stdout
global print_newline_character_to_stdout
global print_uint_in_decimal_format

global print_signed_int_in_decimal_format_to_stdout
global read_character_from_stdin_and_return_it

global read_word_from_stdin_into_buffer

exit:
	mov rax, 60
	syscall

string_length:
	mov rax, -1
	xor rcx, rcx
	next_character:	
		inc rax
		mov cl, byte[ rdi + rax ]
		test rcx, rcx
		jne next_character
	ret

print_null_terminated_string_to_stdout:
	push rdi
	call string_length
	pop rdi
	mov rdx, rax; argument 3, how many bytes to write?
	mov rsi, rdi; argument 2, where does the string start? 
	mov rdi, 1; argument 1, file descriptor ( where to write )
	mov rax, 1; rax holding system call's number. rdi, rsi, rdx, r10, r8 and r9 are used to hold arguments
	syscall; system call in *nix systems, changes rcx and r11
	ret

print_character_to_stdout:
	mov byte[character_buffer], dil; dil is the lower 8 bits of the rdi register
	mov rax, 1
	mov rdi, 1
	mov rdx, 1
	mov rsi, character_buffer
	syscall; system call in *nix systems, changes rcx and r11
	ret

print_newline_character_to_stdout:
	mov rdi, 0xa
	call print_character_to_stdout
	ret

print_uint_in_decimal_format:
    mov rax, rdi
    mov rcx, rsp  
	sub rsp, 32	
	mov rbx, 10; divisor 
	dec rcx
    mov byte[ rcx ], 0 
    test rax, rax
    jnz .convert_uint_to_decimal_string
		dec rcx
		mov byte[ rcx ], '0'
		jmp .print

.convert_uint_to_decimal_string:
.convert_uint_to_decimal_string_loop:
		xor rdx, rdx; clear rdx (the remainder)
        div rbx; rax = rax / 10, rdx = rax % 10
		add dl, '0'
		dec rcx
		mov byte[rcx], dl
        test rax, rax
        jnz .convert_uint_to_decimal_string_loop
.print:
	mov rdi, rcx
	call print_null_terminated_string_to_stdout
	add rsp, 32
	ret
	
	

print_signed_int_in_decimal_format_to_stdout:
	cmp rdi, 0
	jge .positive_argument_case
	push rdi
	mov rdi, '-'
	call print_character_to_stdout
	pop rdi
	neg rdi
.positive_argument_case:
	call print_uint_in_decimal_format
	ret
	
	
read_character_from_stdin_and_return_it:
	mov rcx, rsp
	sub rsp, 16
	dec rcx
        ; file descriptor 0 (stdin)
    mov rsi, rcx     ; pointer to the buffer
    mov rdx, 1 

    mov rax, 0
    mov rdi, 0
	
	push rcx
	syscall

	pop rcx
	mov rax, 0
	mov al, byte[ rcx ]

	add rsp, 16
	ret
	
read_word_from_stdin_into_buffer:

	push r12
	push r13
	
	mov r12, rdi
	mov r13, rsi
	
	;rdi - buffer addr, rsi - size;

.skip_leading_spaces:
	call read_character_from_stdin_and_return_it
	; rax - char
	cmp al, 0x20; space character
	je .skip_leading_spaces
	cmp al, 0x9; tabulation character
	je .skip_leading_spaces
	cmp al, 0x10; line break character
	je .skip_leading_spaces

	mov rcx, -1
	jmp .skip_character_reading
.read_word:
	push rcx
	call read_character_from_stdin_and_return_it
	pop rcx
.skip_character_reading:

	cmp al, 0
	je .end_of_word
	cmp al, 0x20; space character
	je .end_of_word
	cmp al, 0x9; tabulation character
	je .end_of_word
	cmp al, 0x10; line break character
	je .end_of_word
	
	inc rcx
	inc rcx
	cmp rcx, r13
	je .word_is_too_big
	dec rcx
	
	mov byte[ r12 + rcx ], al
	
	jmp .read_word
	
	
.end_of_word:
	mov byte[ r12 + rcx ], 0
	mov rax, r12
	
	pop r13
	pop r12
	ret
	
.word_is_too_big:
	mov rax, 0
	pop r13
	pop r12
	ret