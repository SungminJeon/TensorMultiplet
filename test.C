#include "Theory.h"

int main(){
    // 리스트 버전
    auto T = Theory::from({
        { s(12), n_(7) },
        { i(22) }
    });
    T.print();

    // 그래프 버전
    TheoryGraph G;
    auto A = G.add(s(12));
    auto B = G.add(n_(7));
    auto C = G.add(i(22));
    G.connect(A,B); // OK
    G.connect(B,C); // OK
    // G.connect(A,C); // 예외 (s-i 금지)
    G.print();
}
