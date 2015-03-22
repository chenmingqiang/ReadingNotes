# C++ 11中的新feature

# Lambda 表达式
lambda 表达式的通俗说法就是匿名函数。而匿名函数通常是短小且只用一次的函数。

    [capture](parameters)->return_type {body}

对于capture 有如下选择：
* []        Capture nothing (or, a scorched earth strategy?)
* [&]       Capture any referenced variable by reference
* [=]       Capture any referenced variable by making a copy
* [=, &foo] Capture any referenced variable by making a copy, but capture variable foo by reference
* [bar]     Capture bar by making a copy; do not copy anything else
* [this]    Capture the this pointer of the enclosing class

代码片段:
    // case 1
    [] { cout << "Hello, World" << endl; } ();  
   
    // case 2 
    char s[]="Hello World!";
    int Uppercase = 0; //modified by the lambda
    for_each(s, s+sizeof(s), [&] (char c) {
            if (isupper(c))
            Uppercase++;
            });
   
    // case 3 
    int i = 1024;
    auto func = [=] { printf("%d\n", i); };
    func();



## 自动类型推导 
自动类型推导有两个关键字auto, deltype. 
### auto
自动类型推导可以简化代码。

    auto x=0; //x has type int because 0 is int
    auto c='a'; //char
    auto d=0.5; //double
    auto national_debt=14400000000000LL;//long long

auto 最大的好处就是让代码简洁，尤其是那些模板类的声明，比如：STL中的容器的迭代子类型。
vector<int>::const_iterator ci = vi.begin(); 可以变成：auto ci = vi.begin();

关于 decltype 是一个操作符，其可以评估括号内表达式的类型，其规则如下：

如果表达式e是一个变量，那么就是这个变量的类型。
如果表达式e是一个函数，那么就是这个函数返回值的类型。
如果不符合1和2，如果e是左值，类型为T，那么decltype(e)是T&；如果是右值，则是T。
原文给出的示例如下，我们可以看到，这个让的确我们的定义变量省了很多事。
const vector<int> vi;
typedef decltype (vi.begin()) CIT;
CIT another_const_iterator;
还有一个适合的用法是用来typedef函数指针，也会省很多事。比如：

decltype(&myfunc) pfunc = 0;
 
typedef decltype(&A::func1) type;
auto 和 decltype 的差别和关系

    #include <vector>
     
    int main()
    {
        const std::vector<int> v(1);
        auto a = v[0];        // a 的类型是 int
        decltype(v[0]) b = 1; // b 的类型是 const int&, 因为函数的返回类型是
                              // std::vector<int>::operator[](size_type) const
        auto c = 0;           // c 的类型是 int
        auto d = c;           // d 的类型是 int
        decltype(c) e;        // e 的类型是 int, 因为 c 的类型是int
        decltype((c)) f = c;  // f 的类型是 int&, 因为 (c) 是左值
        decltype(0) g;        // g 的类型是 int, 因为 0 是右值
    }

如果auto 和 decltype 在一起使用会是什么样子？能看下面的示例，下面这个示例也是引入decltype的一个原因——让C++有能力写一个 “ forwarding function 模板”，

template< typename LHS, typename RHS>
  auto AddingFunc(const LHS &lhs, const RHS &rhs) -> decltype(lhs+rhs)
{return lhs + rhs;}

这个函数模板看起来相当费解，其用到了auto 和 decltype 来扩展了已有的模板技术的不足。怎么个不足呢？在上例中，我不知道AddingFunc会接收什么样类型的对象，这两个对象的 + 操作符返回的类型也不知道，老的模板函数无法定义AddingFunc返回值和这两个对象相加后的返回值匹配，所以，你可以使用上述的这种定义。

## 统一的初始化语法
C/C++的初始化的方法比较，C++ 11 用大括号统一了这些初始化的方法。
比如：POD的类型。
    int arr[4]={0,1,2,3};
    struct tm today={0};

关于POD相说两句，所谓POD就是Plain Old Data，当class/struct是极简的(trivial)、属于标准布局(standard-layout)，以及他的所有非静态（non-static）成员都是POD时，会被视为POD。如：

    struct A { int m; }; // POD
    struct B { ~B(); int m; }; // non-POD, compiler generated default ctor
    struct C { C() : m() {}; ~C(); int m; }; // non-POD, default-initialising m

POD的初始化有点怪，比如上例，new A; 和new A(); 是不一样的，对于其内部的m，前者没有被初始化，后者被初始化了（不同 的编译器行为不一样，VC++和GCC不一样）。而非POD的初始化，则都会被初始化。

从这点可以看出，C/C++的初始化问题很奇怪，所以，在C++ 2011版中就做了统一。原文作者给出了如下的示例：

    C c {0,0}; //C++11 only. 相当于: C c(0,0);
     
    int* a = new int[3] { 1, 2, 0 }; /C++11 only
     
    class X {
        int a[4];
        public:
            X() : a{1,2,3,4} {} //C++11, member array initializer
    };

容器的初始化：

    // C++11 container initializer
    vector<string> vs={ "first", "second", "third"};
    map singers =
    { {"Lady Gaga", "+1 (212) 555-7890"},
    {"Beyonce Knowles", "+1 (212) 555-0987"}};

还支持像Java一样的成员初始化：

    class C
    {
       int a=7; //C++11 only
       public:
          C();
    };

## Delete 和 Default 函数
我们知道C++的编译器在你没有定义某些成员函数的时候会给你的类自动生成这些函数，比如，构造函数，拷贝构造，析构函数，赋值函数。有些时候，我们不想要这些函数，比如，构造函数，因为我们想做实现单例模式。传统的做法是将其声明成private类型。

在新的C++中引入了两个指示符，delete意为告诉编译器不自动产生这个函数，default告诉编译器产生一个默认的。原文给出了下面两个例子：

    struct A
    {
        A()=default; //C++11
        virtual ~A()=default; //C++11
    };
    
再如delete
    struct NoCopy
    {
        NoCopy & operator =( const NoCopy & ) = delete;
        NoCopy ( const NoCopy & ) = delete;
    };
    NoCopy a;
    NoCopy b(a); //compilation error, copy ctor is deleted

这里，我想说一下，为什么我们需要default？我什么都不写不就是default吗？不全然是，比如构造函数，因为只要你定义了一个构造函数，编译器就不会给你生成一个默认的了。所以，为了要让默认的和自定义的共存，才引入这个参数，如下例所示：

    struct SomeType
    {
     SomeType() = default; // 使用编译器生成的默认构造函数
     SomeType(OtherType value);
    };

关于delete还有两个有用的地方是

1）让你的对象只能生成在栈内存上：
struct NonNewable {
    void *operator new(std::size_t) = delete;
};
2）阻止函数的其形参的类型调用：（若尝试以 double 的形参调用 f()，将会引发编译期错误， 编译器不会自动将 double 形参转型为 int 再调用f()，如果传入的参数是double，则会出现编译错误）

void f(int i);
void f(double) = delete;

## nullptr
C/C++的NULL宏是个被有很多潜在BUG的宏。因为有的库把其定义成整数0，有的定义成 (void*)0。在C的时代还好。但是在C++的时代，这就会引发很多问题。你可以上网看看。这是为什么需要 nullptr 的原因。 nullptr 是强类型的。

void f(int); //#1
void f(char *);//#2
//C++03
f(0); //二义性
//C++11
f(nullptr) //无二义性，调用f(char*)
所以在新版中请以 nullptr 初始化指针。

## 委托构造
在以前的C++中，构造函数之间不能互相调用，所以，我们在写这些相似的构造函数里，我们会把相同的代码放到一个私有的成员函数中。

class SomeType {
private:
  int number;
  string name;
  SomeType( int i, string&amp; s ) : number(i), name(s){}
public:
  SomeType( )               : SomeType( 0, "invalid" ){}
  SomeType( int i )         : SomeType( i, "guest" ){}
  SomeType( string&amp; s ) : SomeType( 1, s ){ PostInit(); }
};

但是，为了方便并不足让“委托构造”这个事出现，最主要的问题是，基类的构造不能直接成为派生类的构造，就算是基类的构造函数够了，派生类还要自己写自己的构造函数：

class BaseClass
{
public:
  BaseClass(int iValue);
};
 
class DerivedClass : public BaseClass
{
public:
  using BaseClass::BaseClass;
};
上例中，派生类手动继承基类的构造函数， 编译器可以使用基类的构造函数完成派生类的构造。 而将基类的构造函数带入派生类的动作 无法选择性地部分带入， 所以，要不就是继承基类全部的构造函数，要不就是一个都不继承(不手动带入)。 此外，若牵涉到多重继承，从多个基类继承而来的构造函数不可以有相同的函数签名(signature)。 而派生类的新加入的构造函数也不可以和继承而来的基类构造函数有相同的函数签名，因为这相当于重复声明。（所谓函数签名就是函数的参数类型和顺序不）

## 右值引用和move语义
在老版的C++中，临时性变量（称为右值”R-values”，位于赋值操作符之右）经常用作交换两个变量。比如下面的示例中的tmp变量。示例中的那个函数需要传递两个string的引用，但是在交换的过程中产生了对象的构造，内存的分配还有对象的拷贝构造等等动作，成本比较高。

    void naiveswap(string &amp;a, string &amp;b)
    {
     string temp = a;
     a=b;
     b=temp;
    }

C++ 11增加一个新的引用（reference）类型称作右值引用（R-value reference），标记为typename &&。他们能够以non-const值的方式传入，允许对象去改动他们。这项修正允许特定对象创造出move语义。

举例而言，上面那个例子中，string类中保存了一个动态内存分存的char*指针，如果一个string对象发生拷贝构造（如：函数返回），string类里的char*内存只能通过创建一个新的临时对象，并把函数内的对象的内存copy到这个新的对象中，然后销毁临时对象及其内存。这是原来C++性能上重点被批评的事。

能过右值引用，string的构造函数需要改成“move构造函数”，如下所示。这样一来，使得对某个stirng的右值引用可以单纯地从右值复制其内部C-style的指针到新的string，然后留下空的右值。这个操作不需要内存数组的复制，而且空的暂时对象的析构也不会释放内存。其更有效率。

class string
{
    string (string&&); //move constructor
    string&& operator=(string&&); //move assignment operator
};

The C++11 STL中广泛地使用了右值引用和move语议。因此，很多算法和容器的性能都被优化了。

## C++ 11 STL 标准库
C++ STL库在2003年经历了很大的整容手术 Library Technical Report 1 (TR1)。 TR1 中出现了很多新的容器类 (unordered_set, unordered_map, unordered_multiset, 和 unordered_multimap) 以及一些新的库支持诸如：正则表达式， tuples，函数对象包装，等等。 C++11 批准了 TR1 成为正式的C++标准，还有一些TR1 后新加的一些库，从而成为了新的C++ 11 STL标准库。这个库主要包含下面的功能：

## 线程库
这们就不多说了，以前的STL饱受线程安全的批评。现在好 了。C++ 11 支持线程类了。这将涉及两个部分：第一、设计一个可以使多个线程在一个进程中共存的内存模型；第二、为线程之间的交互提供支持。第二部分将由程序库提供支持。大家可以看看promises and futures，其用于对象的同步。 async() 函数模板用于发起并发任务，而 thread_local 为线程内的数据指定存储类型。更多的东西，可以查看 Anthony Williams的 Simpler Multithreading in C++0x.

## 新型智能指针
C++98 的知能指针是 auto_ptr， 在C++ 11中被废弃了。C++11  引入了两个指针类： shared_ptr 和 unique_ptr。 shared_ptr只是单纯的引用计数指针，unique_ptr 是用来取代auto_ptr。 unique_ptr 提供 auto_ptr 大部份特性，唯一的例外是 auto_ptr 的不安全、隐性的左值搬移。不像 auto_ptr，unique_ptr 可以存放在 C++0x 提出的那些能察觉搬移动作的容器之中。

为什么要这么干？大家可以看看《More Effective C++》中对 auto_ptr的讨论。

## 新的算法
定义了一些新的算法： all_of(), any_of() 和 none_of()。

    include <algorithm>
    //C++11 code
    //are all of the elements positive?
    all_of(first, first+n, ispositive()); //false
    //is there at least one positive element?
    any_of(first, first+n, ispositive());//true
    // are none of the elements positive?
    none_of(first, first+n, ispositive()); //false

使用新的copy_n()算法，你可以很方便地拷贝数组。

    include <algorithm>
    int source[5]={0,12,34,50,80};
    int target[5];
    //copy 5 elements from source to target
    copy_n(source,5,target);

使用 iota() 可以用来创建递增的数列。如下例所示：

    include <numeric>
    int a[5]={0};
    char c[3]={0};
    iota(a, a+5, 10); //changes a to {10,11,12,13,14}
    iota(c, c+3, 'a'); //{'a','b','c'}

总之，看下来，C++11 还是很学院派，很多实用的东西还是没有，比如： XML，sockets，reflection，当然还有垃圾回收。看来要等到C++ 20了。呵呵。不过C++ 11在性能上还是很快。参看 Google’s benchmark tests。原文还引用Stroustrup 的观点：C++11 是一门新的语言——一个更好的 C++。
