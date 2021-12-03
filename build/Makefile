CXX=g++
CXXFLAGS=-std=c++17 -fsanitize=address -Wall -Wextra -pedantic -O3 -D IMAGE_PATH="../images"
#-Werror
LDFLAGS=-fsanitize=address
LIBFLAGS=-lm

WX_CONFIG := wx-config

WX_CXXFLAGS := $(shell $(WX_CONFIG) --cxxflags)
WX_LIBS := $(shell $(WX_CONFIG) --libs)

CXXFLAGS+=$(WX_CXXFLAGS)
LIBFLAGS+=$(WX_LIBS)

OBJ_DIR=./objs
#SRC_DIR := $(wildcard ../src/*)
SRC_DIR=../src

SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC))

EXEC=main.out

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LIBFLAGS)

$(OBJ): $(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm $(OBJ) $(EXEC)

run: all
	./$(EXEC)