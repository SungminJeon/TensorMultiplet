#pragma once
#include <vector>
#include <string>
#include <initializer_list>
#include <utility>
#include <stdexcept>
#include <iostream>
#include <functional>
#include <unordered_map>



enum class Kind { SideLink, InteriorLink, Node };

struct Spec { Kind kind; int param; };
// 간단 헬퍼
inline Spec s(int p){ return {Kind::SideLink, p}; }
inline Spec i(int p){ return {Kind::InteriorLink, p}; }
inline Spec n_(int p){ return {Kind::Node, p}; }

struct TensorMultiplet {
	int tensors = 0, hypers = 0, vectors = 0;
};

class Tensors {
	public:
		Tensor(Kind k, int p) : kind_(k), param_(p) {
			tm_ = computeTM(k, p);
		}
		// 후처리(니가 쓰려던 AT/AL) – 아직 내부 로직은 빈칸으로
		Tensor& AT(int x) { at_ += x; return *this; }
		Tensor& AL(int x) { al_ += x; return *this; }

		Kind kind() const { return kind_; }
		int  param() const { return param_; }
		const TensorMultiplet& TM() const { return tm_; }

	private:
		Kind kind_;
		int  param_;
		TensorMultiplet tm_;
		int at_ = 0, al_ = 0;

		static TensorMultiplet computeTM(Kind k, int p){
			TensorMultiplet t{};
			// TODO: 네 실제 규칙으로 교체
			if (k==Kind::SideLink){ t.tensors=p/2; }
			else if (k==Kind::InteriorLink){ t.tensors=p; }
			else { t.hypers=p; }
			return t;
		}
};
