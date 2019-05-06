FROM disconnect3d/nsjail:2.8

RUN apt update && apt-get install -y openjdk-8-jdk socat
COPY j/ctf /j/ctf
RUN javac j/ctf/AesOhAes.java

