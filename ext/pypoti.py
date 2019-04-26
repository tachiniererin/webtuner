#!/usr/bin/python3 -u

import json
import sys
import struct
import serial

def encodeMessage(messageContent):
    encodedContent = json.dumps(messageContent).encode('utf-8')
    encodedLength = struct.pack('@I', len(encodedContent))
    return {'length': encodedLength, 'content': encodedContent}

def sendMessage(encodedMessage):
    sys.stdout.buffer.write(encodedMessage['length'])
    sys.stdout.buffer.write(encodedMessage['content'])
    sys.stdout.buffer.flush()

try:
    with serial.Serial('/dev/ttyACM0', 115200, timeout=1) as ser:
        while True:
            line = ser.readline()
            if len(line) > 0:
                sendMessage(encodeMessage(line.decode("utf-8").rstrip()))
except serial.SerialException:
    sendMessage(encodeMessage("Error".rstrip()))
    sys.exit(0)
