CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude

SRC = src/main.cpp src/glad.c

ifeq ($(OS),Windows_NT)
	OUT = BPAST.exe
	LDFLAGS = -lglfw3 -lopengl32 -lgdi32 -luser32 -lshell32
	RM = del /Q
else
	OUT = BPAST
	LDFLAGS = -lglfw -lGL -ldl
	RM = rm -f
endif

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT) $(LDFLAGS)

clean:
	-$(RM) $(OUT)
