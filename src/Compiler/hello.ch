main:
start, main
org, [100]
word: db, "Hello, World!"
ctr: db, 0d13
org, main
mov, rx, ctr
mov, ac, [main]
loop:
; char, [ac]
inc, ac
equ, rx, ry
jpt, loop
end


