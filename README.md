# Contiki-CM5000-MSP-programming

Frequently asked questions and  Answers: https://docs.google.com/document/d/1GH2Q-Dr8PxqmjQwxbL9UkLUDsel1xHCho7ggKwXeyAg/edit 



Floating Vs Fixed-point 
In signal processing most important operation is inner product operation, which is basically dot product of two vectors. Most of the signal transforms are defined in the real field. Therefore, it requires  floating point operations. The TelosB mote can perform both floating-point and fixed-point arithmetic.  
To emulate dot product we define the following code
float a=2.3, b=7.8, c[256],frac;

for (i=0; i<256; i++)
  	{
  		a=a+1;
  		c[i]=a*b;
  	}

These are performed using floating-point arithmetic. System ticks in TelosB mote are measured using   RTIMER_NOW().  This dot product takes around 5033 system ticks.  


Now same operation is performed using fixed-point arithmetic. Qm.n format is used where “m” is the number of magnitude bits and “n” is the number of fraction bits.

For this example, m=12 and n=4. The values of “a” and “b” are converted to Q12.4 format as,

uint16_t i, aFi=0x0025, bFi=0x007d, cFi[256];

One can use MATLAB/ PYTHON to convert these numbers in required format.  MATLAB is hex(fi(2.3,0,16,4)) and  hex(fi(7.8,0,16,4))  . 

 Now we need to define fixed-point multiplication because we are working in our defined number system. The multiplication function is defined as,

uint16_t multiply(uint16_t a, uint16_t b)
{
  uint32_t result;
  uint16_t out;
  result= (uint32_t) a * (uint32_t) b; // typecast to avoid oveflow error 

  result= result>>fracPart;  // bring back to the Qn.m formate  

  out=result;
   return out;
}


Now the dot product is changed to fixed point arithmetic as,

for (i=0; i<256; i++){
  	aFi=aFi+0x0010;    // 1 fixedpoint is 0x0010 for Q12.4
  	cFi[i]=multiply(aFi, bFi);
  	}
uint16_t i, aFi=0x0025, bFi=0x007d, cFi[256];
This dot product using fixed-point arithmetic takes only around 84 system ticks.   To read the results back in floating point one can use the following commands in MATLAB,
result=(fi([],0,16,4));
result.hex=’19e’;   //  19e is the result stored in cFi[0]
result

Code is given in the file named as “fixedPoint.c”

Summery: Fixed point arithmetic can reduce execution time significantly. It should be clear that fixed-point arithmetic will have small quantization error. In the case when accuracy is critical use floating-point otherwise use fixed-point arithmetic in the resource-constrained devices. By increasing fraction value “n” accuracy can be increased in the fixed-point arithmetic. Floating numbers and operations take more memory as compared to fixed-point.



Math operations

Now we will observe the execution time and memory uses for simple square root of a number.

One simple way is to include the <math.h> in the file and use sqrt() function. This will give you results but consume more memory and takes more time.

Another way is to use a customized square root function. Square root function’s efficient implementations and motivation can be found here: http://www.azillionmonkeys.com/qed/sqroot.html.
One sample function for sqrt is given here:
uint16_t sqrt_uint32(uint32_t val) {
    uint32_t temp, g=0, b = 0x8000, bshft = 15;
    do {
        if (val >= (temp = (((g << 1) + b)<<bshft--))) {
           g += b;
           val -= temp;
        }
    } while (b >>= 1);
    return (uint16_t) g;
}

Code for comparison is given in the file named as  sqrtFixedpoint.c.

The sqrt() from the math library takes around  365 system ticks. Whereas, the function takes sqrt_uint32()takes only 242 system ticks.
Summery: The customized math functions may perform better and take less memory compared to the library defined.


Memory compression of NULLNET and hello world program. 
If you are not using IP layer and higher then to save memory use NULLNET. The memory uses for hello-world program  and nullnet program are shown in the figure below. The hello-world program usages 42189 bytes whereas nullnet uses only 17063 bytes. 



 

