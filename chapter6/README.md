# Chapter 6

这一章的主要内容是终端控制和信号。

### `rotate`

- rotate.c
  - 按照字母表的顺序，将输入按照“往后移一位”的规则进行输入；
  - 执行 `stty -echo -icanon` 命令会有一个更好的体验，能够让输入不回显，而且不需要等到按回车之后再响应。

### `play_again`

- play_again:
  - play_again0.c：最简单的 play_again 代码（也是最简陋的）；
  - play_again1.c：不需要输入回车即可开始响应，且在输入错误之后显示提示信息;
  - play_again2.c：不回显输入字符，且在输入错误之后不显示提示信息；
  - play_again3.c：非阻塞输入；
  - play_again4.c：加入了对 `<Ctrl-C>` 信号的处理。

### `signal`文件夹

为了学习信号而做的一些小实验。

- sigdemo1.c：对 `<Ctrl-C>`（也就是 `SIGINT` ） 信号的处理；
- sigdemo2.c：对 `<Ctrl-C>`（也就是 `SIGINT` ） 信号的忽略（`SIG_IGN`）。