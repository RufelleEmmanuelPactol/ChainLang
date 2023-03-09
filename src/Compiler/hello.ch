; data
i : db, 0d10
str: db, "Hello, World"


@trace


mov, rx, [i]
loop:
char, rx
inc, r
inc, ac
cmp, ac, i
jpf, loop
add

; fix inc memreg




; invalidate mov [] to acx
end