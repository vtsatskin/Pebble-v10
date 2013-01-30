#simplest ruby program to read from arduino serial, 
#using the SerialPort gem
#(http://rubygems.org/gems/serialport)

require "serialport"
require "grackle"

client = Grackle::Client.new
user = client.users.show.pebble?
puts user.status.text

#params for serial port
port_str = "/dev/tty.usbmodem1421"
baud_rate = 9600
data_bits = 8
stop_bits = 1
parity = SerialPort::NONE

# See String#encode
encoding_options = {
  :invalid           => :replace,  # Replace invalid byte sequences
  :undef             => :replace,  # Replace anything not defined in ASCII
  :replace           => '',        # Use a blank for those replacements
  :universal_newline => true       # Always break lines with \n
}
safe_str = (user.status.text.encode Encoding.find('ASCII'), encoding_options).tr("\n", " ")
puts safe_str

sp = SerialPort.new(port_str, baud_rate, data_bits, stop_bits, parity)

sp.puts(safe_str + "\\")

sp.close