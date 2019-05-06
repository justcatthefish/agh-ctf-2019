# [easy] RSA_low
### Crypto challenge.

#### Task message
Sometimes a longer key does not mean a better key.

#### Hints
1. Just count bits:

a - 20 bits
b - 33 bits

a*b - bitlen(a)+bitlen(b) bits

a^b - bitlen(a) * b bits

And even if modulo cuts some bits, it may cut them only a little ;)

2. Also, you may find [iroot](https://gmpy2.readthedocs.io/en/latest/mpz.html?highlight=iroot) useful

#### Stats
Number of solves at the event: 0