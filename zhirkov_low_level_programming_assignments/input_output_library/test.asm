section .data

message1: db '-abcde',0
message2: db '-12345',0
message3: dw '-1','2'

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

extern read_word_from_stdin_into_buffer

extern parse_null_terminated_string_to_unsigned_integer
extern parse_null_terminated_string_to_signed_integer
extern parse_int
extern string_equals
extern string_copy


global _start

_start:
	mov r15, rsp
	sub rsp, 128
	
	mov byte[ r15 - 4 ], 0
	mov byte[ r15 - 5 ], 'a'
	mov byte[ r15 - 6 ], 'b'
	mov byte[ r15 - 7 ], 'c'
	mov byte[ r15 - 8 ], 'd'
	mov byte[ r15 - 9 ], 'e'
	mov byte[ r15 - 10 ], 'f'
	
	
	mov byte[ r15 - 17 ], 0
	mov byte[ r15 - 18 ], '1'
	mov byte[ r15 - 19 ], '2'
	mov byte[ r15 - 20 ], '3'
	mov byte[ r15 - 21 ], '4'
	mov byte[ r15 - 22 ], '5'
	mov byte[ r15 - 23 ], '6'
	
	
	
	lea rdi, [r15 - 23]
	call print_null_terminated_string_to_stdout
	
	
	lea rdi, [ r15 - 10 ]
	lea rsi, [ r15 - 23 ]
	mov rdx, 10
	
	
	call string_copy
	call print_newline_character_to_stdout
	;mov rdi, rax
	;call print_uint_in_decimal_format

	;call print_newline_character_to_stdout
	
	
	lea rdi, [r15 - 23]
	call print_null_terminated_string_to_stdout
	
	
	add rsp, 128
	xor rdi, rdi
	call exit