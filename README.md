# justCatTheFish & SKN Telephoners CTF
## 27th April 2019

This repository contains challenges from a [CTF event](https://ctftime.org/ctf-wtf/) held at the AGH UST in Kraków and organised by [SKN Telephoners](http://telephoners.agh.edu.pl/)(organization) and [justCatTheFish](https://ctftime.org/team/33893) team (tasks).


The event lasted for about seven hours and there were twelve teams, each consisting of two members. The final scoreboard can be seen below:

![](/images/scoreboard.png)

Three top teams were gifted tickets for IT confereces: ([CONFidence](https://confidence-conference.org/2019/krakow.html), [PLNOG](https://plnog.pl/) or [JDD](https://jdd.org.pl/)) as a reward.

## Playing offline

If you want to test out yourself, all the tasks are included in this repo.

The tasks can be found in `offline` and `online` directories. Each task has a `README.md` that contains the description given to participants along with the number of solves during the event.

The online tasks were hosted by using Docker; in order to host all of them on your own machine, you need to have Linux, install Docker (e.g. `apt install docker-io`) and run `./run_all.sh`.

To stop hosting them, you need to remove containers by hand - list them with `docker ps -a` and remove them with `docker rm -f <container name or id>` (run for each container).
