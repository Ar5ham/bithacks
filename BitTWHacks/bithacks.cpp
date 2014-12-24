
#include <iostream> 
#include <bitset>
#include "bithacks.h"
using namespace std; 

int main()
{
   int x = 10.2; 
   bithacks::showbits(x);

   
   
    system("PAUSE");
    return 0;
}
   

    /*++
        Computes sign of a given integer.

    Arguments:

        v - Integer value we want to compute the sign for.

    Return Value:

    -1 if v < 0, else 0
--*/
int bithacks::ComputeSign_1(int v)
{
    /* CHAR_BIT is the number of bits per byte (normally 8).
    *  to avoid branching on CPUs with flag registers (IA32)
    */
    int sign = -(int) ((unsigned int) ((int) v) >> (sizeof(int) * CHAR_BIT - 1));

    /* 
    * For one less instruction (but not portable): 
    *
    * sign = v >> (sizeof(int) * CHAR_BIT - 1); 
    *
    * Above evaluates to sign = v >> 31 for 32-bit integers.This is one operation 
    * faster than the obvious way, sign = -(v < 0). This trick works because when 
    * signed integers are shifted right, the value of the far left bit is copied to 
    * the other bits. The far left bit is 1 when the value is negative and 0 otherwise; 
    * all 1 bits gives -1. Unfortunately, this behavior is architecture-specific.
    * 
    * Alternatively, if you prefer the result be either -1 or +1, then use:
    * 
    * sign = +1 | (v >> (sizeof(int) * CHAR_BIT - 1));  // if v < 0 then -1, else +1
    *
    * If you prefer the result be either -1, 0, or +1, then OR with (v != 0) 
    *
    * or for portability, brevity, and (perhaps) speed:
    *  
    *  sign = (v > 0) - (v < 0); // -1, 0, or +1
    */

    return sign;
}

 /*++
        Computes sign of a given integer. Using bit mask

    Arguments:

        v - Integer value we want to compute the sign for.

    Return Value:

    -1 if v < 0, else 0
--*/
int bithacks::ComputeSign_2(int x)
{
    // The & will result either in 0x80000000 or 0x00000000 
    return (x & bithacks::bit_mask(x) ? -1 : 0);
}

 /*++
        Creates a bit mask according to the size of integer variable passed

    Arguments:

        x - Integer value which we want to create a bit mask for.

    Return Value:

        bit mask with MSB set to 1.
--*/
template <typename T> T bithacks::bit_mask(T x)
{
    return 1 << (sizeof(x) * CHAR_BIT) - 1;
}


/*++
        Prints out bit values 0s and 1s of a given integer.

    Arguments:

        x - The variable which we want to create a bit mask for.

    Return Value:

        bit mask with MSB set to 1.
--*/
template <typename T> void bithacks::showbits(T x)
{
   cout << bitset<sizeof(T) * CHAR_BIT>(x).to_string() << endl; 
}
