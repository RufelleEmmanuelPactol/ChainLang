add
label:
mov, r, label
mov, ac, [50]
org, [130]
variable : db, 0x102123B
; to-do
; Implement the label checker reference and the register checker
; implement numeric converter, numeric checker, found in translator and memory_unit
; number_string in tokenizer -> convert to binary string in translator
; implement start and org
; fix decimal parsing of memory references
; add label-register convergences
; create decimal parser


; --> TO IMPLEMENT LIST before 1.0 release