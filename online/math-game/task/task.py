#

#
# UCZESTNICY NIE MAJA DOSTEPU DO TEGO PLIKU
# MUSZA BLACKBOXOWAC CO TU SIE DZIEJE
#

from random import randint
from os import system
import string

print("It's simple game!")
print("I will give you simple calculs using *, -, + operations and...")
print("you will find equivalent with different operator.")
print("""
As an example, if I provide you this string:
1 + 2
You need to provide me another one that consits of * or - operator that returns the same result, e.g.:
4 - 1
""")

operators = ['*', '+', '-']

for _ in range(10):
    operator = operators[randint(0, len(operators)-1)]
    a = randint(1, 10**8)
    b = randint(1, 10**8)
    print(a, operator, b)
    result = str(eval(str(a) + operator + str(b)))

    line = input()

    if (operator in line) or ('print' in line):
        print("You don't understand the rules!")
        exit(1)
    if ('*' not in line) and ('+' not in line) and ('-' not in line):
        print("Not result!")
        exit(1)
    if "system" in line:
        print("I catched you!")

    user_result = str(eval(line))
    if user_result == result:
        print("Nice one! Only... few left.")
    else:
        print("No,",  user_result," is not good answer. :(")
        exit(0)

print("Yes, yes, yes!")
print("This is my file with data you are not looking for.")
print(system('cat /task/irrevalent.data'))
print("")
print("")
