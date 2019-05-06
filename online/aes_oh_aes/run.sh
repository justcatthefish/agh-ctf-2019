#!/bin/bash

docker rm -f aes-oh-aes
docker build -t aes-oh-aes .

docker run --restart=always -d \
	-p 1341:8000 \
	--name aes-oh-aes \
	-v `pwd`/flag.txt:/flag.txt:ro \
	-v `pwd`/secretPassword.txt:/secretPassword.txt:ro \
	aes-oh-aes \
	socat tcp-l:8000,reuseaddr,fork EXEC:"/usr/bin/java j.ctf.AesOhAes"

