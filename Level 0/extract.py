import sys

try:
    plaintext = open(sys.argv[1], "r").read()
except:
    print("File argument needed! %s <raw payload file>" % sys.argv[0])
    sys.exit()
data=('unsigned int payload[] = { 0x' + ', 0x'.join(hex(ord(x))[2:] for x in plaintext) + ' };')
print(data)

with open("shell.hex","w") as f:
	f.write(data)
	f.close()