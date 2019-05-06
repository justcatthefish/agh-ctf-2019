#!/bin/bash

docker rm -f math-game
docker build -t math-game .

docker run --restart=always -d \
	--memory=250M \
	--kernel-memory=250M \
	--privileged \
	-p 1340:8000 \
	--name math-game \
	math-game \
	nsjail -Ml --port 8000 --user 99999 --group 99999  --disable_proc --time_limit 30 -R / -R /task/fakepasswd:/etc/passwd -- /usr/bin/python3 /task/task.py
