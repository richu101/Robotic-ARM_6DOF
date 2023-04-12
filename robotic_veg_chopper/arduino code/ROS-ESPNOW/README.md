# This is a test code to send data from ros to ESP 32 and from that esp 32 to another using ESP-NOW Protocol 



## Step 1

upload the esp-now-slave.ino code to another esp 32

## Step 2

Find the mac address of the slave esp 32 and replace it in the arduino-serial-master.ino code

To find the mac address of the slave esp 32, [link]( "https://github.com/richu101/Robotic-ARM_6DOF/blob/main/robotic_veg_chopper/arduino%20code/ESP32_MAC/ESP32_MAC.ino")

## Step 3

Upload the arduino-serial-master.ino code to the master esp 32

## Step 4

Open the terminal and run roscore

## Step 5

Open another terminal and run the command  **rosrun rosserial_python serial_node.py**

## Step 6

Open another terminal and run the python file **talker.py**

if that dont work open another terminal and run the command **rosrun rosserial_python serial_node.py /dev/ttyUSB0**
/dev/ttyUSB0 is the port where the esp 32 is connected

## Step 7

type any floating point number in the terminal where the talker.py is running

## Step 8

The data will be sent from the ros to the master esp 32 and from that esp 32 to the slave esp 32 and from that slave esp 32 to serial monitor of computer where the slave esp 32 is connected





