from matplotlib import pyplot

f = open("arduinoReadings.txt")
data = map(lambda reading: int(reading.replace("\n", "").replace("\xef\xbf\xbd2", "") or "0") , f.readlines())
f.close()

pyplot.plot(range(len(data)), data)
pyplot.xlabel("Nth Reading")
pyplot.ylabel("Detector reading")

pyplot.show()

pyplot.savefig("readingPlot.png")

    
