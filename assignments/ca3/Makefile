# Naming Convention Guideline
# Class names: PascalCase
# Function names: camelCase
# Variable names: lower_snake_case
# Constant names: UPPER_SNAKE_CASE

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

SRCS = main.cpp Utils.cpp SystemLogger.cpp Installable.cpp Module.cpp Package.cpp InstallationEngine.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = installer

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)