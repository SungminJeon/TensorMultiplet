CXX = g++
CXXFLAGS = -std=c++17 -O3 -fopenmp -Wall -Wextra
INCLUDES = -I/usr/include/eigen3   # Eigen 헤더 경로

# 실행 파일 이름
TARGET = topology_node2

# 소스
SRCS = topology_node2.C Tensor.C
OBJS = $(SRCS:.C=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^

%.o: %.C
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

