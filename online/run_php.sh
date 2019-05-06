#!/bin/bash

IMAGE_NAME="$1"

cd "${IMAGE_NAME}"

IMAGE_NAME_SLUG="${IMAGE_NAME,,}"
IMAGE_NAME_SLUG="${IMAGE_NAME_SLUG// /-}"
IMAGE_NAME_SLUG="${IMAGE_NAME_SLUG//_/-}"
IMAGE_NAME="${IMAGE_NAME// /_}"
shift


docker build . -t "${IMAGE_NAME_SLUG}"

docker rm -f "${IMAGE_NAME}"

# cpu-quota - limit cpu to 30%
docker run --restart=always -d \
	--memory=250M \
	--kernel-memory=250M \
	"$@" \
	--name "${IMAGE_NAME}" \
	"${IMAGE_NAME_SLUG}"

	#--cap-drop=ALL \
