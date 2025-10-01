# ===== Makefile =====
CXX := g++

# ---- 옵션 토글 ----
# 사용법 예시:
#   make MODE=asan OMP=0     # ASan 빌드, OpenMP 끔
#   make MODE=rel  OMP=1     # 최적화 빌드, OpenMP 켬 (기본)
MODE ?= rel      # rel | asan | dbg
OMP  ?= 1        # 1=사용, 0=미사용

# ---- 공통 플래그 ----
CXXWARN   := -Wall -Wextra
INCLUDES  := -I/usr/include/eigen3
LDLIBS    :=

# ---- 빌드 모드별 플래그 ----
ifeq ($(MODE),asan)
  CXXMODE := -O1 -g -fsanitize=address,undefined -fno-omit-frame-pointer
else ifeq ($(MODE),dbg)
  CXXMODE := -O0 -g
else
  CXXMODE := -O3
endif

# OpenMP 토글
ifeq ($(OMP),1)
  OMPFLAG := -fopenmp
else
  OMPFLAG :=
endif

CXXFLAGS := -std=c++17 $(CXXMODE) $(CXXWARN) $(OMPFLAG) $(INCLUDES)
LDFLAGS  := $(OMPFLAG)
# macOS라면:
# CXXFLAGS := -std=c++17 $(CXXMODE) $(CXXWARN) -Xpreprocessor $(OMPFLAG) $(INCLUDES)
# LDFLAGS  := $(OMPFLAG)
# LDLIBS   := -lomp

# ---- 타깃/소스 ----
TARGET := topology_node2
SRCS   := topology_node2.C Tensor.C 
OBJS   := $(SRCS:.C=.o)

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXMODE) -o $@ $^ $(LDFLAGS) $(LDLIBS)

%.o: %.C
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
# ===== end =====

