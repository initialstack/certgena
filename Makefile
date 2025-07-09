CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude -O2

# Source files
SRC = src/main.cpp \
      src/executor/OpenSSLExecutor.cpp \
      src/generator/CertificateGenerator.cpp \
      src/generator/OpenSSLConfigCreator.cpp \
      src/manager/CertificateManager.cpp

# Object files - derived from source files
OBJ = $(SRC:.cpp=.o)

# Name of the executable target
TARGET = certgen

.PHONY: all clean

# Default target: builds the executable
all: $(TARGET)

# Rule to link the executable
# Links all object files ($^) into the target ($@)
$(TARGET): $(OBJ)
      $(CXX) $(CXXFLAGS) -o $@ $^

# Rule to compile individual source files into object files
# $<: the first prerequisite (the .cpp file)
# $@: the target (the .o file)
%.o: %.cpp
      $(CXX) $(CXXFLAGS) -c $< -o $@

# Cleans up generated object files and the executable
clean:
      rm -f $(OBJ) $(TARGET)
