#!/bin/bash

docker rm -f random-lottery
docker build -t random-lottery .

docker run --restart=always -d \
	--memory=250M \
	--kernel-memory=250M \
	--privileged \
	-v `pwd`/task:/task:ro \
	-p 1342:8000 \
	--name random-lottery \
	random-lottery \
	nsjail -Ml --port 8000 --user 99999 --group 99999  --disable_proc --time_limit 900 -R / -- /task/random_lottery
