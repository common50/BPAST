CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude -Ithird_party/glad/include -Ithird_party/glm/include -Ithird_party/stb/include

SRCS := $(wildcard src/*.cpp src/*/*.cpp) third_party/glad/src/glad.c

ifeq ($(OS),Windows_NT)
	OUT = BPAST.exe
	LDFLAGS = -lglfw3 -lopengl32 -lgdi32 -luser32 -lshell32
	RM = del /Q
else
	OUT = BPAST
	LDFLAGS = -lglfw -lGL -ldl
	RM = rm -f
endif

$(OUT): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(OUT) $(LDFLAGS)

clean:
	-$(RM) $(OUT)
