# brainfuck-compiler

入力したソースコード
11669 bytes
146 lines

```bat
$ time bf ./mandelbrot.bf
real    0m14.263s
user    0m8.250s
sys     0m0.328s
```

```bat
$ gcc main.c
$ ./a.out ./mandelbrot.bf
$ gcc -o mandelbrot.out mandelbrot.c
$ time ./mandelbrot.out
real    0m21.421s
user    0m20.359s
sys     0m0.063s
```

出力したソースコード
333020 bytes
11461 lines

```bat
$ gcc main.c
$ ./a.out ./mandelbrot.bf
$ gcc -std=gnu11 -O2 -DONLINE_JUDGE -o mandelbrot.out mandelbrot.c
$ time ./mandelbrot.out
real    0m2.946s
user    0m1.328s
sys     0m0.000s
```

出力したソースコード
333020 bytes
11461 lines

## 最適化1

圧縮

```bat
real    0m2.282s
user    0m1.313s
sys     0m0.031s
```

出力したソースコード
125369 bytes
4125 lines
