import serial.tools.list_ports

ports = serial.tools.list_ports.comports()
serialInst = serial.Serial()

portList = []

for onePort in ports: 
    portList.append(str(onePort))
    print(str(onePort))

serialInst.baudrate = 9600
serialInst.port = "COM3"
serialInst.open() 

while True:
    if serialInst.in_waiting:
        packet = serialInst.readline()
        print(packet.decode('utf'))