import threading
import numpy as np
import face_recognition as fr
import cv2
#import os

class VideoWorker():
    def __init__(self, signalSend):
        self.WorkThread = None
        self.ThEvent =  threading.Event()
        self.IsContinue = False
        self.SignalSend= signalSend
        self.ThEvent.clear()
        #opencv 파트
        self.video_capture = cv2.VideoCapture(cv2.CAP_ANY+0)
        self.me_image = fr.load_image_file('me.jpg')
        self.me_face_encoding = fr.face_encodings(self.me_image)
        self.known_face_encondings = [self.me_face_encoding][0]
        self.known_face_names = ["Me"]

    def ImageProc(self):
        ret, frame = self.video_capture.read()
        

        if not ret:
            return
        detectMe = False
        face_locations = fr.face_locations(frame)
        face_encodings = fr.face_encodings(frame, face_locations)
        
        for (top, right, bottom, left), face_encoding in zip(face_locations, face_encodings):
            matches = fr.compare_faces(self.known_face_encondings, face_encoding)

            name = "Unknown"

            face_distances = fr.face_distance(self.known_face_encondings, face_encoding)
            
            if len(face_distances) == 0 :
                print('distance count zero')
                continue

            best_match_index = np.argmin(face_distances)

            if matches[best_match_index]:
                name = self.known_face_names[best_match_index]
                detectMe=True
            else:
                print('unknown')

            cv2.rectangle(frame, (left, top), (right, bottom), (0, 0, 255), 2)
            cv2.rectangle(frame, (left, bottom -35), (right, bottom), (0, 0, 255), cv2.FILLED)
            font = cv2.FONT_HERSHEY_SIMPLEX
            cv2.putText(frame, name, (left + 6, bottom - 6), font, 1.0, (255, 255, 255), 1)
        
        cv2.imshow('Webcam_facerecognition', frame)

        if detectMe:
            self.SignalSend.PublishMessage('detect', '1')
        else :
            self.SignalSend.PublishMessage('detect', '0')

    def WorkProc(self):
        self.IsContinue=True
        
        while self.IsContinue:
            #print("event wait")
            self.ThEvent.wait()
            #print("proc2")
            self.ImageProc()
            cv2.waitKey(33) 
                

    def Start(self):
        if self.WorkThread == None:
            print('create thread')
            self.WorkThread = threading.Thread(target=self.WorkProc)
            self.WorkThread.setDaemon(True)
            self.WorkThread.start()

        if not self.ThEvent.is_set():
            print('Activate ThEvent')
            self.ThEvent.set()
        
    def Stop(self, terminate = False):
        if self.ThEvent.is_set():
            print('Deactivate ThEvent')
            self.ThEvent.clear()

        if terminate:
            self.Dispose()

    def Dispose(self):
        self.IsContinue=False
        self.ThEvent.set()
        
        if self.WorkThread != None:
            self.WorkThread.join()
            self.WorkThread=None

        self.video_capture.release()
        cv2.destroyAllWindows()
