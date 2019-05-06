#!/usr/bin/env bash

function run_generic_task() {
	(cd $1; bash -x ./run.sh)
}

function run_php_task() {
	bash -x ./run_php.sh "$1" -p "$2":80
}

run_php_task "PHPSon" 8081
run_php_task "PHPSon 2" 8082
run_php_task "PHPCollision" 8083
run_php_task "PHPMagic" 8084
run_php_task "sss" 8085

run_generic_task traverse_the_universe
run_generic_task exp0
run_generic_task exp2
run_generic_task math-game
run_generic_task random_lottery
