main:
mov, ac, [main]
local: db, 0d50
mov, r, local
inc, r
int16, [acx]
inc, r