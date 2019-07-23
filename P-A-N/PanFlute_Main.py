from gpiozero import LED, Button # Pin in-out library
from random import randint		 # Random-number library
import time	   					 # 
from time import sleep
import datetime					 # 
import pygame					 # Audio-playback library
#from neopixel import * 			 # LED-strip library.
import argparse					 # ...Dunno what this is for
import serial					 # For serial connection to Arduino
import sys
import threading

def read_serial_A():
	global serial_input_A
	global change_in_input
	global first_time_read_data
	global string_A_is_A
	while True:
		serial_input_A = (((str(serial_Arduino_A.readline())).strip()).replace("\r","")).replace("\n","")
		change_in_input = True
		if first_time_read_data:
			first_time_read_data = False
			if serial_input_A[0] is 'A':
				string_A_is_A = True
			else:
				String_A_is_A = False

	
def read_serial_B():
	global serial_input_B
	global change_in_input
	global first_time_read_data
	global string_A_is_A
	while True:
		serial_input_B = (((str(serial_Arduino_B.readline())).strip()).replace("\r","")).replace("\n","")
		change_in_input = True	
		if first_time_read_data:
			first_time_read_data = False
			if serial_input_B[0] is 'A':
				string_A_is_A = False
			else:
				String_A_is_A = True	

def manage_audio(boolean, note):
	if note is "01_E":	
		if boolean:
			pygame.mixer.Channel(0).set_volume(0.0, 1.0)
			pygame.mixer.Channel(0).play(pygame.mixer.Sound(root_path + "01_E.wav"), loops = -1, fade_ms = fadein_length)
		else:
			pygame.mixer.Channel(0).fadeout(fadeout_length)
	if note is "02_F":
		if boolean:
			pygame.mixer.Channel(1).set_volume(0.1, 0.9)
			pygame.mixer.Channel(1).play(pygame.mixer.Sound(root_path + "02_F.wav"), loops = -1, fade_ms = fadein_length)
		else:
			pygame.mixer.Channel(1).fadeout(fadeout_length)
	if note is "03_G":	
		if boolean:
			pygame.mixer.Channel(2).set_volume(0.2, 0.8)
			pygame.mixer.Channel(2).play(pygame.mixer.Sound(root_path + "03_G.wav"), loops = -1, fade_ms = fadein_length)
		else:
			pygame.mixer.Channel(2).fadeout(fadeout_length)
	if note is "04_A":	
		if boolean:
			pygame.mixer.Channel(3).set_volume(0.3, 0.7)
			pygame.mixer.Channel(3).play(pygame.mixer.Sound(root_path + "04_A.wav"), loops = -1, fade_ms = fadein_length)
		else:
			pygame.mixer.Channel(3).fadeout(fadeout_length)
	if note is "05_H":	
		if boolean:
			pygame.mixer.Channel(4).set_volume(0.4, 0.6)
			pygame.mixer.Channel(4).play(pygame.mixer.Sound(root_path + "05_H.wav"), loops = -1, fade_ms = fadein_length)
		else:
			pygame.mixer.Channel(4).fadeout(fadeout_length)
	if note is "06_C":	
		if boolean:
			pygame.mixer.Channel(5).set_volume(0.5, 0.5)
			pygame.mixer.Channel(5).play(pygame.mixer.Sound(root_path + "06_C.wav"), loops = -1, fade_ms = fadein_length)
		else:
			pygame.mixer.Channel(5).fadeout(fadeout_length)
	if note is "07_D":	
		if boolean:
			pygame.mixer.Channel(6).set_volume(0.6, 0.4)
			pygame.mixer.Channel(6).play(pygame.mixer.Sound(root_path + "07_D.wav"), loops = -1, fade_ms = fadein_length)
		else:
			pygame.mixer.Channel(6).fadeout(fadeout_length)
	if note is "08_E":	
		if boolean:
			pygame.mixer.Channel(7).set_volume(0.7, 0.3)
			pygame.mixer.Channel(7).play(pygame.mixer.Sound(root_path + "08_E.wav"), loops = -1, fade_ms = fadein_length)
		else:
			pygame.mixer.Channel(7).fadeout(fadeout_length)
	if note is "09_F":	
		if boolean:
			pygame.mixer.Channel(8).set_volume(0.8, 0.2)
			pygame.mixer.Channel(8).play(pygame.mixer.Sound(root_path + "09_F.wav"), loops = -1, fade_ms = fadein_length)
		else:
			pygame.mixer.Channel(8).fadeout(fadeout_length)
	if note is "10_G":	
		if boolean:
			pygame.mixer.Channel(9).set_volume(0.9, 0.1)
			pygame.mixer.Channel(9).play(pygame.mixer.Sound(root_path + "10_G.wav"), loops = -1, fade_ms = fadein_length)
		else:
			pygame.mixer.Channel(9).fadeout(fadeout_length)
	if note is "11_A":	
		if boolean:
			pygame.mixer.Channel(10).set_volume(1.0, 0.0)
			pygame.mixer.Channel(10).play(pygame.mixer.Sound(root_path + "11_A.wav"), loops = -1, fade_ms = fadein_length)
		else:
			pygame.mixer.Channel(10).fadeout(fadeout_length)
		
# --------------------------------------------------- #
# -------------------- INITIATION ------------------- #
# --------------------------------------------------- #

# Open serial connection to both arduinos
try:
	serial_Arduino_A = serial.Serial('/dev/ttyACM0', 115200)
	print("ARDUINO-A :: port ACM0 connected")
except Exception as e:
	print(e)
	sys.exit(0)
	
try:
	serial_Arduino_B = serial.Serial('/dev/ttyACM1', 115200)
	print("ARDUINO-B :: port ACM1 connected")
except Exception as x:
	print(x)
	sys.exit(0)	

# Wait for the arduino to reset, which is does on new serial connections.
sleep(5)

# Initiate the audio mixer
pygame.mixer.pre_init(22050, -16, 2, 512)
pygame.mixer.init()
pygame.mixer.set_num_channels(11) # default is 8


# --------------------------------------------------- #
# -------------------- VARIABLES -------------------- #
# --------------------------------------------------- #

# Audio
root_path = "/home/pi/Desktop/P-A-N/Audio/"
note_volume_level = 1
fadein_length = 0
fadeout_length = 100

note_array = ["11_A","10_G","09_F","08_E","07_D","06_C","05_H","04_A","03_G","02_F","01_E"]
play_array = [False, False, False, False, False, False, False, False, False, False, False]

# String Variables
serial_input_A = ""
serial_input_B = ""
full_input_string = "nnnnnnnnnnn"

# Serial-related Variables
first_time_read_data = True
string_A_is_A = False
change_in_input = False
arduino_minimum_sensor_sample_size = 100		#{0, 15, 25, 35, 50} # b'X' is to encode it as bytes, which is the only way it can be sent via serial

# --------------------------------------------------- #
# -------------------- MAIN LOOP -------------------- #
# --------------------------------------------------- #

# Start serial-listening as independent threads
thread_A = threading.Thread(target=read_serial_A) 
thread_B = threading.Thread(target=read_serial_B)
thread_A.start()
thread_B.start()

# Send desired input-delay to the arduinos
serial_Arduino_A.write(b'%i' %arduino_minimum_sensor_sample_size)
serial_Arduino_B.write(b'%i' %arduino_minimum_sensor_sample_size)

print("going into loop")

while True:
	
	# Compile the full_input_string, with the right string going forst (the one that starts with 'A'
	if string_A_is_A:		
		full_input_string = "".join(reversed(serial_input_A[1:])) + serial_input_B
	else:
		full_input_string = "".join(reversed(serial_input_B[1:])) + serial_input_A
	
	print(full_input_string)
	
	# If we have a change in the input string, and the full string is length 11
	if change_in_input and len(full_input_string) is 11:
		for i in range(len(full_input_string)):								# Iterate through chars in the string
			if full_input_string[i] is 'y' and play_array[i] is False:		# If we find a y, and are not currently playing that note
				play_array[i] = True
				manage_audio(play_array[i],note_array[i])					# Play it
				change_in_input = False
			elif full_input_string[i] is 'n' and play_array[i] is True:		# If we find a n, and the note is currently playing
				play_array[i] = False
				manage_audio(play_array[i],note_array[i])					# Halt it. 
				change_in_input = False
				
							# Finally, note we no longer have a change in input.













