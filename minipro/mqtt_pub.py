import paho.mqtt.client as mqtt
import json

class mqttpub():
    def __init__(self):
        self.Client =  mqtt.Client()
        self.Client.on_connect = self.OnConnected
        self.Client.on_disconnect = self.OnDisconnected
        self.Client.on_publish = self.OnPublished

    def OnConnected(self, client, userdata, flags, rc):
        if rc == 0:
            print("connected ok")

        else:
            print("bad connection returned code= ", rc)

    def OnDisconnected(self,client, userdata, flags, rc = 0):
        print(str(rc))

    def OnPublished(self,client, userdata, mid):
        pass
        #print("in on_pub callback data= ", userdata)

    def Connect(self, address, port):
        self.Client.connect(address, port)
        self.Client.loop_start()

    def PublishMessage(self, topic, message, qos = 1):
        if self.Client.is_connected():
            self.Client.publish(topic, message, qos)

        else :
            print('not connected')
    
    def Disconnect(self):
        self.Client.loop_stop()
        self.Client.disconnect()
