FROM python:3.7

RUN pip install flask gunicorn

# This could be done shorter but idk
RUN groupadd -g 99999 jailed
RUN useradd --uid 99999 --gid 99999 jailed
RUN mkdir /home/jailed
RUN chown jailed /home/jailed -R
RUN chmod 755 /home/jailed -R
USER jailed

#RUN find /usr/bin ! -name 'ls' -name ',' -delete
#RUN find /bin ! -name 'ls' -name ',' -delete

WORKDIR /task/task/task/task/task/task/task/task/task/task/task/task/task/task/task/task

CMD gunicorn -b 0.0.0.0:8000 -t 2 -w 3 app:app --access-logfile - --error-logfile -

