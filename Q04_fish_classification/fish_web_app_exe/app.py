'''
Filename: app.py
Created Date: Wednesday, May 15th 2023, 19:36:43
Author: Quest Global
Copyright (c) 2023 Renesas
Functionality: Application for UI and WS communication to V2L board
'''

import base64
import socket
import subprocess

import cv2
import numpy as np
from flask import Flask, redirect, render_template, request, url_for
from flask_socketio import SocketIO, emit

app = Flask(__name__)
socketio = SocketIO(app)
request_main = None
client_socket = None
ip_address = None


@app.route('/', methods=['GET', 'POST'])
def index():
    """
    Render the index template and handle form submission for IP address.
    """
    if request.method == 'POST':
        global request_main
        request_main = request
        global ip_address
        ip_address = request.form['ip']
        ping_output = subprocess.Popen(
            ["ping", "-c", "1", ip_address], stdout=subprocess.PIPE).communicate()[0]
        print(ping_output)
        if "1 received" in ping_output.decode("utf-8"):
            src = "fish_classification"
            dest = f"root@{ip_address}:/home/root/fish_delivery"
            command = f"scp -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null -o LogLevel=ERROR {src} {dest}"
            subprocess.Popen(['ssh', '-o StrictHostKeyChecking=no',
                             f'root@{ip_address}', "for pid in $( ps |  grep fish | awk '{print $1}'); do kill -9 $pid; done ;"])
            subprocess.run(command, shell=True, capture_output=True)
            src = "fish_classification_model"
            dest = f"root@{ip_address}:/home/root/fish_delivery"
            command = f"scp -r -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null -o LogLevel=ERROR {src} {dest}"
            subprocess.run(command, shell=True, capture_output=True)
            command = f"ssh -o StrictHostKeyChecking=no {ip_address}"
            subprocess.Popen(['ssh', '-o StrictHostKeyChecking=no',
                             f'root@{ip_address}', "cd /home/root/fish_delivery/; ./fish_classification WS"])
            return redirect(url_for('upload_photo'))
        else:
            return render_template('index.html', error=True)
    else:
        return render_template('index.html', error=False)


@app.route('/upload_photo')
def upload_photo():
    """
    Render the upload_photo template.
    """
    return render_template('upload_photo.html')


@socketio.on('disconnect')
def test_discconect():
    """
    Handle the event when a client disconnects.
    """
    print('Client Disconnected')


@socketio.on('send_photo')
def send_photo(photo):
    """
    Receive and process the photo sent by the client.
    """
    print("connected")
    global request_main, ip_address
    photo_data = photo.split(',')[1]
    decoded_data = base64.b64decode(photo_data)
    img_buffer = cv2.imdecode(np.frombuffer(
        decoded_data, np.uint8), cv2.IMREAD_COLOR)
    cv2.imwrite("test.png", img_buffer)
    src = "test.png"
    dest = f"root@{ip_address}:/home/root/fish_delivery"
    command = f"yes | scp {src} {dest}"
    subprocess.run(command, shell=True, capture_output=True)
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect((ip_address, 2002))
    client_socket.sendall("test.png".encode())
    data = client_socket.recv(1024)
    class_name = data.decode("utf-8")
    print("Class :", class_name)
    emit('photo_sent', {'result': class_name})


if __name__ == "__main__":
    socketio.run(app, host='192.168.197.132')
