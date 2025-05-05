CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude

SRC = src/main.cpp src/DNSResolverFactory.cpp

ifeq ($(OS),Windows_NT)
    SRC += src/WINDNSResolver.cpp
    LDLIBS = -lws2_32
    TARGET = dns_explorer.exe
    RM = del /Q
    NULL = nul
else
    SRC += src/POSIXDNSResolver.cpp
    LDLIBS =
    TARGET = dns_explorer
    RM = rm -f
    NULL = /dev/null
endif

OBJ = $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDLIBS)

clean:
	-$(RM) $(OBJ) $(TARGET) 2>$(NULL)
