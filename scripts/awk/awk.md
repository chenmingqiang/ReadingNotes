# Reading notes for "Sed & Awk 101 hacks"

Awk也是一个文本处理工具。对于记录格式的文件(每一行用某种分隔符分开的多个记录）尤为擅长。AWK最初是由A. Aho, B. W.
Kernighan and P. Weinberger.这也是AWK的名字来源。

## AWK 历史
AWK 由三个变种：
1. 原始的AWK
2. NAWK（new AWK)
3. GAWK (GNU AWK) 兼容AWK和NAWK

## AWK 基本语法

    awk -Fs '/pattern/ {action}' input-file
    awk -Fs '{action}' intput-file

1. -F 指定分隔符(field delimiter), 如果不指定，默认为空格
2. /pattern/ 是可选的

例子：
    awk -F: '{print $1}' /etc/passwd

上面的例子会输出所有的用户名

和Sed一样，Awk 也可以以文件的方式执行
**注意** 必须使用单引号.

## AWK program 结构
BEGIN, body, END

1. BEGIN block

BEGIN { awk-commands }

BEGIN block 只会执行一次,在body block 执行所有行的时候开始执行,即使是多个输入文件，也只执行一次。

* 打印头部以及初始化变量
* 在begin块中可以有一个或多个awk命令
* BEGIN必须大写
* BEGIN块是可选的

2. body block

/pattern/ {action}

* 模式是可选的
* 只对匹配的行执行命令

3. END block

END { awk-commands }
END 块和BEGIN块一样只会执行一次,在body block执行完所有行后开始执行,即使是多个输入文件，也只执行一次。


* 打印尾部以及清理活动
* 在end块中可以有一个或多个awk命令
* END必须大写
* END块是可选的

例子：

    awk 'BEGIN { FS=":";print "---header---" } \
    /mail/ {print $1} \
    END { print "---footer---"}' /etc/passwd

例子：

    awk -F: 'BEGIN { print "UID"} { print $3 }' /etc/passwd
    awk 'BEGIN { print "Hello World!" }'
    awk -F: '{ print $1 }' /etc/passwd
    awk 'BEGIN { FS=":";print "---header---" } /mail/ {print $1} END { print "---footer---"}' /etc/passwd
    awk '{print}' employee.txt 
    awk '{print $0}' employee.txt
    awk -F ',' '{print $2}' employee.txt
    awk -F "," '{print $2}' employee.txt
    awk -F, '{print $2}' employee.txt
    awk -F ',' 'BEGIN { print "-------------\nName\tTitle\n-------------"} { print $2,"\t",$3;} END { print "-------------"; }' employee.txt

    awk 'BEGIN { print "test1" "test2" }'
    test1test2
    awk 'BEGIN { print "test1","test2" }'
    test1 test2

    awk 'BEGIN { FS="\n"; RS="-\n"; OFS=":" } {print $2, $3}' employee-change-fs-ofs.txt
    awk 'BEGIN { FS=","; ORS="\n---\n" } {print $2, $3}' employee.txt

    awk 'NR % 2 == 0' items.txt

1. $0表示整个记录
2. FS=":" 等价于 -F ':', -F:, -F ":"

## 内建变量

1. 输入分隔符FS, 可以指定多个字符例如, FS="[,:%]"
2. 输出分隔符OFS,当print 后面接多个变量时。每个变量中间默认用空格隔开. 如果想用其他符号，可以显示指定，也可以应OFS变量
3. 记录分隔符RS,一行可以有多个记录。因此，可以指定记录分隔符，然后在根据域分隔符划分
4. 输出记录分隔符ORS
5. 记录数NR,当用在body block中时，表示行号.用在end block中时，表示总的记录数.
6. 字段数NF,表示当前记录中的field个数
6. FILENAME,当前文件名。当输入来自管道时，FILENAME 为 "-"
7. FNR，记录在文件中的行号。当输入为多个文件时，行号从1开始

## 变量

    $cat total-company-salary.awk
    BEGIN {
        FS=",";
        total=0;
    }
    {
        print $2 "'s salary is: " $4;
        total=total+$4
    }
    END {
        print "---\nTotal company salary = $"total;
    }

一元操作符-,+,++,--,这些含义和C语言中的这些一元操作符含义一样.

## 条件匹配

如果awk不指定命令的话，就输出匹配条件的语句。

1. 比较操作符==, >, <, >=, <=, !=.
2. 条件操作符&&, ||
3. 匹配操作符~, !~ 


## 条件语句和循环语句

### 条件语句

    if (conditional-expression)
        action

    if (conditional-expression)
    {
        action1;
        action2;
    }

    if (conditional-expression)
        action1
    else
        action2

    conditional-expression ? action1 : action2 ;

### 循环语句

    while(condition)
        actions    

    do
        action
    while(condition)

    for(initialization;condition;increment/decrement)
        actions

### break, continue and exit

这些含义和C语言中的类似

## 关联数组
awk 中的数组是关联数组。语法如下:

    arrayname[string]=value

在awk中，index总是string，当你传入数字的时候，也会转成string.下面的语句是等价的。 

    item[101]="HD Camcorder"
    item["101"]="HD Camcorder"

在awk中，如果引用一个不存在的index，会创建这个index，然后赋值为null。可以通过使用前检查避免这个

    if (index in arrayname) 


例子：

    $ cat array-assign.awk
    BEGIN {
        item[101]="HD Camcorder";
        item[102]="Refrigerator";
        item[103]="MP3 Player";
        item[104]="Tennis Racket";
        item[105]="Laser Printer";
        item[1001]="Tennis Ball";
        item[55]="Laptop";
        item["na"]="Not Available";
        print item["101"];
        print item[102];
        print item["103"];
        print item[104];
        print item["105"];
        print item[1001];
        print item[55];
        print item["na"];
        print item["nonexist"];
    }
    $ awk -f array-assign.awk
    HD Camcorder
    Refrigerator
    MP3 Player
    Tennis Racket
    Laser Printer
    Tennis Ball
    Laptop
    Not Available


### 数组遍历

遍历数组可可以使用如下方法:

    for (var in arrayname) 
        action

var表示数组中的index。

### 删除数组元素和数组

    delete arrayname[index];
    delete array; # [GAWK]

### 多维数组

例子：

    $ cat array-multi2.awk
    BEGIN {
    item[1,1]=10;
    item[1,2]=20;
    item[2,1]=30;
    item[2,2]=40;
    for (x in item)
    print item[x];
    }
    $ awk -f array-multi2.awk
    30
    40
    10
    20
   
上面中，纬度之间有\034这个非打印字符分隔开来。我们可以指定一个自己的分隔符. 类似前面的FS,OFS等，使用变量SUBSEP可以指定.


### 数组排序
语法如下：

    asort(arrayname)

1. 返回值为数组中元素的个数
2. 排序后，index变为1到n（假设有n个元素）


类似的对index排序的有asorti函数


## 其他awk命令

### printf
printf 函数，类似C语言中的printf,但是不会使用OFS,ORS

* s String
* c Single Character
* d Decimal
* e Exponential Floating point
* f Fixed Floating point
* g Uses either e or f depending on which is
* smaller for the given input
* o Octal
* x Hexadecimal
* % Prints the percentage symbol

### 算术运算
1. int(n) 取整数部分
2. log(n) 自然对数
3. sqrt(n) n^(1/2)
4. exp(n) e^n
5. sin(n)
6. cos(n)
7. atan(m, n)
8. rand() 产生0到1之间的随机数

### 字符串函数

1. index
2. length
3. split
4. substr
5. sub
6. Gsub
7. match
8. ARGC, ARGV, ARGIND
* ARGC， 参数个数
* ARGV， 参数数组
* ARGIND 参数索引

例子：

    $ cat arguments.awk
    BEGIN {
    print "ARGC=",ARGC
    for (i = 0; i < ARGC; i++)
    print ARGV[i]
    }
    $ awk -f arguments.awk arg1 arg2 arg3 arg4 arg5
    ARGC= 6
    awk
    arg1
    arg2
    arg3
    arg4
    arg5

### awk profiler, pgawk

pgawk可以显示每条awk语句执行的次数，用法:

    $ pgawk --profile=myprofiler.out -f profiler.awk items.txt

### 位运算

### 系统函数

    $ awk 'BEGIN { system("pwd") }'
    /home/ramesh
    $ awk 'BEGIN { system("date") }'
    Sat Mar 5 09:19:47 PST 2011

### 时间戳函数(GAWK)

    $awk 'BEGIN { print systime(); }'


    $awk 'BEGIN { print systime(); }'

### 读取行(getline)


例子(从外部文件读取行)

    $ awk -F"," '{print $0; getline tmp < "items-sold.txt"; print tmp;}' items.txt

例子(执行外部命令然后获取结果) ：

    BEGIN {
        FS=",";
        "date" | getline # default storing to $0
        close("date")
        print "Timestamp:" $0
    }

    BEGIN {
        FS=",";
        "date" | getline timestamp
        close("date")
        print "Timestamp:" timestamp
    }
