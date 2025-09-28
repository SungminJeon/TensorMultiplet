CXX = g++
CXXFLAGS = -std=c++17 -O3 -march=native -DNDEBUG -fopenmp \
           -I/usr/include/eigen3 -I.

LDFLAGS = -fopenmp

SRCS = Tensor.C topology_opt.C
OBJS = $(SRCS:.C=.o)

TARGET = topology_opt

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o $@

%.o: %.C
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

