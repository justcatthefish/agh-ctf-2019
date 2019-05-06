#!/usr/bin/env bash

docker build . -t traverse-the-universe

docker rm -f traverse-the-universe

# cpu-quota - limit cpu to 30%
docker run --restart=always -d \
	--memory=250M \
	--kernel-memory=250M \
	--cap-drop=ALL \
	-v `pwd`/flag.txt:/flag.txt:ro \
	-v `pwd`/task/:/task/task/task/task/task/task/task/task/task/task/task/task/task/task/task/task:ro \
	-p 8001:8000 \
	--name traverse-the-universe \
	traverse-the-universe

