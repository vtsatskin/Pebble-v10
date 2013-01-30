#simplest ruby program to read from arduino serial, 
#using the SerialPort gem
#(http://rubygems.org/gems/serialport)

require "serialport"

#params for serial port
port_str = "/dev/tty.usbmodem1421"
baud_rate = 9600
data_bits = 8
stop_bits = 1
parity = SerialPort::NONE

sp = SerialPort.new(port_str, baud_rate, data_bits, stop_bits, parity)

time = Time.now
sp.puts(time.strftime("%D") + "        " + time.strftime("%r") + "\\")

sp.close 