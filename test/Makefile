TARGET=test
SRCS  = $(shell  find ../src ./ -type f -regex ".*/*.cpp" | grep -v "../src/main.cpp")
OBJS = $(SRCS:.cpp=.o)
GTEST_DIR=../Dependencies/googletest
GMOCK_DIR=../Dependencies/googlemock

INCLUDES = -I../include -I./mocks
CPPFLAGS += -std=c++17 -Wall -isystem $(GTEST_DIR)/include -isystem $(GMOCK_DIR)/include $(INCLUDES) 
#CXXFLAGS += -O2 -std=c++17 -Wall  -pthread -g # $(INCLUDES)  
CXXFLAGS += -g -Wall -Wextra -pthread
LDFLAGS = -lpthread

GTESTS_OBJS = gtest_main.a gmock_main.a

all:$(TARGET)

gtest:
	make -f makefile-gtest all
$(TARGET).o: $(TARGET).cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) -c ./$(TARGET).cpp 

$(TARGET): $(TARGET).o $(OBJS)
	make gtest && $(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) $(OBJS) $(GTESTS_OBJS) -o $@ 
clean:
	make -f makefile-gtest clean