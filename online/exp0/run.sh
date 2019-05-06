#!/bin/bash

docker rm -f exp0
docker build -t exp0 .

docker run --restart=always -d \
	--memory=250M \
	--kernel-memory=250M \
	--privileged \
	-v `pwd`/flag.txt:/flag.txt:ro \
	-p 1337:8000 \
	--name exp0 \
	exp0 \
	nsjail -Ml --port 8000 --user 99999 --group 99999  --disable_proc --chroot /task --time_limit 30 -R /lib/ -R /lib64/ -R /usr/lib/ -R /flag.txt /exp0
