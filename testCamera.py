
import cv2

cap = cv2.VideoCapture(2)

def cameraVideo():
    while True:
        ret, frame = cap.read()
        if ret:
            cv2.imshow('frame', frame)
            if cv2.waitKey(25) & 0xFF == ord('q'):
                break
        else:
            break            

def captureImage():
    result, image = cap.read()
    if result:
        cv2.imwrite("images.jpg", image)
    else:
        print("No image detected. Please! try again")      

cameraVideo()
captureImage()
cap.release()



