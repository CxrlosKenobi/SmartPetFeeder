# Weight sensor code


# Code to get weight from FSR402
def read_weight():
    global message

    while reading:
        message = f"Weight: {sensor.value:1.2f} kg"
        print(message)

        sleep(0.1)



# Sensor de Proximidad
from signal import signal, SIGTERM, SIGHUP, pause
from time import sleep
from threading import Thread
from gpiozero import DistanceSensor

reading = True
sensor = DistanceSensor(echo=20, trigger=21)

def safe_exit(signum, frame):
    exit(1)

def read_distance():
    global message

    while reading:
        message = f"Distance: {sensor.value:1.2f} m"
        print(message)

        sleep(0.1)

try:
    signal(SIGTERM, safe_exit)
    signal(SIGHUP, safe_exit)

    reader = Thread(target=read_distance, daemon=True)
    reader.start()

    pause()

except KeyboardInterrupt:
    pass

finally:
    reading = False
    reader.join()
    sensor.close()


# Cámara RPi



# Micro Servo Motor
