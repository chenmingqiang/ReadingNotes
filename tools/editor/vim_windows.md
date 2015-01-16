# 关于vim window的读书笔记

## 关键概念
### Window 
窗口是buffer的一个viewport

### Buffer
buffer 是一个load进内存的文件

### screen or tab page
page 是一些windows 的集合

### buffer的状态

    state		displayed	loaded		":buffers"  ~
    		    in window  	shows	    ~
    active		  yes		 yes		  'a'
    hidden		  no		 yes		  'h'
    inactive	  no		 no		  ' '

### start vim with window

vim -o file1 file2 file3  

vim -O file1 file2 file3

-ON : 如果N大于文件的数量，多余的窗口会是empty buffer， 小于，则有些文件没有打开

o :  水平window

O :  垂直window

### 用命令打开窗口

:vs[plit]

:sp[lit]

CTRL-W n : 创建一个空的window，以及一个空的文件，等价于 :new


### 关闭window

1. CTRL-W q						*CTRL-W_q*
2. :q[uit] 退出当前window,如果是最后一个(不计算help window），退出vim. 
3. :q[uit]! buffer 中的内容会丢失	
4. CTRL-W c					
5. :clo[se][!] 关闭当前窗口	

### 移动window

CTRL-W <Down>					

CTRL-W CTRL-J					*CTRL-W_CTRL-J* *CTRL-W_j*

CTRL-W j	Move cursor to Nth window below current one.  Uses the cursor position to select between alternatives.

CTRL-W <Up>					*CTRL-W_<Up>*

CTRL-W CTRL-K					*CTRL-W_CTRL-K* *CTRL-W_k*

CTRL-W k	Move cursor to Nth window above current one.  Uses the cursor position to select between alternatives.

CTRL-W <Left>					*CTRL-W_<Left>*

CTRL-W CTRL-H					*CTRL-W_CTRL-H*

CTRL-W <BS>					*CTRL-W_<BS>* *CTRL-W_h*

CTRL-W h	Move cursor to Nth window left of current one.  Uses the cursor position to select between alternatives.

CTRL-W <Right>					*CTRL-W_<Right>*

CTRL-W CTRL-L					*CTRL-W_CTRL-L* *CTRL-W_l*

CTRL-W l	Move cursor to Nth window right of current one.  Uses the cursor position to select between alternatives.

CTRL-W w					*CTRL-W_w* *CTRL-W_CTRL-W*
CTRL-W CTRL-W	Without count: move cursor to window below/right of the

CTRL-W W	Without count: move cursor to window above/left of current one.  If there is no window above or left, go to bottom-right window.  With count: go to Nth window, like with CTRL-W w.

CTRL-W t					*CTRL-W_t* *CTRL-W_CTRL-T*

CTRL-W CTRL-T	Move cursor to top-left window.

CTRL-W b					*CTRL-W_b* *CTRL-W_CTRL-B*

CTRL-W CTRL-B	Move cursor to bottom-right window.

CTRL-W p					*CTRL-W_p* *CTRL-W_CTRL-P*

CTRL-W CTRL-P	Go to previous (last accessed) window.

CTRL-W P	Go to preview window.  When there is no preview window this is an error.

### 改变window的大小

CTRL-W =	Make all windows (almost) equally high and wide, but use

CTRL-W -	Decrease current window height by N (default 1). 

CTRL-W +	Increase current window height by N (default 1).

CTRL-W _	Set current window height to N (default: highest possible).

CTRL-W <	Decrease current window width by N (default 1).

CTRL-W >	Increase current window width by N (default 1).

CTRL-W |	Set current window width to N (default: widest possible).

### buffers

#### show buffers command

:buffers[!]

:ls[!]

:files[!]

examples : 

    1 #h  "/test/text"		line 1 ~
    2u    "asdf"			line 0 ~
    3 %a+ "version.c"		line 1 ~

    Indicators (chars in the same column are mutually exclusive):

        u	an unlisted buffer (only displayed when [!] is used)
        |unlisted-buffer|
        %	the buffer in the current window
        #	the alternate buffer for ":e #" and CTRL-^
        a	an active buffer: it is loaded and visible
        h	a hidden buffer: It is loaded, but currently not
        displayed in a window |hidden-buffer|
        -	a buffer with 'modifiable' off
        =	a readonly buffer
        +	a modified buffer
        x   a buffer with read errors

