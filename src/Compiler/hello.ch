main:
start, main
mov, ac, [main]
local: db, 0d50
mov, r, local
inc, r
int16, [ac]
inc, r
mov, ac, [local]




; to-do
; Implement the label checker reference and the register checker

; implement numeric converter, numeric checker, found in translator and memory_unit
; number_string in tokenizer -> convert to binary string in translator
; implement start and org

marang:
marang: