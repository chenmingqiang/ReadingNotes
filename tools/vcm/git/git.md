# git 读书笔记

## git 简介
git 是一个分布式源代码版本控制系统。相对于其他版本控制系统来说，有两个比较重要的特点： 1.多种开发流程；2.简便的branch功能。

## 常用git 命令
0. git config
工欲善其事，必先利其器。在使用git前，我们可以先配置git，提高效率。git 配置参数数分为三个级别。 系统级（对所有用户/etc/gitconfig)，全局级(~/.gitconfig)，仓库级(.git/config)，优先级从低到高。除了一些常用的配置以外，配置alias 能够提高效率。

1. git status
可以用来check在那个branch，以及check文件的状态，比如untracted, modified, staged等等。

2. git add
可以将修改的文件到从working tree 到stage(indexing)。

3. git diff
主要用来显示不同级别的改变。比如，working directory 和stage area的改变。stage 和 local repository 的改变，不同branch之间的改变，不同commit之间的改变等等。

4. git commit
将stage area的东西放入到local repository

5. git rm
从working tree 或者index中删除文件。支持glob匹配。

6. git mv
移动文件，也就是重命名。

7. git log
查看commit 历史.

8. git commit --amend
这个可以将当前的commit和上一个commit 合并成一个commit

9. git reset
unstage 一个文件: get reset HEAD filename.

10. git checkout -- fiename
撤销一个修改的文件

11. git remote
这个命令可以显示remote repository，以及添加，删除，重命名remote repository。常用命令如下:

    git remote -v
   git remote -v
    git remote add upstream ....
    git remote rm  upstream
    git remote show origin
    git remote rename origin upstream


12. git fetch
可以fetch remote的branch

13. git push
可以推送当前的branch 到remote 的branch。 git push origin master

14. git tag
tag commit. 因此你可以给任何commit 打tag。如果没有commit， 那么就是指最近的一次commit. 使某个snapshot 具有可读的tag label。你必须主动推送tag 到remote server。
 git push origin tagname 后者git push origin --tags 都可以推送tag到remote server.

15. git merge
合并两个branch

16. git pull
git pull 等价于git fetch + git merge

17. git rebase
don't rebase 已经发布到public server 的commit.


## 小技巧

### 自动完成功能
从git source code 中找出文件git-completion.bash，加入bashrc中。

### 别名
可以使用git config 来进行命名别名 
git config --global alias.co checkout



## reference
[1] https://www.atlassian.com/git/tutorials/merging-vs-rebasing/conceptual-overview
[2] progit
