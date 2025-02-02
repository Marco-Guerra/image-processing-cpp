CXX=g++
CXXFLAGS=-std=c++17 -O2
#-D DEBUG_VAR 
#-Wall -Wextra 
#-fsanitize=address -pedantic 
#-g 
#-Werror
#LDFLAGS=-fsanitize=address
LIBFLAGS=-lm

WX_CONFIG := wx-config
OPENCV_CONFIG := pkg-config

WX_CXXFLAGS := $(shell $(WX_CONFIG) --cxxflags)
WX_LIBS := $(shell $(WX_CONFIG) --libs)

OPENCV_CXXFLAGS := $(shell $(OPENCV_CONFIG) --cflags opencv4)
OPENCV_LIBS := $(shell $(OPENCV_CONFIG) --libs opencv4)

CXXFLAGS+=$(WX_CXXFLAGS)
CXXFLAGS+=$(OPENCV_CXXFLAGS)
LIBFLAGS+=$(WX_LIBS)
LIBFLAGS+=$(OPENCV_LIBS)

OBJ_DIR=./objs
SRC_DIR=../src

SRC := $(wildcard $(SRC_DIR)/*/*.cpp)
OBJ := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC))
PCH := $(wildcard $(SRC_DIR)/include/*.hpp)
PCH_OUT := $(patsubst $(SRC_DIR)/include/%.hpp, ./%.hpp.gch, $(PCH))

EXEC=main.out

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LIBFLAGS)

$(OBJ): $(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm $(OBJ) $(EXEC)

generate_pch: $(PCH_OUT)
$(PCH_OUT): $(PCH)
	$(CXX) $(CXXFLAGS) $< -o $@

run: all
	./$(EXEC)

deploy:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(EXEC) $(LIBFLAGS)
	./$(EXEC)