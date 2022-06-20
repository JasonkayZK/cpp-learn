/**
根据以下语法规则：
    1、非类型模板参数可以使用lambda表达式，并且每个lambda表达式都拥有不同的匿名类型（尽管代码里面都是[]{}）；

    2、类模板内可以用友元注入的方式定义友元函数，从而为类外非模板函数提供定义；

    3、非模板非inline函数只能有一个定义；

    因此通过构造函数的lambda非类型模板参数实例化不同的DefiGen类，它们都为A_CAN_ONLY_CONSTRUCT_ONCE函数提供定义，

    在第二次实例化时会爆出A_CAN_ONLY_CONSTRUCT_ONCE函数重复定义的错误
 */
template<class T>
struct DeclGen {
    friend constexpr void A_CAN_ONLY_CONSTRUCT_ONCE(DeclGen);
};

template<class T, class V>
struct DefiGen : DeclGen<T> {
    friend constexpr void A_CAN_ONLY_CONSTRUCT_ONCE(DeclGen<T>) {}
};

class A {
public:
    template<auto L = [] {}>
    constexpr A() {
        A_CAN_ONLY_CONSTRUCT_ONCE(DefiGen<A, decltype(L)>());
    }
};

int main() {
    A a;
//    A b;

    return 0;
}
