# BASH

## 运行脚本
有很多中方法
* 在脚本的第一行加上#!/bin/bash, 然后保证脚本具有可读以及执行权限。添加可读以及执行权限的方法

	chmod 555 scriptname  # 每个人都有可读和执行权限
	chmod +rx scriptname  # 每个人都有可读和执行权限
	chmod u+rx scriptname # 只有用户有可读和执行权限

* 使用bash scriptname的方式执行

## 变量

## 特殊变量

| 变量名 |       含义       | 变量名 |       含义       |
| ------ |------------------| ------ |------------------|
| $?     | 上一个命令的结构 | $#     | 命令行的参数个数 |
| $1     | 第一个命令行参数 | $!     | 上一个后台进程PID|
| $$     | 脚本本省的PID    | $@     | 所有的参数       |
| $*     | 所有的参数       | $_     | 上一个命令的最后一个参数 |
| $?     | 上一个命令的结构 | $#     | 上一个命令的结构 |

## 算术运算扩展

再bash中有几种算术运算扩展，分别是使用反引号号`(和expr一起使用）,双括号，以及let

例子1:

	sum=`expr 3 + 5`
    echo $sum      # 8 
    multiply=`expr 3 \* 5` 
    echo $multiply # 15

**注意:乘法需要转义**

例子2:
    
	sum=$((3+5))
	echo $sum      # 8
    a=3
	sum=$((a+5))
	echo $sum      # 8
	sum=$(($a+5))
	echo $sum      # 8

**注意:在双括号中，解引用符$是可选的**

例子3:

	let sum=3+5
	y=1
	let y=y+1
	let y++
	let y=$y+1
	let "y = y + 3"

**注意:如果没有双引号时，操作符前后不能有空格,解引用符是可选的**

## 测试
bash 中有多种方法进行测试，包括test命令，双方括号、圆括号操作符以及if,then语句。在linux/unix 系统中，退出代码为0一般表示成功。

* [命令是test命令的同义词，在某些系统上甚至是完全相同的。此命令将起参数认为是比较表达式或者文件测试。0为true，1为false。

* [[是一个关键字，用来进行一些比较语义的测试

* ((和let构造也会产生exit code，根据计算结果是否为0来确定。如果计算结果为0，则返回1（false）,否则返回0（true）

* if/then,对于if测试，任意整数，以及任意字符串为true; NULL，未定义变量是false. if test 中可以跟任何语句，不仅仅时方括号的比较等。if test condition 等价于 if [ condition ].

例子1


例子2


例子3


例子4

	if cmp /bin/\[ /bin/test &> /dev/null
	then  
		echo "[ is the same as test command"
	else 
		echo "[ is not the same as test command"
	fi

	word=Linux
	letter_sequence=inu
	if echo "$word" | grep -q "$letter_sequence"
	then
	echo "$letter_sequence found in $word"
	else
	echo "$letter_sequence not found in $word"
	fi

	if [ 1 ]
	then
		echo "1 is true"
	else	
		echo "1 is false"
	fi

	# if else 语句
	if [ condition-true ]
	then
		command 1
		command 2
		...
	else 
		command 3
		command 4
		...
	fi

	# if elif else 语句
	if [ condition1 ]
	then
		command1
		command2
		command3
	elif [ condition2 ]
	then
		command4
		command5
	else
		default-command
	fi

**注意:在[后必须有空格和]前必须有空格。**

通过man test，我们可以知道那些测试可以用[]符号来进行测试。主要分为几类

* 文件
  * -b file       True if file exists and is a block special file.
  * -c file       True if file exists and is a character special file.
  * -d file       True if file exists and is a directory.
  * -e file       True if file exists (regardless of type).
  * -f file       True if file exists and is a regular file.
  * -g file       True if file exists and its set group ID flag is set.
  * -h file       True if file exists and is a symbolic link.  This operator is retained for compatibility with pre-
                  vious versions of this program. Do not rely on its existence; use -L instead.
  * -k file       True if file exists and its sticky bit is set.
  * -n string     True if the length of string is nonzero.
  * -p file       True if file is a named pipe (FIFO).
  * -r file       True if file exists and is readable.
  * -s file       True if file exists and has a size greater than zero.
  * -t fd         True if the file whose file descriptor number is file_descriptor is open and is associated with a
                  terminal.
  * -u file       True if file exists and its set user ID flag is set.
  * -w file       True if file exists and is writable.  True indicates only that the write flag is on.  The file is
                  not writable on a read-only file system even if this test indicates true.
  * -x file       True if file exists and is executable.  True indicates only that the execute flag is on.  If file
                  is a directory, true indicates that file can be searched.
  * -L file       True if file exists and is a symbolic link.
  * -O file       True if file exists and its owner matches the effective user id of this process.
  * -G file       True if file exists and its group matches the effective group id of this process.
  * -S file       True if file exists and is a socket.
  * file1 -nt file2 True if file1 exists and is newer than file2.
  * file1 -ef file2 True if file1 and file2 exist and refer to the same file.

* 字符串
  * -z string     True if the length of string is zero.
  * string        True if string is not the null string.
  * s1 = s2       True if the strings s1 and s2 are identical.
  * s1 != s2      True if the strings s1 and s2 are not identical.
  * s1 < s2       True if string s1 comes before s2 based on the ASCII value of their characters.
  * s1 > s2       True if string s1 comes after s2 based on the ASCII value of their characters.

* 复合测试
  * ! expression  	           True if expression is false.
  * expression1 -a expression2 True if both expression1 and expression2 are true.
  * expression1 -o expression2 True if either expression1 or expression2 are true.
  * (expression)               True if expression is true.

-a 操作符比 -o 优先级高。

* 整数比较
  * n1 -eq n2  True if the integers n1 and n2 are algebraically equal.
  * n1 -ne n2  True if the integers n1 and n2 are not algebraically equal.
  * n1 -gt n2  True if the integer n1 is algebraically greater than the integer n2.
  * n1 -ge n2  True if the integer n1 is algebraically greater than or equal to the integer n2.
  * n1 -lt n2  True if the integer n1 is algebraically less than the integer n2.
  * n1 -le n2  True if the integer n1 is algebraically less than or equal to the integer n2.

## 字符串

## 循环和分支

### for 循环

	for arg in [list]
	do
	command(s)...
	done

### while 循环

	while [ condition ]
	do
	command(s)...
	done

### until 循环

	until [ condition-is-true ]
	do
	command(s)...
	done

注意: continue 和 break的语义和C语言中一样;

### case 分支

	case "$variable" in
	"$condition1" )
	command...
	;;
	"$condition2" )
	command...
	;;
	esac

### select 分支
select 分支可以用来提供目录和用户进行交互选择。select缺省使用$PS3 prompt,这也可能会改变。 

	select variable [in list]
	do
	command...
	break
	done

例子：

	#!/bin/bash
	PS3='Choose your favorite vegetable: ' # Sets the prompt string.
	# Otherwise it defaults to #? .
	echo
	select vegetable in "beans" "carrots" "potatoes" "onions" "rutabagas"
	do
		echo
		echo "Your favorite veggie is $vegetable."
		echo "Yuck!"
		echo
		break # What happens if there is no 'break' here?
	done
	exit
