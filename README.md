# The Galaxy Programming Language

Author: Nicholas E. Manley <nm3n8@mail.umkc.edu>

## About

Galaxy is just a simple hobby project to help me learn about compilers.
It's not intended for real world use, and it is unlikely to be well
maintained after a certain point. It is not recommended that it be
used for a project of any importance.

## Status

Galaxy is in the very early stages of development. Currently, it cannot
compile any code. The lexer and parser are still being developed.

## Development

Galaxy uses LLVM 3.4.2 as the backend and has identical
dependencies. See the [LLVM Requirements](http://llvm.org/releases/3.4.2/docs/GettingStarted.html#requirements)
for information on what dependencies are required to build Galaxy.

## Building

Use the following commands to build and install Galaxy.

```shell
$ ./configure --enable-targets=x86
$ make
$ make install
```

## Grammar

```
digit = "0"|"1"|"2"|"3"|"4"|"5"|"6"|"7"|"8"|"9" ;
letter = "a"|"b"|"c"|"d"|"e"|"f"|"g"|"h"|"i"|"j"|
         "k"|"l"|"m"|"n"|"o"|"p"|"q"|"r"|"s"|"t"|
         "u"|"v"|"w"|"x"|"y"|"z" ;
capital = "A"|"B"|"C"|"D"|"E"|"F"|"G"|"H"|"I"|"J"|
          "K"|"L"|"M"|"N"|"O"|"P"|"Q"|"R"|"S"|"T"|
          "U"|"V"|"W"|"X"|"Y"|"Z" ;
alpha = (letter | capital) , { letter | capital }
binop = "+" | "-" | "*" | "/" ;

expression = term , { binop , term } ;
term = number | "(", expression, ")" | "-", number ;
number = digit , { digit } ;
```
