# push_swap
<br/>
<br/>
<p align="center">
<i>As a young boy, I dreamed of being a baseball. <br/>
    But tonight I say, we must move forward, not backward; <br/>
    upward, not forward; <br/>
    and always twirling, twirling, twirling towards freedom! <br/>
</i>
</p>
<p align="left">
<i>         ~ William Jefferson Clinton </i>
</p>
<br/>
<br/>
Part of 42 common core cursus; algorithm design && implementation.  
  
The program must receive a non-zero amount of numbers that will be treated as a stack,
and then it will print through standard output the series of instructions used to order the stack.  

This program follows a list of rules:  
* It has available two stacks, a & b  
* At the end of the algo execution, stack a must be filled with the ordered set of input integers, and b  
  must be empty.  
* It will use a limited list of instructions:  
  
  
  * sa: swap the two first elements of a
  * sb: swap in b
  * ss: sa & sb
  * pa: push from b to a
  * pb: push from a to b
  * ra: rotate upwards a
  * rb: rotate upwards b
  * rr: ra & rb
  * rra: reverse rotate a
  * rrb: reverse rotate b
  * rrr: rra & rrb

## Usage
### Push swap
To compile and execute the program.  
```
make && ./push_swap [ n ...]
```

### Checker
Checker binary receives from standard input a list of arguments and a stack of numbers as parameters,
then check if the argument list is capable of ordering the stack.  
```
make checker && ./checker [n ...]
```

### Tester
Batch of tests with different size of inputs.  
```
./test.sh
```

_> Project passed with [125/100] mark ✅😎 <_
