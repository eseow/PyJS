TARGET=test
SRCS  = $(shell  find ../src ./ -type f -regex ".*/*.cpp" | grep -v "../src/main.cpp")
OBJS = $(SRCS:.cpp=.o)

LIB_DIR=/usr/lib/x86_64-linux-gnu
LIBS=libgtest.a libgtest_main.a libgmock.a libgmock_main.a

INCLUDES = -I../include -I./mocks
CPPFLAGS += -std=c++17 -Wall $(INCLUDES) 
CXXFLAGS += -g -Wall -Wextra -pthread
LDFLAGS = -lpthread

all:$(TARGET)

$(TARGET): $(TARGET).o $(OBJS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) $(OBJS) $(addprefix $(LIB_DIR)/, $(LIBS)) -o $@ 
clean:
	$(RM) $(OBJS) $(TARGET)