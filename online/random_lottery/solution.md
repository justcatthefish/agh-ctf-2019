### random lottery

Simple challenge with integer overflow / negative integers / `abs()` "bug".

You can bet money in lottery. If you are lucky, you win same amount of money you have invested. 

The bug is here:
```c
int64_t toBet;
if(toBet < 0)
    toBet = abs(toBet);
```

`abs` function called with INT\_MIN (`-2**63`) returns INT\_MIN (because of how integers are represented in memory).

So betting `-2**63` will give you `-2**63` dollars (independently of lottery result). Then you can buy flag, because the price is of unsigned type (`size_t):
```c
int64_t this->money;
size_t price;

if(price <= this->money) {
    this->money -= price;
    return true;
}
```

Unfortunately there was a bug during the CTF. `price` was of type `int64_t` and the challenge was (probably) unsolvable ;/

