f = open("test.txt", "w")
f.write("1000000\n")

for i in range(500000):
    f.write("1 ")
for i in range(500000):
    f.write("0 ")

f.write("\n")

for i in range(500000):
    f.write("0 ")
for i in range(500000):
    f.write("1 ")
f.write("\n")

for i in range(1, 1000000):
    f.write(str(i) + " " + str(i+1) + "\n")
    