from datetime import datetime, timedelta
import paho.mqtt.client as mqtt
import RPi.GPIO as GPIO
import time

flag = 0
on_time = 0

def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("connected OK")
    else:
        print("Bad connection : ", rc)

def on_message(client, userdata, msg):
    GPIO.setmode(GPIO.BOARD)
    GPIO.setwarnings(False)
    GPIO.setup(11, GPIO.OUT)
    data = str(msg.payload)

    if (data.find('1') > 0):
        global flag
        global on_time
        flag = 1
        on_time = time.time()
        GPIO.output(11, True)
    elif (data.find('0') > 0):
        off_time = time.time()
        if (flag == 1):
            diff_time = off_time - on_time
            if (diff_time <= 3):
                GPIO.output(11, True)
            else:
                GPIO.output(11, False)
                flag = 0
        else:
            GPIO.output(11, False)
    
    #print(data)

client = mqtt.Client()

client.on_connect = on_connect
client.on_message = on_message

client.connect('localhost')
client.subscribe('detect',1)
client.loop_forever()
GPIO.clear(11)
