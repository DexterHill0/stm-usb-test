import serial
import serial.tools.list_ports
import sys
import wave
import numpy as np

ports = serial.tools.list_ports.comports()

usb_serial = next(port for port in ports if "Serial" in port.description or "FTDI" in port.manufacturer)

print(f"found serial device on {usb_serial.device}")

s = serial.Serial(usb_serial.device, baudrate=256000)


packets = 1000

pcm_data_raw = []

while packets > 0:
    pcm = s.read_until(b'\n').strip()

    samples = [int(i) for i in pcm.decode().removesuffix(",").split(",")]

    print(samples, packets)

    pcm_data_raw.extend(samples)

    packets -= 1


pcm_data = np.array(pcm_data_raw, dtype=np.int16)

print(pcm_data)

sample_rate = 48000  
num_channels = 1     
sample_width = 2     

with wave.open("output.wav", "w") as wav_file:
    wav_file.setnchannels(num_channels)       
    wav_file.setsampwidth(sample_width)       
    wav_file.setframerate(sample_rate)        
    wav_file.writeframes(pcm_data.tobytes())  
