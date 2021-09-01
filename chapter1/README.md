# Chapter 1

### 主要内容

在本章主要完成的内容是命令 `more` ，其各个版本及响应的改进如下：
- more01.c：最基本的功能：固定打印窗格尺寸大小，从标准输入 `stdin` 中读取键盘输入字符……；
- more02.c：为了解决 `ls /bin | ./more.out` 不会停止的问题，修改键盘的输入为从 `/dev/tty` 中读取，而不是从标准输入中读取；
- more03.c：解决了几个问题：
  - 消除重复打印的 ` --more?-- ` ；
  - 适配了当前终端窗口尺寸；
  - 不需要输入回车即可响应；
  - 使输入的选项不回显；
  - 将回车替换为输入 `n` 表示显示下一行，更符合输入习惯。

### 参考

#### 适配当前终端窗口尺寸

```c
struct winsize window_size;
ioctl(STDIN_FILENO, TIOCGWINSZ, &window_size);
```

通过上述方式即可得到窗口尺寸，其中 `struct winsize` 的结构为：

```c
//其中struct winsize位于termios.h头文件内
//具体位置在 /usr/include/asm-generic/termios.h
struct winsize {
    unsigned short ws_row;      // 以字符为单位的行数
    unsigned short ws_col;      // 以字符为单位的列数
    unsigned short ws_xpixel;   // 以像素为单位的水平方向尺寸
    unsigned short ws_ypixel;   // 以像素为单位的竖直方向尺寸
}
```

#### 改变光标位置

```c
printf("\r\033[K");
```

其中 `\r` 表示将光标移动到行首，`\033[K` 表示清空此行光标之后的内容。

其他的打印选项参考这个链接：[C/C++ linux下光标定位和清屏函数(printf 实现)](https://blog.csdn.net/kevinshq/article/details/8179252?utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7EBlogCommendFromBaidu%7Edefault-5.essearch_pc_relevant&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7EBlogCommendFromBaidu%7Edefault-5.essearch_pc_relevant)。

#### 使输入不回显且无需输入回车即可响应

```c
system("stty raw -echo");
```

其中，`system` 函数中的内容为 `stty raw` 时表示使输入无需输入回车即可响应；`system` 函数中的内容为 `stty -echo` 时表示使输入不回显。

注意，在使用完之后要将终端恢复为默认状态，恢复的方法如下。

```c
system("stty -raw echo");
```
