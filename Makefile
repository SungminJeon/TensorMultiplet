#────────────────────────────────────────
# Makefile — manually specify build targets
#────────────────────────────────────────

CXX      = g++
CXXFLAGS = -std=c++17 -O3 -Wall -Wextra -fopenmp -DNDEBUG
INCLUDES = -I/usr/include/eigen3 -I.

# 공용 코어
CORE_SRC = Tensor.C
CORE_OBJ = $(CORE_SRC:.C=.o)
CORE_LIB = libcore.a

# 👇 여기서 수동으로 빌드할 타깃을 지정
TARGETS = topology_node2_2 topology_fast

# ────────────────────────────────────────
all: $(CORE_LIB) $(TARGETS)

# 각 실행파일에 대응되는 소스 (.C 파일명 동일)
$(TARGETS): %: %.o $(CORE_LIB)
	@echo "[+] Linking $@"
	$(CXX) $(CXXFLAGS) $< -L. -lcore -o $@

$(CORE_LIB): $(CORE_OBJ)
	@echo "[+] Archiving $@"
	ar rcs $@ $^

%.o: %.C
	@echo "[+] Compiling $<"
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(TARGETS) $(CORE_OBJ) $(CORE_LIB) *.o *.txt

.PHONY: all clean

