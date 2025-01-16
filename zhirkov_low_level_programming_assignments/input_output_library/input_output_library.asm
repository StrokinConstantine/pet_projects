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

global parse_null_terminated_string_to_unsigned_integer
global parse_null_terminated_string_to_signed_integer
global parse_int

global string_equals
global string_copy


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
	mov byte[ r12 + rcx + 1 ], 0
	mov rax, r12
	mov rbx, rcx
	pop r13
	pop r12
	ret
	
.word_is_too_big:
	mov rax, 0
	pop r13
	pop r12
	ret


parse_null_terminated_string_to_unsigned_integer:
	xor rax, rax
	xor rcx, rcx
	xor rdx, rdx
	mov r11, 10
	.parse_loop:
		mov cl, byte[ rdi + rcx ]
		sub cl, '0'; conversion from ASCII code to integer
		jl .return_because_character_is_not_a_digit
		cmp cl, 9
		jg .return_because_character_is_not_a_digit
		push rdx; mul affects rdx
		mul r11; rax *= 10
		pop rdx
		add rax, rcx
		inc rdx
		jmp .parse_loop
.return_because_character_is_not_a_digit:
	ret

	
parse_null_terminated_string_to_signed_integer:
	cmp byte[ rdi ], '-'
	je .parse_int
	jne .parse_uint

.parse_int:
	inc rdi
	;push rdi
	call parse_null_terminated_string_to_unsigned_integer
	;pop rdi
	inc rdx
	neg rax
	ret

.parse_uint:
	call parse_null_terminated_string_to_unsigned_integer
	ret


string_equals:
	mov rcx, -1
	.loop:
		inc rcx
		mov al, byte[ rdi + rcx ]
		cmp byte[ rsi + rcx ], al
		je .equal
		jmp .return_inequality
	
.equal:
	cmp al, 0
	je .return_equality
	jmp .loop

.return_inequality:
	mov rax, 0
	ret

.return_equality:
	mov rax, 1
	ret


string_copy:
	;rdi, rsi, rdx
	
	push rdi
	push rsi
	push rdx
	
	call string_length
	
	pop rdx
	pop rsi
	pop rdi
	
	inc rax




	cmp rax, rdx
	jge .return_failure
	;dec rax


	.loop:
		dec rax
		mov cl, byte[ rdi + rax ]
		mov byte[ rsi + rax ], cl

		

		

		cmp rax, 0
		je .return_success
		jmp .loop
.return_failure:
	mov rax, 0
	ret
	
.return_success:
	mov rax, 1
	ret
	
; calee-saved: rbx, rbp, rsp, r12-r15
; caller-saved all outher