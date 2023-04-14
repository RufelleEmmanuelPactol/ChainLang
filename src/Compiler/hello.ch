; .bss
@auto
m:

name: db, "Hello, Kyla"
mxb: dw, 0xFFFF
main:
start, m
add, ac, r
add, r, ac
end
mov, ac, [50]
