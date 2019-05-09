# [medium] exp2
### Exploit challenge

#### Task message
What does execstack mean?

#### Hints
1. You may find [shellcraft](http://docs.pwntools.com/en/stable/shellcraft/amd64.html) useful

#### Stats
Number of solves at the event: 0

#### Notes
If you hit infinite loop on read, modify the code:
```c
if(read(0, name, 7331) == 0)
  break;
```
