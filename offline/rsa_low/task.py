#!/usr/bin/env python
# -*- coding: utf-8 -*-

from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives.asymmetric import rsa
from cryptography.hazmat.primitives.serialization import PublicFormat, Encoding

with open('flag.txt', 'rb') as f:
    flag = f.read()
    assert len(flag) == 18
    flag = int.from_bytes(flag, 'big')

key = rsa.generate_private_key(public_exponent=13, key_size=1848, backend=default_backend())

N = key.private_numbers().public_numbers.n
E = key.private_numbers().public_numbers.e
with open('key.pem', 'wb') as f:
    f.write(key.public_key().public_bytes(Encoding.PEM, PublicFormat.PKCS1))

assert flag < N
print((pow(flag,E) - pow(flag,E,N)) // N)
flag_enc = pow(flag, E, N)
flag_enc = int.to_bytes(flag_enc, 231, 'big')

with open('flag_enc.txt', 'wb') as f:
    f.write(flag_enc)
