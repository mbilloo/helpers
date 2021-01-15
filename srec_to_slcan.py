import sys
import subprocess

MAX_BYTES_IN_CAN        =  8
MAX_DIGITS_FOR_SLCAN    = MAX_BYTES_IN_CAN * 2

CAN_SEND_COMMAND        = "cansend"
CAN_INTERFACE           = "can0"

SREC_START_ARB_ID       = "123"
SREC_CONTINUE_ARB_ID    = "456"
SREC_END_ARB_ID         = "789"

SREC_SINGLE_ARB_ID      = "2BC"


def usage():
    print("Usage: python3 srec_to_slcan.py <srec_file>")

if len(sys.argv) != 2:
    usage()
    sys.exit(1)

try:
    with open(sys.argv[1], 'r') as srec_file:
        lines = srec_file.readlines();
        for line in lines:
            if line[0] != 'S':
                print("Invalid SRecord in " % sys.argv[1]);
            new_line = '0' + line[1:].rstrip()
            srecord = [new_line[i:i+MAX_DIGITS_FOR_SLCAN] for i in range(0, len(new_line), MAX_DIGITS_FOR_SLCAN)]
            print(srecord)
            for hex_values in srecord:
                if len(srecord) == 1:
                    can_message = SREC_SINGLE_ARB_ID + "#" + hex_values
                else:
                    if srecord.index(hex_values) == 0:
                        can_message = SREC_START_ARB_ID + "#" + hex_values
                    elif srecord.index(hex_values) == len(srecord) -1:
                        can_message = SREC_END_ARB_ID + "#" + hex_values
                    else:
                        can_message = SREC_CONTINUE_ARB_ID + "#" + hex_values

                print("Can message = " + can_message)
                subprocess.run([CAN_SEND_COMMAND, CAN_INTERFACE, can_message])

                input("Enter")
except IOError as e:
        print("Couldn't open srec file (%s)." %  e)
