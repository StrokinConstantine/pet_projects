section .data

message: db '1bcvbcbfdgs', 2

section .text

extern string_length
extern print_null_terminated_string_to_stdout
extern print_character_to_stdout
extern print_newline_character_to_stdout
extern print_uint_in_decimal_format
extern print_uint

extern exit

extern print_signed_int_in_decimal_format_to_stdout
extern read_character_from_stdin_and_return_it

global _start

_start:



	
	
	
	call read_character_from_stdin_and_return_it

	
	mov rdi, rax
	call print_signed_int_in_decimal_format_to_stdout
	
	
	
	xor rdi, rdi
	call exit