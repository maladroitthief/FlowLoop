def sendCommand(cmd):
    "This sends a command over UDP to the 7i80 board and gets a response"
    sdata = cmd
    sdata = sdata.decode('hex');
    s.sendto(sdata,(sip,sport))
    try:
        data,addr = s.recvfrom(1280)
        print ('>'),data.encode('hex')
    except socket.timeout:
        print ('No answer')

import socket
import time
s = socket.socket(socket.AF_INET,socket.SOCK_DGRAM,0)
sip = "192.168.1.121"
sport = 27181
s.settimeout(.2)
# config the DDR registers
sendCommand("83C200110000C00001FEFF00FFFFFF00")
sendCommand("83420011")
# clear the data bus
sendCommand("01C2041001000000")
sendCommand("01C2041000000000")
# wait for pulses to start
print('turn pulses on...')
print('5...')
time.sleep(1)
print('4...')
time.sleep(1)
print('3...')
time.sleep(1)
print('2...')
time.sleep(1)
print('1...')
time.sleep(1)
# send the start prove signal
sendCommand('01C2001000004000')
sendCommand('01C2001000000000')

# start looping through the data
while(2 > 0):
    # latch the data
    print ('\nlatching data')
    sendCommand("01C200100000C000")
    sendCommand("01C2001000004000")
    # reg 0 - meter 1 fwd
    print ('\nmeter 1, fwd')
    sendCommand("01C2041000000000")
    sendCommand("82420410")
    # reg 1 - meter 2 fwd
    print ('\nmeter 2, fwd')
    sendCommand("01C2041000020000")
    sendCommand("82420410")
    # reg 10 - meter 1 rev
    print ('\nmeter 1, rev')
    sendCommand("01C2041000140000")
    sendCommand("82420410")
    # reg 11 - meter 2 rev
    print ('\nmeter 2, rev')
    sendCommand("01C2041000160000")
    sendCommand("82420410")
    # reg 20 - meter 1 err
    print ('\nmeter 1, err')
    sendCommand("01C2041000280000")
    sendCommand("82420410")
    # reg 21 - meter 2 err
    print ('\nmeter 2, err')
    sendCommand("01C20410002A0000")
    sendCommand("82420410")
    # reg 30 - meter 1 edges a
    print ('\nmeter 1, a, edges')
    sendCommand("01C20410003C0000")
    sendCommand("82420410")
    # reg 40 - meter 1 edges b
    print ('\nmeter 1, b, edges')
    sendCommand("01C2041000500000")
    sendCommand("82420410")
    # reg 31 - meter 2 edges a
    print ('\nmeter 2, a, edges')
    sendCommand("01C20410003E0000")
    sendCommand("82420410")
    # reg 41 - meter 2 edges b
    print ('\nmeter 2, b, edges')
    sendCommand("01C2041000200000")
    sendCommand("82420410")
    # reg 50 - meter 1 a timer
    print ('\nmeter 1, a, timer')
    sendCommand("01C2041000660000")
    sendCommand("82420410")
    # reg 60 - meter 1 b timer
    print ('\nmeter 1, b, timer')
    sendCommand("01C2041000780000")
    sendCommand("82420410")
    # reg 51 - meter 2 a timer
    print ('\nmeter 2, a, timer')
    sendCommand("01C2041000680000")
    sendCommand("82420410")
    # reg 61 - meter 2 b timer
    print ('\nmeter 2, b, timer')
    sendCommand("01C2041000800000")
    sendCommand("82420410")
    # reg 70 - prover 1 timer
    print ('\nprover 1 timer')
    sendCommand("01C20410008C0000")
    sendCommand("82420410")
    # reg 72 - meter 1 phase counts
    print ('\nmeter 1, phase counts')
    sendCommand("01C2041000900000")
    sendCommand("82420410")
    # reg 73 - meter 2 phase counts
    print ('\nmeter 2, phase counts')
    sendCommand("01C2041000920000")
    sendCommand("82420410")
    

# 0x1000  I/O port  0..23       01420010
# 0x1004  I/O port 24..47       01420410
# 0x1008  I/O port 48..71


    
