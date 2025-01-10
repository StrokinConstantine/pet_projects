section .data

message: db '1bcvbcbfdgs', 2

section .text

extern string_length
extern print_null_terminated_string_to_stdout
extern print_character_to_stdout
extern print_newline_character_to_stdout
extern print_uint_in_decimal_format
extern print_uint

global _start

_start:


	mov rdi, 222222
	

	;and rsp, 0xFFFFFFFFFFFFFFF0 
	;sub rsp, 32
	call print_uint
	;add rsp, 32	
	mov rdi, 222222
	call print_uint_in_decimal_format

	call print_newline_character_to_stdout

	xor rdi, rdi
	
	mov rax, 60; exit syscall number
	SYSCALL; assembly language is case insensitive	
	
	
	

print_null_terminated_string_to_stdout_1:

	;call string_length
	mov rdx, 5; argument 3, how many bytes to write?
	mov rsi, rcx; argument 2, where does the string start? 
	mov rdi, 1; argument 1, file descriptor ( where to write )
	mov rax, 1; rax holding system call's number. rdi, rsi, rdx, r10, r8 and r9 are used to hold arguments
	syscall; system call in *nix systems, changes rcx and r11
	  
	ret







	
	;mov rsp, rbp           ; Restore stack pointer
  ;  pop rbp                ; Restore base pointer
	;ret 
	
	

	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
   sub rsp, 32                ; Allocate 32 bytes on the stack (enough for our string)

    ; Store the null-terminated string "Hello, World!" on the stack
    mov rax, 'Hello,'      ; Load first part of the string into rax
    mov [rsp], rax            ; Store it at the top of the stack
    mov rax, 'rld!'           ; Load the second part of the string into rax
    mov [rsp + 8], rax        ; Store it at the next position
    mov byte [rsp + 16], 0    ; Null terminator

    ; Load the address of the string into rdi
    lea rdi, [rsp]            ; rdi points to the start of the string

    ; Call the print function
    ;call print_null_terminated_string_to_stdout

    ; Clean up the stack
    add rsp, 32               ; Deallocate the allocated space
	
	
	
	
	mov rdi, message
	;call print_null_terminated_string_to_stdout
	lea rdi, [rsp-3]
	;call print_null_terminated_string_to_stdout
	inc rdi
	inc rdi
	;call print_null_terminated_string_to_stdout
	dec rdi
	dec rdi
	dec rdi
	dec rdi
	;call print_null_terminated_string_to_stdout
	
	
	;lea rdi, [rsp-4]
	;call print_null_terminated_string_to_stdout
	
	
	
	;call print_null_terminated_string_to_stdout
	
	
	
	


	xor rdi, rdi
	mov rax, 60; exit syscall number
	SYSCALL; assembly language is case insensitive
	

	