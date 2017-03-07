TARGET=HorseRaceSorting
FLAGS=-std=c++11

.PHONY: all clean

all: $(TARGET)

$(TARGET):
	g++ $(TARGET).cc -o $(TARGET) $(FLAGS)

clean:
	rm -f $(TARGET)

rebuild: clean all