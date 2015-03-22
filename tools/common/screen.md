# Screen 常用命令及配置

## 创建一个screen window

screen

screen -S foo [推荐做法]

## screen 帮助文档

ctrl + a + ?

       Command key:  ^A   Literal ^A:  a
    
    break       ^B b       displays    *          help        ?          lockscreen  ^X x       number      N          quit        \          screen      ^C c       title       A          writebuf    >
    clear       C          dumptermcap .          history     { }        log         H          only        Q          readbuf     <          select      '          vbell       ^G         xoff        ^S s
    colon       :          fit         F          info        i          login       L          other       ^A         redisplay   ^L l       silence     _          version     v          xon         ^Q q
    copy        ^[ [       flow        ^F f       kill        K k        meta        a          pow_break   B          remove      X          split       S          width       W
    detach      ^D d       focus       ^I         lastmsg     ^M m       monitor     M          pow_detach  D          removebuf   =          suspend     ^Z z       windows     ^W w
    digraph     ^V         hardcopy    h          license     ,          next        ^@ ^N sp n prev        ^H ^P p ^? reset       Z          time        ^T t       wrap        ^R r
    
    ^]  paste .
    "   windowlist -b
    -   select -
    0   select 0
    1   select 1
    2   select 2
    3   select 3
    4   select 4
    5   select 5
    6   select 6
    7   select 7
    8   select 8
    9   select 9
    I   login on
    O   login off
    ]   paste .

## 创建一个nested screen window

ctrl + a  + c

## detached 一个screen

ctrl + a + d

## kill 一个screen session

ctrl + a + k

## 多个screen window 之间切换

ctrl + a + p
ctrl + a + n
ctrl + a + [0-9]
ctrl + a , ctrl + a
ctrl + a + " (list 所有的screen window)

## attach 一个screen window

ctrl + a + r

## 给screen window 添加title

ctrl + a + A

## 
