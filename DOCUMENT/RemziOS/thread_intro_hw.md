```
.main
mov 2000, %ax   # get the value at the address
add $1, %ax     # increment it
mov %ax, 2000   # store it back
halt
```

2000 : the number (2000) is the address  
(%cx) : contents of register (in parentheses) forms the address  
1000(%dx) : the number + contents of the register form the address  
10(%ax,%bx) : the number + reg1 + reg2 forms the address  
