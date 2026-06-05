import subprocess
from picamera2 import Picamera2
import time
import gpiod
LED_PIN = 17
chip = gpiod.Chip('gpiochip4')
led_line = chip.get_line(LED_PIN)
led_line.request(consumer="LED", type=gpiod.LINE_REQ_DIR_OUT)
picam2 = Picamera2()
while True:
   capture_config = picam2.create_still_configuration()
   picam2.start(show_preview=True)
   time.sleep(2)
   picam2.switch_mode_and_capture_file(capture_config, "example.jpg")
   
   subprocess.call(['convert', './example.jpg', '-threshold', '+60%', 'speech.jpg'])
   print("Performing OCR")
   subprocess.call(['tesseract', 'speech.jpg', 'speech'])
   print("The detected text is")

   subprocess.call(['cat', 'speech.txt'])
   with open(r'speech.txt', 'r') as file:
# read all content from a file using read()
    content = file.read()
# check if string present or not
   if 'AMBULANCE' in content:
      print('AMBULANCE string exist')
      led_line.set_value(1)
   else:
    print('AMBULANCE string does not exist')
    led_line.set_value(0)
    print("Speaking text")
    subprocess.call(['festival', '--tts', 'speech.txt'])
   picam2.close()
   led_line.release()