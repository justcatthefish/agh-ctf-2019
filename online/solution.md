### aes oh aes

The task was supposed to be simple - standard CPA against AES in ECB mode with flag as constant suffix and no prefix (see for example https://cryptopals.com/sets/2/challenges/12).

Turns out there is a bug: base64 decoding in java "breaks" input. Sending for example `800f0f0f0f0f0f0f0f0f0f0f0f0f0f0f` (in hex) results in `efbfbd0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f` (because of utf8 decoding). Now, it still should be exploitable. But certainly it is not an "easy" challenge ;)

