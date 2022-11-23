# To run:
#    1. Run Node Server
#    2. Plug in and run Arduino
#    3. Run the arduino-reader.py




import requests 
import threading
import time
import csv


sensor_data_csv = open("sensor_data.csv", "w")
time_data_csv = open("time_data.csv", "w")






record = False
sensor_data_ax = []
sensor_data_ay = []
sensor_data_az = []
sensor_data_gx = []
sensor_data_gy = []
sensor_data_gz = []
time_data = []
startTime = 0


def send_req():
	global record
	global time_data
	global startTime
	URL = "http://127.0.0.1:3000"
	while(True):
		while(record):
			# GET ARDUINO DATA
			print("a")
			r = requests.get(url = URL)
			print("b")
			sensordata = r.json()
			sensor_data_ax.append(sensordata['ax'])
			sensor_data_ay.append(sensordata['ay'])
			sensor_data_az.append(sensordata['az'])
			# sensor_data_gx.append(sensordata['gx'])
			# sensor_data_gy.append(sensordata['gy'])
			# sensor_data_gz.append(sensordata['gz'])
			time_data.append(time.time() - startTime)
			


T = threading.Thread(target=send_req)
T.setDaemon(True)
T.start()


def main():
	global record
	global startTime
	while(True):
		user_input = input("Record (r): ")
		if user_input == 'r':
			
			startTime = time.time()
			record = True
			while(True):
				user_input = input("Stop Recording (x): ")
				if(user_input == 'x'):
					record = False

					writer = csv.writer(sensor_data_csv)
					writer.writerow(sensor_data_ax)
					writer.writerow(sensor_data_ay)
					writer.writerow(sensor_data_az)
					# writer.writerow(sensor_data_gx)
					# writer.writerow(sensor_data_gy)
					# writer.writerow(sensor_data_gz)
					sensor_data_csv.close()

					writer = csv.writer(time_data_csv)
					writer.writerow(time_data)
					time_data_csv.close()

					return


main()