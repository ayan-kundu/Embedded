import serial, time

# Set up the serial connection
ser = serial.Serial('COM5', 9600)  # Replace 'COM3' with your Arduino's port

# Read and print data from Arduino
while True:
    if ser.in_waiting > 0:
        arduino_output = ser.readline().decode('utf-8').strip()
        print(f"Arduino says: {arduino_output}")
        
        # Store the output in a variable
        # yaw=arduino_output[-3:] # needs adjustment
        # pitch=arduino_output[13:16] # needs adjustment
   
        # Print mushroom tilt values in console 
        # print(f"Mushroom inclined at: {yaw} w.r.t vertical plane || {pitch} rotated in horizontal plane")
    else:
        print('Gimbal status ',ser.in_waiting,'Program ended!')
        time.sleep(100)