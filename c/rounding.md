# 四捨五入公平嗎？

數字只要保留部份有效位數時

四捨五入規則和四捨六入五成雙規則。在台灣尚可見到無條件捨去法、無條件進位法

Banker's Rounding

Another common way to re
duce the significant bits
 representing a number 
is to simply mask of
f the N-M lower bits. Thi
s process is known as 
trunca-
tion
 and results in a relatively large bias

Rounding
 is a means of reducing the prec
ision of a number by removing a 
lower-order range of bits from that 
number’s representation and possibly 
modifying the remaining portion of the number to more accurately repre-
sent its former value. For 
example, the original numb
er will have N bits of 
precision, whereas the new number wi
ll have only M bits of precision 
(where N>M), so N-M bits of precision
 are removed from the number in 
the process of rounding.
The 
round-to-nearest
 method returns the closest number to the original. 
By convention, an original number
 lying exactly halfway between two 
numbers always rounds up to the la
rger of the two. For example, when 
rounding the 3-bit, two’s-complement
 fraction 0.25 (binary 0.01) to the 
nearest 2-bit two’s-complement fractio
n, this method returns 0.5 (binary 
0.1). The original fraction lies 
exactly midway 
between 0.5 and 0.0 
(binary 0.0), so this method rounds up
. Because it always rounds up, this 
method is called 
biased rounding
.
The convergent rounding method also returns the closest number to the original. However, in cases where the 
original number lies exactly halfway between two numbers, this method re
turns the nearest even number, the one containing an LSB of 0. So for th
e example above, the result would be 0.0, since that is the even numbered
 choice of 0.5 and 0.0. Since it rounds up and down based on the surrounding values, this method is called 
unbiased rounding
. 

round-to-zero
round-to-nearest

[Blackfin ® Processor Programming Reference](http://www.analog.com/media/en/dsp-documentation/processor-manuals/Blackfin_pgr_rev2.2.pdf)
[Shawn's DSP Tutorials](https://sestevenson.wordpress.com/index-to-tutorials)

https://mathematica.stackexchange.com/questions/2116/why-round-to-even-integers
http://www.artist-embedded.org/docs/Events/2009/EmbeddedControl/SLIDES/FixPoint.pdf
