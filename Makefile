TARGET=HorseRaceSorting

.PHONY: all clean

all: $(TARGET)

$(TARGET):
	g++ $(TARGET).cc -o $(TARGET)

clean:
	rm -f $(TARGET)

rebuild: clean all