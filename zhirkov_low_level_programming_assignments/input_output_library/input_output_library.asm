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
%define SYS_READ  0
%define SYS_WRITE 1
%define SYS_EXIT  60

; File descriptors
%define STDIN     0
%define STDOUT    1








global exit
global string_length
global print_null_terminated_string_to_stdout
global print_character_to_stdout
global print_newline_character_to_stdout
global print_uint_in_decimal_format

global print_uint


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
	
	 mov rbx, 10 
	dec rcx
    mov byte[ rcx ], 0  
	


    ; Check for zero
    test rax, rax
    jnz .convert_uint_to_decimal_string            ; If rax is not zero, start converting
	
	dec rcx
    ; handle the case where the input number is 0
    mov byte[ rcx ], '0'     ; If the number is zero, store '0'
    jmp .print              ; Jump to print
	
.convert_uint_to_decimal_string:
    ; Convert number to string in reverse order
    .loop:
        xor rdx, rdx        ; clear rdx (the remainder)
               ; divisor
        div rbx             ; rax = rax / 10, rdx = rax % 10
      
		add dl, '0'         ; convert digit to ASCII
		dec rcx
                  ; move buffer pointer back
		mov byte[rcx], dl       ; store ASCII character in buffer
        test rax, rax       ; check if rax is zero
        jnz .loop           ; repeat if not zero
.print:
	mov rdi, rcx
	call print_null_terminated_string_to_stdout
	add rsp, 32
	ret 





print_uint:
  mov rax, rdi    ; rax <- uint to print
  mov rcx, 10     ; rcx: divider
  mov r11, rsp    ; Save rsp to r11
  ; uint from rdi can be maximum 20 chars
  sub rsp, 32     ; Stack should be 16 bytes aligned for x64 ABI, so we need to allocate 32 bytes
  dec r11
  mov byte [r11], NULL_SYM  ; Null-terminator
  .loop:
    xor rdx, rdx  ; Clear division remainder for iter
    div rcx       ; rax /= 10; rdx = rax % 10
    add dl, '0'   ; rax % 10 to ASCII
    dec r11
    mov byte [r11], dl
    cmp rax, 0
    jnz .loop     ; if rax / 10 != 0
  mov rdi, r11    ; rdi <- uint string starts address
  call print_null_terminated_string_to_stdout
  add rsp, 32     ; Free used stack data
  ret
  
  
  
  
  
  
  
  
  
  
  
  ;; Принимает указатель на нуль-терминированную строку, возвращает её длину
string_length_1:
  xor rax, rax  ; Clear the length counter

  .counter:
    ; Checking the current byte is 0
    cmp byte [rdi + rax], NULL_SYM
    je .return

    inc rax     ; Go to next byte
    jmp .counter
  .return:
    ret

;; Принимает указатель на нуль-терминированную строку, выводит её в stdout
print_string:
  push rdi      ; Save rdi
  call string_length_1
  pop rdi       ; Restore rdi

  mov rdx, rax  ; rdx <- string length
  mov rsi, rdi  ; rsi <- string start address

  mov rax, SYS_WRITE
  mov rdi, STDOUT
  syscall

  ret