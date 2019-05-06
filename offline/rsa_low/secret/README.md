# rsa low

Simple RSA challenge

## Writeup

Parameters are chosen in such a way that we can **almost** compute root of the encrypted flag to get the flag. Plaintext flag (`18` bytes) raised to power of e (`13`) modulo n (`1848` bits) should be of length `(18 * 8) * 13 = 1872` bits.

So:

`flag ^ e % n == flag_enc`

`flag ^ e == flag_enc + k*n`

`k should be small` -> `root(flag_enc + k*n, e) == flag`.

K is small (about 250 in value) and is bruteforcable ;)
