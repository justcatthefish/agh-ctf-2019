#!/usr/bin/env python


from CryptoAttacks.PublicKey import rsa
from CryptoAttacks.Utils import i2b
from gmpy2 import iroot


with open('../flag_enc.txt', 'rb') as f:
    flag = f.read()
    flag = int.from_bytes(flag, 'big')

key = rsa.RSAKey.import_key('../key.pem')

f = flag
for i in range(0, 300):
    x = iroot(f, key.e)
    if x[1]:
        print(i, i2b(int(x[0])))
        break
    f += key.n
