# Makefile for Airplane Fleet Management System
# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -g

# Directories
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
BIN_DIR = bin
DATA_DIR = data

# Source files
SOURCES = $(SRC_DIR)/PlaneClass.cpp \
          $(SRC_DIR)/Destination.cpp \
          $(SRC_DIR)/Airplane.cpp \
          $(SRC_DIR)/FleetManager.cpp \
          $(SRC_DIR)/main.cpp

# Object files
OBJECTS = $(OBJ_DIR)/PlaneClass.o \
          $(OBJ_DIR)/Destination.o \
          $(OBJ_DIR)/Airplane.o \
          $(OBJ_DIR)/FleetManager.o \
          $(OBJ_DIR)/main.o

# Target executable
TARGET = $(BIN_DIR)/fleet_manager

# Default target
all: directories $(TARGET)

# Create necessary directories
directories:
	@mkdir -p $(OBJ_DIR) $(BIN_DIR) $(DATA_DIR)

# Link object files to create executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files to object files
$(OBJ_DIR)/PlaneClass.o: $(SRC_DIR)/PlaneClass.cpp $(INC_DIR)/PlaneClass.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJ_DIR)/Destination.o: $(SRC_DIR)/Destination.cpp $(INC_DIR)/Destination.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJ_DIR)/Airplane.o: $(SRC_DIR)/Airplane.cpp $(INC_DIR)/Airplane.h $(INC_DIR)/PlaneClass.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJ_DIR)/FleetManager.o: $(SRC_DIR)/FleetManager.cpp $(INC_DIR)/FleetManager.h \
                           $(INC_DIR)/Airplane.h $(INC_DIR)/Destination.h $(INC_DIR)/PlaneClass.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp $(INC_DIR)/FleetManager.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Clean build artifacts
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Clean all (including data files)
cleanall: clean
	rm -rf $(DATA_DIR)/*.dat

# Run the program
run: all
	./$(TARGET)

# Phony targets
.PHONY: all clean cleanall directories run
