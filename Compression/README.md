# Demonstration for various methods of text compression implemented in C++

> Input string:
```
Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nullam at volutpat purus, ut lacinia enim.
Sed bibendum, turpis ac hendrerit bibendum, lectus augue varius turpis, ut varius nisl arcu non
libero. Vivamus nec erat purus. Nulla facilisi. Sed ut turpis in justo tincidunt tincidunt. Fusce
lacinia justo vel augue malesuada, id interdum urna egestas. Nullam tristique mi vel purus
facilisis tristique. Maecenas sit amet tincidunt felis, eget tincidunt nisi.
```

> Huffman encoding:
```
Huffman Encoding
---------------------------
 : 001
,: 011101
.: 010001
F: 011100110
L: 11010011
M: 011100111
N: 1001101
S: 10011000
V: 110100101
a: 1000
b: 0111000
c: 01001
d: 01111
e: 0101
f: 1101000
g: 110101
h: 110100100
i: 101
j: 10011001
l: 00000
m: 10010
n: 1100
o: 010000
p: 11011
q: 01110010
r: 00001
s: 0110
t: 0001
u: 111
v: 100111
Bits in input string: 3688
Bits in encoded string: 1933
Compression rate: 52.4132%
```
