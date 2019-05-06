import os
import subprocess

from flask import Flask, render_template

app = Flask(__name__)

# "Now you see me, now you don't"
#<!--
def listdir(path):
    banner, *entries = subprocess.check_output(['ls', '-lah', '--', path]).decode().splitlines()
    entries = map(str.split, entries)
    return render_template('list_files.html', banner=banner, path=path, entries=entries)


def getfile(path):
    with open(path, 'rb') as f:
        return render_template('show_file.html', path=path, content=f.read().decode())


@app.route('/', defaults={'path': './'})
@app.route('/<path:path>')
def s(path):
    if path == 'favicon.ico':
        return ''

    if os.path.isdir(path):
        return listdir(path)
    else:
        return getfile(path)
#--!>

if __name__ == '__main__':
    app.run(host='0.0.0.0', debug=True)
