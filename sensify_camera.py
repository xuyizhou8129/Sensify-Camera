# import cv2

# cap = cv2.VideoCapture(0);

# if not cap.isOpened():
	# print("Error:Could not open webcam.")
	# exit()

# while(True):
	# ret,frame = cap.read()

# if ret:
	# cv2.imwrite('photo.jpg',frame)
	# cv2.imwrite('photo.jpg',frame)
	# print("Photo saved")
# else:
	# print("Error: Could not read frame from webcam.")
	
# cap.release()

# from picamera2 import Picamera2
# import cv2
# picam = Picamera2()
# picam.preview_configuration.controls.FrameRate = 30
# picam.start()

# while True:
	# frame = picam.capture_array()
	# cv2.imshow("steam", frame)
	
	
	
# cv2.destroyAllWindows()
# picam.stop()

from picamzero import Camera
from time import sleep
cam = Camera()
cam.start_preview()
sleep(5)
