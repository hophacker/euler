Euler math library(c++)
========


Euler is a c++ math library created with lots of consideration of running speed which you can take to hack all kinds of hard math problems and do a lot of cool calculation.


Euler was first created when I was hacking a series of computational problems from 
[projecteuler](http://projecteuler.net/). There are a lot of repeated program routines among those questions which I think can be combined into one library. So, the work started!
Then, when I first faced a big integer problem, I tried to find some big integer library which help me. I was so disappointed to find that there was no proper big integer library which can satisfy my need. They are either so simple or buggy. Interestingly, when I downloaded the famous [C++ Big Integer library](https://mattmccutchen.net/bigint/)(If you search "big integer library" on google, it will appear at the top of the page) and ran it. I is a huge math library created like professional, but so sadly, I found that it does not support calculation like (a = a * a).

So I decided to create a Big Integer Library myself!

As a result, Euler has two parts now, one for normal math problems, such as calculating the sum of all the factors of a given number, the other is for big integer problems, such as calculating the greatest common divisor(GCD) of "123412341234123412341234123412341234"  and "12312312312414123123412312312312312412314123".

How to use `Big Integer Library`
------------
Down Euler to your project folder: `git clone https://github.com/hophacker/euler`
 
Now, make it! `make` and then all the objects and targets will appear in the folder "lib".

Open the file "testBigIntBase.cc", you will find lots of examples about how to use the BigInteger library.

Some cool examples here:

**(1)Get GCD of the two numbers I give above:**

```BigIntBase e("123412341234123412341234123412341234"), f("12312312312414123123412312312312312412314123");```

`BigIntBase g = e.gcd(f);`

`cout << g << endl`

You will get the answer is `7`

**(2)Get k-permutations of n where k=60 and n=123**

`BigIntBase a = BigIntBase::permutation(123, 60);`

`cout << a << endl`

Don't be hesitate, try it now and you will get the answer `6126426623277607558830892659050738012468992831594946549976844836830737333775846630022365422877182368153600000000000000`

**(3)Get the power of base=1234 to exponent=40**

`BigIntBase a("1234"), b = a.pow(40);`

`cout << b << endl`


The answer is:`4493723926702212177102715930895505163093661512740028111091444935676043681712474862933310710677287635716764659044658735742976`



How to use `Normal math functions`
------------
Actually, I think it's trivial to show these examples here. You can just check the file *euler.cc* and you will get the right way by looking at the function names and my comments.


