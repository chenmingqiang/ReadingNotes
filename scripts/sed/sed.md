# "sed & awk 101 hacks" 读书笔记 

## sed执行方式
sed有命令行和文件两种执行方式
命令行方式   : 

    sed [options] {sed commands} {input-file}
    sed [options] -e {sed-command-1} -e {sed-command-2} {input-file}
    sed [options] '{ sed-command-1 sed-command-2 }' {input-file}

例子：

    sed -n 'p' /etc/passwd
    sed -n -e '/^root/ p' -e '/^nobody/ p' /etc/passwd    
    sed -n '{ 
        /^root/ p
        /^nobody/ p
    }' /etc/passwd

文件执行方式 :
    
   sed [options] -f {sed-script-file} {input-file}
   sed -n -f test-script.sed /etc/passwd

## sed 执行流程

<img src="./sed-flow.png">
   
## 打印
打印的时候一般要指定－n选项来抑制pattern space的标准输出

### 指定行范围
1. sed 'p' employee.txt         # 每行打印两次
2. sed -n 'p' employee.txt      # 每行打印一次
3. sed -n '2 p' employee.txt    # 打印第2行
4. sed -n '2,4 p' employee.txt  # 打印第2到4行
5. sed -n '2,$ p' employee.txt  # 打印第2行到文件结尾
6. sed -n '2+4 p' employee.txt  # 打印第2行到第5行
7. sed -n '1~2 p' employee.txt  # 打印奇数行

### 模式匹配
1. sed -n '/Jane/ p' employee.txt       # 匹配Jane的行
2. sed -n '/Jane/,$ p' employee.txt     # 匹配Jane到文件结束
3. sed -n '/Jane/,4 p' employee.txt     # 匹配Jane到第4行（如果前面四行没有匹配上，就值打印后面匹配上的）
4. sed -n '/Jane/,/Tim/ p' employee.txt # 匹配Jane以及Tim之间的文本
5. sed -n '/Jane/,+2 p' employee.txt    # 匹配Jane的行以及接下来的两行

## 删除
删除和打印类似，有两个比较有用的删除命令
sed '/^$/ d'  # 删除空行
sed '/^#/ d'  # 删除注释(假设注释以#开头)

## 输出
输出指定范围的行到指定的文件中

1. sed 'w output.txt' employee.txt        # 输出到output.txt
2. sed -n '2 w output.txt' employee.txt   # 输出第2行到output.txt
3. sed -n '2,4 w output.txt' employee.txt # 输出第2行到第4行到output.txt
4. sed -n '2,$ w output.txt' employee.txt # 输出第2行到第4行到output.txt

## 替换
替换是sed最强大的功能。替换命令的格式如下：

    sed '[address-range|pattern-range] s/originalstring/replacement-string/[substitute-flags]' inputfile

1. sed 's/Manager/Director/' employee.txt   # 替换所有的Manager为Director
2. sed '/Sale/s/Manager/Director/' employee.txt #替换匹配Sale的行中的Manager为Director


### 替换选项flag 

1. g，替换行中的所有出现模式
2. 数字n，替换第n此出现
3. p,打印替换成功的行，一般和-n选项一起使用
4. w,输出替换成功的行，一般和-n选项一起使用
5. i,忽略大小写
6. e,执行

例子：

    $cat files.txt
    /etc/passwd
    /etc/group
    files.txt的每行前面添加"ls -l"
    $sed 's/^/ls -l /' files.txt
    ls -l /etc/passwd
    ls -l /etc/group
    $sed 's/^/ls -l /e' files.txt
    -rw-r--r-- 1 root root 1547 Oct 27 08:11 /etc/passwd
    -rw-r--r-- 1 root root 651 Oct 27 08:11 /etc/group 
   
7. 上面一些flag可以一起使用

例子：

    $ sed -n 's/Manager/Director/gipw output.txt' employee.txt 

## sed 替换分隔符
在下面这个例子中: $ sed 's/\/usr\/local\/bin/\/usr\/bin/' path.txt,如果分隔符为/，那么需要转义。sed支持使用其他任意字符分隔符。一般推荐使用| or ^ or @ or !.因此上面的例子可以写为:

    $sed 's|/usr/local/bin/|/usr/bin/|' path.txt
    $sed 's^/usr/local/bin/^/usr/bin/^' path.txt
    $sed 's!/usr/local/bin/!/usr/bin/!' path.txt
    $sed 's@/usr/local/bin/@/usr/bin/@' path.txt

## 多个替换命令会对同一行起作用

## 
