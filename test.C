#include "Theory.h"
#include <iostream>

int main() {
    // 1) 그래프 구성: Side 두 개 + Node 하나
    TheoryGraph G;
    auto S1 = G.add(s(12));   // 사이드 링크 #1  (AT(-1), AT(-2)로 구성)
    auto S2 = G.add(s(13));   // 사이드 링크 #2  (AT(-1), AT(-2)와 동일 규칙이지만 파라미터는 지금 미사용)
    auto N  = G.add(n_(7));   // 노드 (AT(-7)) → 1x1 IF

    // 2) 간선 연결
    // (1) 자동 포트: S1.right ↔ N.left, weight=1
    G.connect(S1, N);

    // (2) 포트/가중치 명시: S2.right ↔ N.left, weight=2
    //     Node(N)은 곡선이 1개라 Left/Right 모두 index 0으로 매핑됨(현재 정책).
    G.connect(S2, Port::Right, N, Port::Left, 2);

    // 3) 그래프 구조 출력
    std::cout << "=== Graph Edges ===\n";
    G.print();

    // 4) 로컬 IF 확인
    std::cout << "\n=== Local IFs ===\n";
    std::cout << "S1 IF:\n"; PrintMatrixSafe(G.IF(S1.id));
    std::cout << "S2 IF:\n"; PrintMatrixSafe(G.IF(S2.id));
    std::cout << "N  IF:\n"; PrintMatrixSafe(G.IF(N.id));

    // 5) 전역 IF (포트/가중치 반영 글루잉)
    std::cout << "\n=== Global IF (weighted gluing) ===\n";
    auto IFg = G.ComposeIF_Gluing();
    PrintMatrixSafe(IFg);

    // 6) 호환 API (UnitGluing)도 동일 결과
    std::cout << "\n=== Global IF (unit gluing alias) ===\n";
    auto IFg2 = G.ComposeIF_UnitGluing();
    PrintMatrixSafe(IFg2);

    return 0;
}

