#include "Theory.h"
#include <iostream>

int main() {
	
	
	// 1) 그래프 구성: Side 두 개 + Node 하나
	TheoryGraph G;
	auto S1 = G.add(s(12));   // 사이드 링크 #1  (AT(-1), AT(-2)로 구성)
	auto S2 = G.add(s(13));   // 사이드 링크 #2  (AT(-1), AT(-2)와 동일 규칙이지만 파라미터는 지금 미사용)
	
	auto S3 = G.add(s(14));
	
	auto N  = G.add(n_(12));   // 노드 (AT(-7)) → 1x1 IF
	auto I = G.add(i(55));
	auto N1 = G.add(n_(12));
	auto I2 = G.add(i(55));
	auto N2 = G.add(n_(8));
	auto S4 = G.add(s(15));
	auto I3 = G.add(i(55));
	auto N3 = G.add(n_(6));
	auto S5 = G.add(s(15));

	// 2) 간선 연결
	// (1) 자동 포트: S1.right ↔ N.left, weight=1
	G.connect(S1, N);
	G.connect(S3, N);

	// (2) 포트/가중치 명시: S2.right ↔ N.left, weight=2
	//     Node(N)은 곡선이 1개라 Left/Right 모두 index 0으로 매핑됨(현재 정책).
	G.connect(S2, Port::Right, N, Port::Left, 2);

	// 3) 그래프 구조 출력
	G.connect(N, Port::Right, I, Port::Left, 1);
	G.connect(I, N1);
	G.connect(N1, S4);
	G.connect(N1, I2);
	G.connect(I2, N2);
	G.connect(N2, I3);
	G.connect(I3, N3);
	G.connect(N3,S5);
	
	

	std::cout << "=== Graph Edges ===\n";
	G.printLinearWithSides();


	Eigen::MatrixXi glued = G.ComposeIF_UnitGluing();


	Tensor g;

	g.SetIF(glued);
	g.Setb0Q();
	g.Blowdown5(1);
	
	std::cout << g.GetIFb0Q() << std::endl;
	


	

	std::cout << glued << std::endl;
	return 0;
}

