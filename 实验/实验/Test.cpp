#include <iostream>

class Complex {
private:
    double real; // 实部
    double imag; // 虚部

public:
    // 1. 构造函数（兼具默认构造和转换构造函数的功能）
    // 当只传入一个参数时（如 Complex(5)），它会将整数隐式转换为复数（实部为5，虚部为0）
    Complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {}

    // 2. 声明全局友元函数重载 "+"
    // 采用友元函数的好处：左右两个操作数都可以隐式调用转换构造函数
    friend Complex operator+(const Complex& c1, const Complex& c2);

    // 打印复数的方法
    void display() const {
        if (imag >= 0)
            std::cout << real << " + " << imag << "i" << std::endl;
        else
            std::cout << real << " - " << -imag << "i" << std::endl; // 处理虚部为负数的情况
    }
};

// 3. 在类外实现友元函数
Complex operator+(const Complex& c1, const Complex& c2) {
    return Complex(c1.real + c2.real, c1.imag + c2.imag);
}

int main() {
    // 初始化两个复数对象
    Complex c1(3.0, 4.0);
    Complex c2(1.5, -2.5);
    int i = 5;

    // 场景一：复数 + 复数 (c1 + c2)
    Complex res1 = c1 + c2;
    std::cout << "c1 + c2 = ";
    res1.display();

    // 场景二：整数 + 复数 (i + c1)
    // 此时编译器发现右边是 Complex，左边是 int。
    // 因为定义了友元函数且参数为 Complex，编译器会自动将整型 i 隐式转换为 Complex(5.0, 0.0)，然后再相加。
    Complex res2 = i + c1;
    std::cout << "i + c1  = ";
    res2.display();

    // 场景三：复数 + 整数 (c1 + i)
    // 同理，右边的整数 i 会被隐式转换为 Complex
    Complex res3 = c1 + i;
    std::cout << "c1 + i  = ";
    res3.display();

    return 0;
}