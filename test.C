#include "Theory.h"
#include <iostream>

int main(){
    // 1) 선형 Theory
    //
    //

std::cout << " dfjkajfkl? " << std::endl;
    auto T = Theory::from({
        { s(12), n_(7) },  // s-i 인접 금지 규칙: 여기서는 s-n 이라 OK
        { i(55) }          // 세그먼트 경계 n|i 도 OK (s|i만 금지)
    });

	
    std::cout << " djfkafjdlkjfj " << std::endl;
    T.print();

    std::cout << " dkfjafjdkjfkdjfkladsfj " << std::endl;
    T.PrintIF(0,0);

    std::cout << " dkf;sfkk j"  << std::endl;

    auto IF1 = T.TheoryIF_BlockDiag();
    std::cout << "BlockDiag(Theory):\n";
    PrintMatrixSafe(IF1);   // 절대 <<IF1 직접 출력하지 말 것

    // 2) 그래프 Theory
    TheoryGraph G;
    auto S = G.add(s(12));
    auto N = G.add(n_(7));
    auto I = G.add(i(55));
    auto J = G.add(i(55));

    G.connect(S,N);         // 자동 포트: S.right ↔ N.left
    G.connect(N,I);         // 자동 포트: N.right ↔ I.left
    G.connect(J,N);
    G.print();

    G.PrintIF(S.id);

    auto glued = G.ComposeIF_UnitGluing();
    std::cout << "Global IF (unit gluing):\n";
    PrintMatrixSafe(glued); // 안전 출력

    return 0;
}

