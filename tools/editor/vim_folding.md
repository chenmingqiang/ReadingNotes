# Vim folding 读书笔记

## 什么使folding

不会改变buffer中的文本，只是行的显示方式的改变

## 手动folding

光标出输入zfap

## 打开 folding

zo

zO

zr 打开folding， 不用移动到folding 地方

zR 

## 关闭folding

zc

zC

zm

zM

## 删除folding

zd
zD

## folding 的显示

This will show a small column on the left of the window to indicate folds.
A "+" is shown for a closed fold.  A "-" is shown at the start of each open
fold and "|" at following lines of the fold.

## 保存folding

:mkview

:loadview

一个文件最多可以存储10个view。

    :mkview 3
    :loadview 2

## folding 方法

1. 选中文本，然后zf
2. 设置folding方法 :set foldmethod=indent , :set foldlevel=3, :set foldmethod=marker


