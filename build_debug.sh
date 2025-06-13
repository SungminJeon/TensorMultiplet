
#!/usr/bin/env bash
#──────────────────────────────
# build.sh – compile Theory project
#──────────────────────────────
set -e

# ── 옵션 ─────────────────────
CXX=g++
CXXFLAGS="-std=c++17 -O2 -Wall -Wextra"
OUT=debug                 # 실행 파일 이름
SRC=("debug.C" "Theory.C")   # 소스 파일 목록

# Eigen 헤더 경로(보통 /usr/include/eigen3)
EIGEN_INC=$(pkg-config --cflags eigen3 2>/dev/null || echo "-I/usr/include/eigen3")

# ── 컴파일 ───────────────────
echo "[+] building $OUT ..."
$CXX $CXXFLAGS $EIGEN_INC "${SRC[@]}" -o "$OUT"

echo "[✓] done → ./$OUT"
