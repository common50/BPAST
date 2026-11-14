CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude -Ithird_party/glad/include -Ithird_party/glm/include -Ithird_party/stb/include
AR = ar

LIB_SRCS := $(wildcard src/*.cpp src/*/*.cpp) third_party/glad/src/glad.c
LIB_OBJS := $(notdir $(LIB_SRCS))
LIB_OBJS := $(LIB_OBJS:.cpp=.o)
LIB_OBJS := $(LIB_OBJS:.c=.o)
APP_SRCS := examples/main.cpp

ifeq ($(OS),Windows_NT)
	OUT = BPAST.exe
	LIB = libBPAST.a
	LDFLAGS = -lglfw3 -lopengl32 -lgdi32 -luser32 -lshell32
	RM = del /Q
else
	OUT = BPAST
	LIB = libBPAST.a
	LDFLAGS = -lglfw -lGL -ldl
	RM = rm -f
endif

all: $(OUT)

lib: $(LIB)

$(LIB): $(LIB_SRCS)
	$(CXX) $(CXXFLAGS) -c $(LIB_SRCS)
	$(AR) rcs $(LIB) $(LIB_OBJS)

$(OUT): $(APP_SRCS) $(LIB)
	$(CXX) $(CXXFLAGS) $(APP_SRCS) -o $(OUT) -L. -lBPAST $(LDFLAGS)

clean:
	-$(RM) $(OUT) $(LIB) *.o

.PHONY: all lib clean
