# C++basics

## 1. Virtual Function

```c++
#include <iostream>
using namespace std;

// Virtual Methods and Polymorphism
// Polymorpism allows you to treat subclasses as their superclass and yet
// call the correct overwritten methods in the subclass automatically

class Animal{
	public:
		void getFamily() { cout << "We are Animals" << endl; }

		// When we define a method as virtual we know that Animal
		// will be a base class that may have this method overwritten
		virtual void getClass() { cout << "I'm an Animal" << endl; }
};

class Dog : public Animal{
	public:
		void getClass() { cout << "I'm a Dog" << endl; }

};

class GermanShepherd : public Dog{
	public:
		void getClass() { cout << "I'm a German Shepherd" << endl; }
		void getDerived() { cout << "I'm an Animal and Dog" << endl; }

};

void whatClassAreYou(Animal *animal){ 
	animal -> getClass(); 
}

int main(){

	Animal *animal = new Animal;
	Dog *dog = new Dog;

	// If a method is marked virtual or not doesn't matter if we call the method
	// directly from the object
	animal->getClass();
	dog->getClass();

	// If getClass is not marked as virtual outside functions won't look for 
	// overwritten methods in subclasses however
	whatClassAreYou(animal);
	whatClassAreYou(dog);

	Dog spot;
	GermanShepherd max;

	// A base class can call derived class methods as long as they exist 
	// in the base class
	Animal* ptrDog = &spot;
	Animal* ptrGShepherd = &max;

	// Call the method not overwritten in the super class Animal
	ptrDog -> getFamily();

	// Since getClass was overwritten in Dog call the Dog version
	ptrDog -> getClass();

	// Call to the super class
	ptrGShepard -> getFamily();

	// Call to the overwritten GermanShepard version
	ptrGShepard -> getClass();

	return 0;
}
```

## 2. Struct&Class

C++中结构体（Struct）和类（Class）的主要区别在于：

1. **默认访问权限**：结构体的成员默认为公共（public）访问权限，而类的成员默认为私有（private）访问权限。
2. **继承类型**：在没有显式指定的情况下，从结构体派生的类默认是公共继承（public inheritance），而从类派生的类默认是私有继承（private inheritance）。
3. **用途与语义**：虽然结构体和类在C++中功能上非常相似，结构体通常用于简单的数据结构的表示，而类用于更复杂的数据封装和面向对象编程。

### 2.1 Extend

在C++中，结构体和类都可以包含成员变量、成员函数、构造函数、析构函数等。这意味着在功能上，结构体和类几乎是等价的，区别主要在于默认的访问控制和用法上的惯例。

C++中的`struct`对C中的`struct`进行了扩充，它已经不再只是一个包含不同数据类型的数据结构了，它已经获取了太多的功能。
`struct`能包含成员函数吗？ 能！
`struct`能继承吗？ 能！！
`struct`能实现多态吗？ 能！！！

有很多人应该已经知道这样一个事实，但总有些不知道的人，看到这些会感到很惊讶。是的，当我第一次注意到这个事实的时候，我也同样很吃惊。
既然这些它都能实现，那它和`class`还能有什么区别？
最本质的一个区别就是默认的[访问控制](https://so.csdn.net/so/search?q=访问控制&spm=1001.2101.3001.7020)，体现在两个方面：

1）默认的继承访问权限。`struct`是public的，`class`是private的。
如果不知道什么是public继承，什么是private继承的，可以去查书，这里暂不讨论。
你可以写如下的代码：

```cpp
struct A{
	char a;
}；

struct B : A{
	char b;
}；
1234567
```

这个时候B是public继承A的。如果都将上面的`struct`改成`class`，那么B是private继承A的。这就是默认的继承访问权限。所以我们在平时写[类继承](https://so.csdn.net/so/search?q=类继承&spm=1001.2101.3001.7020)的时候，通常会这样写：

```cpp
class B : public A
1
```

就是为了指明是public继承，而不是用默认的private继承。

当然，到底默认是public继承还是private继承，**取决于子类而不是基类**。我的意思是，`struct`可以继承`class`，同样`class`也可以继承`struct`，那么默认的继承访问权限是看子类到底是用的`struct`还是`class`。如下：

```cpp
struct A{}；

class B : A{}; //private继承

struct C : B{}； //public继承
12345
```

2）`struct`作为数据结构的实现体，它默认的数据访问控制是public的，而`class`作为对象的实现体，它默认的成员变量访问控制是private的。

注意我上面的用词，我依旧强调`struct`是一种数据结构的实现体，虽然它是可以像`class`一样的用。我依旧将`struct`里的变量叫数据，`class`内的变量叫成员，虽然它们并无区别。其实，到底是用`struct`还是`class`，完全看个人的喜好，你可以将你程序里所有的`class`全部替换成`struct`，它依旧可以很正常的运行。但我给出的最好建议，还是：当你觉得你要做的更像是一种数据结构的话，那么用`struct`，如果你要做的更像是一种对象的话，那么用`class`。

当然，我在这里还要强调一点的就是，对于**访问控制**，应该在程序里明确的指出，而不是依靠默认，这是一个良好的习惯，也让你的代码更具可读性。

说到这里，很多了解的人或许都认为这个话题可以结束了，因为他们知道`struct`和`class`的“唯一”区别就是访问控制。很多文献上也确实只提到这一个区别。

但我上面却没有用“唯一”，而是说的“最本质”，那是因为，它们确实还有<button>另一个区别</button>，虽然那个区别我们平时可能很少涉及。那就是：“`class`”这个关键字还用于<strong style="color:red ;">定义模板参数，就像“`typename`”</strong>。但关键字“`struct`”不用于定义模板参数。这一点在Stanley B.Lippman写的Inside the C++ Object Model有过说明。

问题讨论到这里，基本上应该可以结束了。但有人曾说过，他还发现过其他的“区别”，那么，让我们来看看，这到底是不是又一个区别。

还是上面所说的，C++中的`struct`是对C中的`struct`的扩充，既然是扩充，那么它就要兼容过去C中`struct`应有的所有特性。例如你可以这样写：

```cpp
struct A //定义一个struct
{
	char c1;
	int n2;
	double db3;
};

A a={'p',7,3.1415926}; //定义时直接赋值
12345678
```

也就是说`struct`可以在定义的时候用`{}`赋初值。那么问题来了，`class`行不行呢？将上面的`struct`改成`class`，试试看。报错！噢~于是那人跳出来说，他又找到了一个区别。我们仔细看看，这真的又是一个区别吗？

你试着向上面的`struct`中加入一个构造函数（或虚函数），你会发现什么？对，`struct`也不能用`{}`赋初值了。
以`{}`的方式来赋初值，只是用一个初始化列表来对数据进行按顺序的初始化，如上面如果写成
`A a={'p',7};`
则c1,n2被初始化，而db3没有。这样简单的copy操作，只能发生在简单的数据结构上，而不应该放在对象上。加入一个构造函数或是一个虚函数会使`struct`更体现出一种对象的特性，而使此`{}`操作不再有效。事实上，是因为加入这样的函数，使得类的内部结构发生了变化。
而加入一个普通的成员函数呢？你会发现`{}`依旧可用。其实你可以将普通的函数理解成对数据结构的一种算法，这并不打破它数据结构的特性。至于虚函数和普通成员函数有什么区别，我会具体写篇文章讨论。

那么，看到这里，我们发现即使是`struct`想用`{}`来赋初值，它也必须满足很多的约束条件，这些条件实际上就是让`struct`更体现出一种数据机构而不是类的特性。
那为什么我们在上面仅仅将`struct`改成`class`，`{}`就不能用了呢？其实问题恰巧是我们之前所讲的——访问控制！
你看看，我们忘记了什么？对，将`struct`改成`class`的时候，访问控制由public变为private了，那当然就不能用`{}`来赋初值了。加上一个public，你会发现，`class`也是能用`{}`的，和`struct`毫无区别！！！

```cpp
class A{ //定义一个class
public:
	char c1;
	int n2;
	double db3;
};

A a={'p',7,3.1415926}; //定义时直接赋值
12345678
```

做个总结，从上面的区别，我们可以看出，`struct`更适合看成是一个数据结构的实现体，`class`更适合看成是一个对象的实现体。所以我会提出什么时候用`struct`什么时候用`class`的建议。如果你有不同的看法，欢迎讨论。

## 3. Difference between instance and pointer

```c++
#include <iostream>
using namespace std;

class Car {
public:
    string color;

    Car() { // 构造函数
        cout << "Car created." << endl;
    }

    ~Car() { // 析构函数
        cout << "Car destroyed." << endl;
    }

    void startEngine() {
        cout << "Engine started on a " << color << " car." << endl;
    }
};
int main() {
    // 在栈上创建对象实例
    cout << "Creating an instance on the stack:" << endl;
    Car myCar; // 栈上创建
    myCar.color = "Red";
    myCar.startEngine();

    cout << "\n";

    // 在堆上创建对象指针
    cout << "Creating an instance on the heap:" << endl;
    Car* myCarPtr = new Car; // 堆上创建
    myCarPtr->color = "Blue";
    myCarPtr->startEngine();

    delete myCarPtr; // 释放堆上的对象

    return 0;
}
```

结果：

```bash
Creating an instance on the stack:
Car created.
Engine started on a Red car.

Creating an instance on the heap:
Car created.
Engine started on a Blue car.
Car destroyed.
Car destroyed.
```

创建一个实例（对象）和创建一个指针在C++中具有重要的不同含义和应用场景：

### 3.1 Creat instance（Object）

- **定义**：创建一个实例意味着在栈（Stack）上分配内存以存储类或结构体的对象。这种方式会自动管理内存，无需手动分配和释放。
- **语法**：`ClassName object;`
- **内存管理**：栈上分配的对象在其所在的作用域结束时自动销毁。
- **应用场景**：
  - 当对象的使用周期与其创建的作用域相匹配时。
  - 当需要快速分配和释放内存时。
  - 当对象的大小已知且较小时。
  - 适用于函数内部或作为类的成员，生命周期短。

### 3.2 Creat pionter

- **定义**：创建一个指针意味着在堆（Heap）上分配内存。这需要使用`new`关键字手动分配内存，并且在不再需要时使用`delete`来释放内存。
- **语法**：`ClassName* pointer = new ClassName;`
- **内存管理**：堆上分配的内存需要程序员手动管理，忘记释放会导致内存泄漏。
- **应用场景**：
  - 当对象的生命周期需要超出创建它的作用域时。
  - 当需要动态分配大量内存或对象大小在运行时才确定时。
  - 适用于需要在不同函数或类之间共享或传递对象时。
  - 当使用多态和继承时，指针和引用提供更多的灵活性。

在这个示例中，`createInstance` 函数在栈上创建一个`Car`对象，当函数结束时，该对象自动销毁。而`createPointer` 函数在堆上创建一个`Car`对象，需要显式调用`delete`来释放内存。

### 3.3 .&->

在C++中，点运算符（`.`）和箭头运算符（`->`）都用于访问对象的成员，但它们在不同的上下文中使用。

1. **点运算符（`.`）**：
   - **用途**：用于直接访问对象的成员。
   - **适用情况**：当你有一个对象实例（非指针）时使用。
   - **示例**：假设有一个类`ClassA`，它有一个成员函数`functionA()`。如果你创建了`ClassA`的一个对象`objA`，你可以使用点运算符来调用`functionA`，如`objA.functionA()`。

2. **箭头运算符（`->`）**：
   - **用途**：用于通过指针访问对象的成员。
   - **适用情况**：当你有一个指向对象的指针时使用。
   - **示例**：继续上面的例子，如果你有一个指向`ClassA`对象的指针`pObjA`，你可以使用箭头运算符来调用`functionA`，如`pObjA->functionA()`。

总的来说，点运算符用于对象实例，而箭头运算符用于对象的指针。箭头运算符实际上是对两个操作的简化：先对指针进行解引用（使用`*`运算符），然后访问成员（使用`.`运算符）。例如，`pObjA->functionA()` 等同于 `(*pObjA).functionA()`。

## 4. Various&Constant

```c++
#include <iostream>
#include <string>
using namespace std;

// const 与 #define
#define DPI 44 // 44 是什么 不需要关心

// 全局 一般不要用
int RandNum{0};
const double PI{3.1415926};

int main(int argc, char *argv[])
{
    cout << "Random Num : " << RandNum << endl;
    RandNum = 3;
    cout << "Random Num : " << RandNum << endl;
    // PI = 4.15;
    const int age = 45;
    const float oldWeight{88};

    // =、 {}
    float nowWeight{oldWeight + 30};
    cout << "age : " << age << endl;
    cout << "Weight : " << nowWeight << endl;

    int dpi_int{DPI};       // int
    string dpi_string{DPI}; // string

    cout << "dpi int " << dpi_int + 2 << endl;
    cout << "dpi string " << dpi_string << endl;
    cout << "dpi string "
         << "44 ascii ','" << endl;
}
```

The function of  `RandNum{0}` and `RandNum = 1` is the same.

### 4.1 Datatype&sizeof

```c++
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    // 对象一个类型
    int x{0};
    cout << sizeof(x) << endl;
    cout << "Intger  " << sizeof(int) << endl;
    cout << "Char " << sizeof(char) << endl;
    cout << "Bool  " << sizeof(bool) << endl;
    cout << "Float  " << sizeof(float) << endl;
    cout << "Double  " << sizeof(double) << endl;
    cout << "Long  " << sizeof(long) << endl;
    cout << "Long Long  " << sizeof(long long) << endl;
    cout << "Long Double  " << sizeof(long double) << endl;

    cout << "Unsigned long " << sizeof(unsigned long) << endl;
    cout << "Size_t " << sizeof(size_t) << endl;

    cout << "Bool*  " << sizeof(bool *) << endl;
    cout << "Float*  " << sizeof(float *) << endl;
    cout << "Double*  " << sizeof(double *) << endl;
    cout << "Long*  " << sizeof(long *) << endl;

    auto value1{12};  // int
    auto value2{2.4}; // double

    cout << "Int " << sizeof(value1) << endl;
    cout << "Double " << sizeof(value2) << endl;

    auto value3{123ll};
    auto value4{1.2f};
    auto value5{123ul}; // unsigned long
    auto value6{1.3l};

    cout << "Long Long " << sizeof(value3) << endl;
    cout << "Float " << sizeof(value4) << endl;
    cout << "Unsigned Long " << sizeof(value5) << endl;
    cout << "Long Double " << sizeof(value6) << endl;
}

```

<strong style="color:red">result:</strong>

```she
4
Intger  4
Char 1
Bool  1
Float  4
Double  8
Long  4
Long Long  8
Long Double  12
Unsigned long 4
Size_t 4
Bool*  4
Float*  4
Double*  4
Long*  4
Int 4
Double 8
Long Long 8
Float 4
Unsigned Long 4
Long Double 12
```

## 5. cmath

[cplusplus.com/reference/cmath/](https://cplusplus.com/reference/cmath/)

<a  href = "https://www.cainiaojc.com/cpp/cpp-library-function-cmath.html">Chinese tutorial</a>

```c++
#include <iostream>
#include <cmath>
#include <time.h>
using namespace std;

int main(int argc, char *argv[])
{
    cout << "abs(-19) = " << abs(-19) << endl;
    cout << "max(5, 4) = " << max(5, 4) << endl;
    cout << "min(5, 4) = " << min(5, 4) << endl;
    cout << "floor(10.45) = " << floor(10.5) << endl;
    cout << "round(10.45) = " << round(10.5) << endl;
    cout << "pow(2, 3) = " << pow(2, 3) << endl;
    cout << "sqrt(100) = " << sqrt(100) << endl;

    cout << endl;

    cout << "exp(1)" << exp(1) << endl;
    cout << "exp2(1)" << exp2(1) << endl;
    cout << "exp2(2)" << exp2(2) << endl;

    cout << "log(20)" << log(20) << endl;
    cout << "log2(8)" << log2(8) << endl;

    // 随机函数
    srand(time(NULL));
    for (size_t i = 0; i < 10; i++)
    {
        int secret = rand() % 10;
        cout << "secret : " << secret << endl;
    }
    return 0;
}
```

<strong style="color:red">result:</strong>

```c++
abs(-19) = 19
max(5, 4) = 5
min(5, 4) = 4
floor(10.45) = 10
round(10.45) = 11
pow(2, 3) = 8
sqrt(100) = 10

exp(1)2.71828
exp2(1)2
exp2(2)4
log(20)2.99573
log2(8)3
secret : 0
secret : 1
secret : 2
secret : 1
secret : 2
secret : 5
secret : 2
secret : 5
secret : 9
secret : 7
```

## 6. Lambda function

Lambda also known **anonymous** function.

```C++
#include <iostream>
using namespace std;

void f(int a,int b){
    cout <<"----f-----"<<endl;
        cout << "a :" << a << endl;
        cout << "b :" << b << endl;


}

int main(int argc,char *argv[]){
    auto func =[](){
        cout<<"xujq52"<<endl;

    };
    int a{10};
    auto func0 = [a]()
    {
        cout << "a : " << a << endl;
    };

    int b{20};

    auto func1 = [&b, a]()
    {
        cout <<"----func1-----"<<endl;
        cout << "a :" << a << endl;
        cout << "b :" << b << endl;
        b++;
    };
    //取值
    auto func2 = [=]()
    {
         cout <<"----func2-----"<<endl;
        cout << "a :" << a << endl;
        cout << "b :" << b << endl;
    };
    //取引用
    auto func3 = [&]()
    {
         cout <<"----func3-----"<<endl;
        cout << "a :" << a << endl;
        cout << "b :" << b << endl;
        a++;
        b++;
    };
    func();
    func0();
    func1();
    f(a,b);
    func2();
    func3();
    cout << a << endl;
    cout << b << endl;
    return 0;
}
```

<strong style="color:red">result:</strong>

```c++
abs(-19) = 19
max(5, 4) = 5
min(5, 4) = 4
floor(10.45) = 10
round(10.45) = 11
pow(2, 3) = 8
sqrt(100) = 10

exp(1)2.71828
exp2(1)2
exp2(2)4
log(20)2.99573
log2(8)3
secret : 0
secret : 1
secret : 2
secret : 1
secret : 2
secret : 5
secret : 2
secret : 5
secret : 9
secret : 7
```

## 7. Function pointer

```c++
#include <iostream>
#include <string>
using namespace std;

char encrypt(const char &param)
{
    return param - 13;
}

char decrypt(const char &param)
{
    return param + 13;
}

void change(string &stringItem, char (*callbackFunction)(const char &))
{
    for (size_t i = 0; i < stringItem.size(); i++)
    {
        stringItem[i] = callbackFunction(stringItem[i]);
    }
}

int main(int argc, char *argv[])
{
    string msg{"xujq52"};
    // encrypt char - 13
    change(msg, encrypt);
    cout << "encrypt: " << msg << endl;

    change(msg, decrypt);
    cout << "msg : " << msg << endl;
    // decrypt char + 13
    return 0;
}
```

In C++, function pointers and callbacks are powerful features that allow you to pass functions as arguments to other functions or store them in data structures. This can be particularly useful for implementing generic algorithms or for enabling dynamic behavior in your programs.

### 7.1 Function Pointers:

A function pointer in C++ is a variable that can store the address of a function. You can use function pointers to call functions indirectly. Here's a simple example:

```cpp
#include <iostream>

// Function with the same signature as the function we want to point to
void myFunction(int x) {
    std::cout << "Function called with argument: " << x << std::endl;
}

int main() {
    // Declare a function pointer
    void (*functionPtr)(int);

    // Assign the address of myFunction to the function pointer
    functionPtr = &myFunction;

    // Call the function through the function pointer
    (*functionPtr)(42);

    return 0;
}
```

In this example, `functionPtr` is a pointer to a function that takes an integer as an argument. It's then assigned the address of `myFunction`, and calling `(*functionPtr)(42)` invokes `myFunction` indirectly.

### 7.2 Callbacks:

A callback is a function that is passed as an argument to another function and is executed at a later time. Callbacks are often used for event handling or customization of behavior. Here's an example:

```cpp
#include <iostream>

// Callback function type
typedef void (*CallbackFunction)(int);

// Function that takes a callback as an argument
void performOperation(int x, CallbackFunction callback) {
    std::cout << "Performing operation with argument: " << x << std::endl;

    // Invoke the callback
    callback(x);
}

// Callback function
void myCallback(int x) {
    std::cout << "Callback called with argument: " << x << std::endl;
}

int main() {
    // Use performOperation with myCallback as the callback
    performOperation(42, &myCallback);

    return 0;
}
```

In this example, `performOperation` is a function that takes an integer and a callback function. It performs some operation and then invokes the callback. In `main()`, we use `performOperation` with `myCallback` as the callback function.

## 8. Rvaule(&&)

```c++
#include <iostream>
using namespace std;

// 右值
int add(int a, int b)
{
    return a + b;
}

int main(int argc, char *argv[])
{
    int a0{1};
    int a1{2};
    int a2{3};
    // 都是左值
    cout << &a0 << endl;
    cout << &a1 << endl;
    cout << &a2 << endl;

    int *p{&a0};
    cout << *p << endl;

    int x{0};
    x = (a1 + a2); // (a1+a2) 地址不能获取 copy
    // int *p = &(a1 + a2);
    int &&result1 = a0 + a1; // 不是值copy
    cout << result1 << endl;
    x = add(a1, a2); // copy
    int &&result2 = add(a1, a2);
    cout << result2 << endl;

    cout << "----- yz ------" << endl;
    return 0;
}
```

Here's a breakdown of the key concepts related to rvalue references:

1. **Lvalue and Rvalue:**
   - An lvalue is an expression that represents an object with a persistent identity (something with a name that you can take the address of).
   - An rvalue is an expression that represents a temporary or a value that does not have a persistent identity.

2. **Rvalue Reference (`&&`):**
   - An rvalue reference is declared using `&&` and is used to bind to rvalues.
   - Unlike lvalue references (`&`), which can bind only to lvalues, rvalue references can bind to both rvalues and lvalues (but typically, they are used with rvalues).

3. **Move Semantics:**
   - Move semantics allow the efficient transfer of resources from one object to another.
   - With move semantics, instead of making a copy of an object, resources owned by an rvalue can be "moved" to a new location, leaving the original object in a valid but unspecified state.

4. **`std::move`:**
   - The `std::move` function is used to cast an lvalue to an rvalue reference. This is often used to indicate that you are willing to "move" the resources from the given lvalue.
   - `std::move` is not mandatory for move semantics to work, but it serves as a signal to the compiler and other programmers that you intend to perform a move.

Here's a simple example demonstrating the use of rvalue references and move semantics:

```cpp
#include <iostream>
#include <utility> // for std::move

class MyString {
public:
    // Move constructor
    MyString(std::string&& s) : data(std::move(s)) {
        std::cout << "Move constructor called." << std::endl;
    }

private:
    std::string data;
};

int main() {
    std::string str = "Hello, World!";
    
    // Using std::move to cast lvalue to rvalue reference
    MyString myStr(std::move(str));

    // At this point, str might be in a valid but unspecified state.
    
    return 0;
}
```

In this example, `MyString` has a move constructor that takes an rvalue reference to a `std::string`. The `std::move` function is used to cast the lvalue `str` to an rvalue reference when constructing `myStr`. This allows the efficient transfer of the string's resources without unnecessary copying. After the move, `str` might be in a valid but unspecified state, and you've effectively "moved" the string's resources to `myStr`.

### 8.1 move constructor

The move constructor in C++ is a special type of constructor designed to transfer resources from a temporary object (an rvalue) to a new object. This concept is part of the C++11 standard, which introduced move semantics to optimize the performance of programs, especially when dealing with large data transfers or resource ownership.

**Syntax of Move Constructor**

The move constructor is similar to the copy constructor, but it takes an rvalue reference as its parameter:

```cpp
ClassName(ClassName &&other);
```

**How Move Constructor Works**

- **Transfers Resources**: Instead of making a deep copy of the object's resources (like in a deep copy), it transfers the resources from one object to another. This is more efficient as it avoids unnecessary copying.
- **Leaves the Source in a Valid State**: The source object, from which resources are moved, is left in a valid but unspecified state. This means it can still be destructed or assigned to without causing issues.

**Example of a Move Constructor**

```cpp
class Example {
public:
    int *data;

    // Constructor
    Example(int d) {
        data = new int(d); // Allocating memory
    }

    // Move constructor
    Example(Example &&other) : data(other.data) {
        other.data = nullptr; // Leaving the source object in a valid state
    }

    ~Example() {
        delete data; // Destructor to free memory
    }
};
```

**When is Move Constructor Called?**

Move constructors are invoked in several scenarios, such as:
1. **Returning large objects from functions by value.**
2. **Passing large objects by value to functions.**
3. **Initializing an object with a temporary (rvalue).**

**Benefits of Move Constructor**

1. **Performance Optimization**: It significantly optimizes performance for temporary and large objects, as it eliminates the need for deep copying.
2. **Efficient Resource Management**: It provides a clean way to transfer ownership of resources, such as memory and file handles, from temporary objects.
3. **Safety in Modern C++**: Ensures safe and efficient handling of resources in modern C++ design, aligning with move semantics.

**Best Practices**

- Implement move constructors for classes that manage resources like dynamic memory, file handles, or network connections.
- Ensure that moved-from objects are left in a valid state to prevent any undefined behavior.
- Implement the Rule of Five (copy constructor, move constructor, copy assignment operator, move assignment operator, and destructor) in classes that manage resources, especially if you already have a custom copy constructor or destructor.

## 9. this

```c++
#include <iostream>
using namespace std;

//this is a pointer
#define PI 3.141592653589793
class Circle{
    public:
    static int count;
    Circle(double radius){
        count++;
        this->radius = radius;
    }
    ~Circle(){
        count--;
    }
    double area(){
        return PI*radius*radius;
    }
    void print_object(){
        cout << "Object address: " << this << endl;
        cout << "radius: " << radius << endl;  
    }
    // 指针object->set_radius_point(radius)->print_radius_point();
    Circle *set_radius_point(double radius){
        cout <<"set point" << endl;
        this->radius = radius;
        return this;
    }
    Circle *get_radius_point(){
        cout <<"get point" << endl;
        return this;
    }
    // 引用object.set_radius_ref(radius).print_radius_ref();
    //*this中*是“解引用”标识符！
    Circle &set_radius_ref(double radius){
        cout <<"set ref" << endl;
        this->radius = radius;
        return *this;
    }
    Circle &get_radius_ref(){
        cout <<"get ref" << endl;
        return *this;
    }
    private:
    double radius{0};
};
// Initialize the static member outside the class
int Circle::count = 0;
int main(){
    //heap create
    cout << "heap create" << endl;
    auto *c1 = new Circle(1);
    c1->print_object();
    c1->get_radius_point()->set_radius_point(2)->get_radius_point();
    cout << "pointer to reference" << endl;
    c1->get_radius_ref().set_radius_ref(3).get_radius_ref();
    //stack create
    cout << "stack create" << endl;
    Circle c2(4);
    c2.print_object();
    c2.get_radius_ref().set_radius_ref(5).get_radius_ref();
    cout << "reference to pointer" << endl;
    c2.get_radius_point()->set_radius_point(6)->get_radius_point();
    //delete
    delete c1;
    c1 = nullptr;
    return 0;
}
```

<strong style="color:red">result:</strong>

```shell
heap create
Object address: 0xff1928
radius: 1
get point
set point
get point
pointer to reference
get ref
set ref
get ref
stack create
Object address: 0x61feb0
radius: 4
get ref
set ref
get ref
reference to pointer
get point
set point
get point
```

## 10. Getter&Setter

Certainly! In object-oriented programming, including C++, getters and setters are methods (member functions) that provide controlled access to the private members (variables) of a class. They are used to encapsulate the internal state of an object, promoting data encapsulation and abstraction.

1. **Getter (Accessor):**
   - **Purpose:** A getter is a method that retrieves the value of a private member variable.
   - **Naming Convention:** Typically, getter methods are named with the prefix `get` followed by the name of the variable they retrieve.
   - **Example:**
     ```cpp
     class MyClass {
     private:
         int myValue;
     
     public:
         int getValue() const {
             return myValue;
         }
     };
     ```
   - **Usage:**
     ```cpp
     MyClass obj;
     int value = obj.getValue();  // Accessing the private variable indirectly through the getter.
     ```

2. **Setter (Mutator):**
   - **Purpose:** A setter is a method that modifies the value of a private member variable.
   - **Naming Convention:** Setter methods are often named with the prefix `set` followed by the name of the variable they set.
   - **Example:**
     ```cpp
     class MyClass {
     private:
         int myValue;
     
     public:
         void setValue(int newValue) {
             myValue = newValue;
         }
     };
     ```
   - **Usage:**
     ```cpp
     MyClass obj;
     obj.setValue(42);  // Modifying the private variable indirectly through the setter.
     ```

3. **Combined Getter-Setter:**
   - It's common to have a single method that serves as both a getter and a setter by returning a reference to the private member variable. This allows both reading and writing of the variable.
   - **Example:**
     ```cpp
     class Cat {
     private:
         std::string name;
     
     public:
         const std::string& getName() const {
             return name;
         }
     
         void setName(const std::string& newName) {
             name = newName;
         }
     };
     ```
   - **Usage:**
     ```cpp
     Cat myCat;
     std::cout << myCat.getName() << std::endl;  // Using the getter.
     myCat.setName("Whiskers");                 // Using the setter.
     ```

Using getters and setters provides a way to control access to the internal state of a class, allowing for validation, manipulation, or additional behavior when reading or modifying the values. It also helps to maintain a clean and consistent interface for interacting with objects.

<strong style="color:purple">For ex ample：</strong>

```c++
//Cat.h
#ifndef CAT_H
#define CAT_H
#include <iostream>
#include <string>
class Cat
{
public:
    Cat(std::string name, int age);

    // 可变引用
    std::string &name()
    {
        return this->m_name;
    }
    // 不可变引用
    const std::string &name() const
    {
        return this->m_name;
    }
    int &age()
    {
        return this->m_age;
    }
    const int &age() const
    {
        return this->m_age;
    }
    // print
    void print_object() const;

private:
    std::string m_name;
    int m_age;
};

#endif
```

```c++
//Cat.cpp
#include "cat.h"
#include <string>

Cat::Cat(std::string name, int age)
{
    this->m_name = name;
    this->m_age = age;
}

void Cat::print_object() const
{
    std::cout << "Cat (" << this << ") : name : " << this->m_name << " age: " << this->m_age << std::endl;
}
```

```c++
//main.cpp
#include <iostream>
#include "cat.h"
using namespace std;

int main(int argc, char *argv[])
{
    Cat mut_cat("cat2", 4);
    mut_cat.name() = "mimi";
    mut_cat.age() += 1;
    mut_cat.print_object();

    const Cat cat("cat1", 2);
    cout << cat.name() << endl;
    // cat.name() = "mimi";error!!!!
    cat.print_object();
    return 0;
}
```

<p align="center"><em style="color:purple">const</em> refence : don't set! don't modify!!!</p>

## 11. mutable

```c++
#include <iostream>

class Example {
private:
    int regularVariable;   // Regular non-mutable variable
    mutable int mutableVariable;   // Mutable variable

public:
    Example(int regular, int mutableVar) : regularVariable(regular), mutableVariable(mutableVar) {}

    // Member function that does not modify any member variables
    void printRegular() const {
        //regularVariable++; error!!!!!
        std::cout << "Regular Variable: " << regularVariable << std::endl;
    }

    // Member function that can modify the mutable variable
    void modifyMutable() const {
        mutableVariable++;  // Okay, even in a const member function
        std::cout << "Mutable Variable (modified): " << mutableVariable << std::endl;
    }
};

int main() {
    Example example(42, 10);

    example.printRegular();   // Regular Variable: 42
    example.modifyMutable();  // Mutable Variable (modified): 11

    return 0;
}
```

The function like "` void modifyMutable() const`" is called as <strong style="color:green">const memeber function</strong>, where any content can't be modify!

## 12. explicit

### 12.1 implicit(System default)

Implicit conversion, also known as "type coercion" or "type conversion," refers to the automatic conversion of one data type to another by the compiler. This conversion is performed when an expression of one data type is used in a context where another data type is expected. Implicit conversions are generally done to ensure compatibility between different types in an expression or assignment.

Here are some common scenarios where implicit conversion occurs in C++:

1. **Promotion:**
   - Smaller integral types (like `char` or `short`) are automatically promoted to larger types (like `int` or `long`) when used in expressions.

    ```cpp
    short a = 10;
    int b = a; // Implicit conversion (promotion) from short to int
    ```

2. **Arithmetic Conversions:**
   - When performing arithmetic operations, the operands are subject to implicit conversion to a common type.

    ```cpp
    int a = 5;
    double b = 2.5;
    double result = a + b; // Implicit conversion of 'a' to double before addition
    ```

3. **Conversion between Built-in Types:**
   - Certain conversions between built-in types are allowed, such as between numeric types and boolean.

    ```cpp
    int a = 42;
    bool flag = a; // Implicit conversion from int to bool
    ```

4. **User-Defined Conversions:**
   - You can define your own conversion functions in classes. These are user-defined conversions.

    ```cpp
    class MyClass {
    public:
        operator int() const {
            return myData;
        }
   
    private:
        int myData;
    };
   
    MyClass obj;
    int convertedValue = obj; // Implicit conversion using user-defined conversion function
    ```

5. **Enum Conversions:**
   - Enums can be implicitly converted to integral types, and vice versa.

    ```cpp
    enum Color { Red, Green, Blue };
    int colorValue = Green; // Implicit conversion from enum to int
    ```

6. **Pointer Conversions:**
   - Implicit conversions can occur between pointers when converting between related types (e.g., derived to base class).

    ```cpp
    class Base {};
    class Derived : public Base {};
   
    Derived derivedObj;
    Base* basePtr = &derivedObj; // Implicit conversion from Derived* to Base*
    ```

It's important to note that while implicit conversions can be convenient, they can also lead to unexpected behavior if not used carefully. It's generally a good practice to be aware of implicit conversions in your code and, when necessary, use explicit type conversions to make the code more readable and to avoid unintended consequences.

### 12.2 explicit（Avoid default implicit）

```c++
//product.h
#ifndef PRODUCT_H
#define PRODUCT_H
#include <iostream>
#include <string>
class Product
{
public:
    Product() = default;
    Product(const std::string &name, const std::string &category, int years);
    Product(const std::string &name, const std::string &category);
    explicit Product(const std::string &name);
    ~Product();

    // setter
    void set_name(const std::string &name) { this->name = name; }
    void set_category(const std::string &category) { this->category = category; }
    void set_years(int years) { *(this->years) = years; }
    // getter
    const std::string &get_name() const { return this->name; }
    const std::string &get_category() const { return this->category; }
    int *get_years() const { return this->years; }

    void print_object()
    {
        std::cout << "Product : " << this
                  << " name: " << this->name
                  << " category: " << this->category
                  << ", years: " << *(this->years)
                  << ", years address: " << this->years << std::endl;
    }

private:
    std::string name{};
    std::string category{};
    int *years{};
};

#endif
```

```c++
//product.cpp
#include "product.h"
Product::Product(const std::string &name, const std::string &category, int years) : name(name), category(category), years(new int(years))
{
    std::cout << "three" << std::endl;
}
Product::Product(const std::string &name, const std::string &category) : Product(name, category, 0)
{
    std::cout << "two" << std::endl;
}
Product::Product(const std::string &name) : Product(name, "")
{
    std::cout << "one" << std::endl;
}

Product::~Product()
{
    std::cout << "delete" << std::endl;
    delete years;
}
```

```c++
//main.cpp
#include <iostream>
#include "product.h"
using namespace std;

bool compare(const Product &product1, const Product &product2)
{
    cout << *(product1.get_years()) << " : " << *(product2.get_years()) << endl;
    return (*(product1.get_years()) > *(product2.get_years())) ? true : false;
}

int main(int argc, char *argv[])
{
    Product p1("Box", "Toy", 2);
    Product p2("ff");
    std::string s1{"dd"};//If there is no explicit Product, you can just compare and pass in s1.
    cout << compare(p1, p2) << endl;
    return 0;
}
```

## 13. Copy constructor

In C++, understanding the concepts of copy constructors, shallow copy, and deep copy is crucial for managing object copying and memory management effectively.

**Copy Constructor**

A copy constructor is a special constructor used to create a new object as a copy of an existing object. Its typical signature looks like this:

```cpp
ClassName(const ClassName &other);
```

Here's a simple example:

```cpp
class Example {
public:
    int *data;

    Example(int d) {
        data = new int(d); // Allocating memory
    }

    // Copy constructor
    Example(const Example &other) {
        data = new int(*(other.data)); // Deep copy
    }

    ~Example() {
        delete data; // Destructor to free memory
    }
};

int main() {
    Example obj1(10);
    Example obj2 = obj1; // Copy constructor is called here
}
```

**Shallow Copy**

A shallow copy occurs when the copying process copies the values of an object's member variables as they are. If the member variable is a pointer, only the address it points to is copied, not the actual resource. This can lead to issues like double free errors and data inconsistencies.

Example of Shallow Copy:
```cpp
Example(const Example &other) {
    data = other.data; // Shallow copy
}
```

<strong style= "color:red">Shallow Copy is used copy address.</strong>

**Deep Copy**

A deep copy, on the other hand, involves copying all fields, and the objects pointed to by the fields are also copied. This is essential for managing dynamic memory and ensuring each object has its own copy of the resources.

Example of Deep Copy:
```cpp
Example(const Example &other) {
    data = new int(*(other.data)); // Deep copy
}
```

**Importance**

1. **Resource Management**: Proper handling of deep and shallow copies is vital in resource management, especially when dealing with dynamic memory allocation.
2. **Avoiding Bugs**: Incorrect handling can lead to bugs like memory leaks or double free errors.
3. **Control over Copying**: Copy constructors give you control over how objects of your class should be copied.

**Best Practices**

- Always define a copy constructor if your class deals with resources like dynamic memory or file handles.
- Decide between shallow and deep copy based on the needs of your application. For simple data, a shallow copy might suffice, but for dynamically allocated memory or resources, a deep copy is usually necessary.
- Implement the Rule of Three (copy constructor, copy assignment operator, and destructor) in classes that manage resources. 
