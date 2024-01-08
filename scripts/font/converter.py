fileIn = open('ibm_bios_font.txt', 'r')
lines = fileIn.readlines()
 
fileOut = open('font.lua', 'w')
# fileOut.write("pog")

print("table = {")

character = 0
lineIndex = 0
for line in lines:
    if line[0] == '-':
        continue

    if lineIndex % 8 == 0:
        print("    },")
        print("    [" + str(character) + "] = {")
        character += 1

    string = line[5:]

    print("        ", end="")

    for i in range(0, 8):
        char = string[i]
        if char == '@':
            print("1, ", end="")
        else:
            print("0, ", end="")

    print("")
    # print("{}".format(string.strip()))

    lineIndex += 1

print("}")

# ----- [ ] (0) -----
# 0x00 ........
# 0x00 ........
# 0x00 ........
# 0x00 ........
# 0x00 ........
# 0x00 ........
# 0x00 ........
# 0x00 ........

fileIn.close()
fileOut.close()
