import cv2
import HandTrackingModule3 as HD
import cvzone
import serial
import time

wCam,hCam =1280,720

cap = cv2.VideoCapture(0)
cap.set(3,wCam)
cap.set(4,hCam)
detector = HD.handDetector(maxHands=1,detectionCon=0.7)
myserial = serial.Serial("COM5",9600)
pTime = 0



while True:
    success, img = cap.read()
   # cTime=time.time()
    #fps = 1/(cTime-pTime)
    #pTime = cTime
    #cv2.putText(img,f'FPS: {int(fps)}',(40,40),cv2.FONT_HERSHEY_COMPLEX,1,(0,0,255),1)
    cv2.putText(img, f'Khalaf', (850, 700), cv2.FONT_HERSHEY_COMPLEX, 2, (0, 0, 255), 2)
    img = detector.findHands(img)
    lmList, bbox = detector.findPosition(img)

    if lmList:
        fingers = detector.fingersUp()
        print(fingers)
        xx = "$"+str(fingers[4])+str(fingers[0])+str(fingers[2])+str(fingers[3])+str(fingers[1])
        print(xx)
        myserial.write(xx.encode())
    cv2.imshow("Image", img)
    cv2.waitKey(1)