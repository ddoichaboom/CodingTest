// 로컬 테스트 헬퍼 - test.cpp에서 solution.cpp 다음에 include 한다.
//
//   CHECK(solution({1, 2, 3}), 6);
//   CHECK(solution({"a", "b"}), {"b", "a"});
//
// 실패하면 기대값과 실제값을 출력하고, Report()가 실패 여부를 종료 코드로 돌려준다.
#pragma once
#include <iostream>
#include <string>
#include <vector>

namespace test
{
    template <class T> struct Identity { using type = T; };

    // string 오버로드는 vector 템플릿보다 먼저 선언되어야 vector<string> 출력에서 찾힌다
    inline void Print(std::ostream& os, const std::string& s) { os << '"' << s << '"'; }
    inline void Print(std::ostream& os, bool b) { os << (b ? "true" : "false"); }
    template <class T> void Print(std::ostream& os, const T& v) { os << v; }
    template <class T> void Print(std::ostream& os, const std::vector<T>& v)
    {
        os << '[';
        for (size_t i = 0; i < v.size(); ++i)
        {
            if (i) os << ", ";
            Print(os, v[i]);
        }
        os << ']';
    }

    inline int g_Total = 0;
    inline int g_Fail = 0;

    // expected를 비추론 문맥으로 두어 CHECK(f(x), {1, 2, 3})처럼 중괄호 초기화를 쓸 수 있게 한다
    template <class A>
    void Check(const A& actual, const typename Identity<A>::type& expected, const char* expr, int line)
    {
        ++g_Total;
        if (actual == expected)
            return;

        ++g_Fail;
        std::cout << "[FAIL] line " << line << ": " << expr << "\n  expected: ";
        Print(std::cout, expected);
        std::cout << "\n  actual  : ";
        Print(std::cout, actual);
        std::cout << '\n';
    }

    inline int Report()
    {
        std::cout << (g_Fail ? "FAILED " : "PASSED ") << (g_Total - g_Fail) << '/' << g_Total << '\n';
        return g_Fail ? 1 : 0;
    }
}

#define CHECK(actual, ...) test::Check((actual), __VA_ARGS__, #actual, __LINE__)
