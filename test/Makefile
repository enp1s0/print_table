CXX=g++
CXXFLAGS=-std=c++14 -I../include/

TARGET=table.test

$(TARGET):main.cpp
	$(CXX) $< -o $@ $(CXXFLAGS)
  
clean:
	rm -f $(TARGET)
