
#include <iostream> 
#include <bitset>
#include <iomanip>
#include "bithacks.h"
using namespace std; 

int main()
{
   /*int x = 10.2; 
   bithacks::showbits(x);*/

   /* int i = 'a';
    char buffer[33];
    _itoa_s(i, buffer, 2);
    printf("binary: %s\n", buffer);*/
   

    //Tests cases for Min (Integral Only)
    /*int x = 3, y = 4; 
    std::cout<< "Min(" << x <<", " << y <<"): " << bithacks::Min(x, y) ; 

    long e = 30, f = 40;
    std::cout << "Min(" << e << ", " << f << "): " << bithacks::Min(e, f);*/

    //Tests cases for Abs
   /* int x = -1000; 
    cout << bithacks::Abs(x) <<endl; 

    int y = 200; 
    cout << bithacks::Abs(y) << endl;*/


    system("PAUSE");
    return 0;
}
  


//void toBinary(float *num) {
//    char* numi = reinterpret_cast<char*>(num);
//    cout << num << " " << numi << endl;
//    
//    for (int i = 8 * sizeof(num) ; i < length; i++)
//    {
//
//    }
//    
//    for (int i = 0; i < 8 * sizeof(num); i++){
//        if (numi & (1 << i)) {
//            cout << 1;
//        }
//        else {
//            cout << 0;
//        }
//    }
//    cout << endl << endl;
//}

    /*++
        Computes sign of a given integer.

    Arguments:

        v - Integer value we want to compute the sign for.

    Return Value:

    -1 if v < 0, else 0
--*/
int bithacks::ComputeSign(int v)
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
int bithacks::ComputeSign_BitMask(int x)
{
    // The & will result either in 0x80000000 or 0x00000000 
    return (x & bithacks::bit_mask(x) ? -1 : 0);
}

/*++
        Returns the smaller of two integral values.
        
        On some rare machines where branching is very expensive and no condition move 
        instructions exist, the expression below might be faster than the obvious approach, 
        r = (x < y) ? x : y, even though it involves two more instructions.
        (Typically, the obvious approach is best, though.) It works because if x < y, 
        then -(x < y) will be all **ones**, so r = y ^ (x ^ y) & ~0 = y ^ x ^ y = x. Otherwise, 
        if x >= y, then -(x < y) will be all **zeros**, so r = y ^ ((x ^ y) & 0) = y. On some machines, 
        evaluating (x < y) as 0 or 1 requires a branch instruction, so there may be no advantage.

        If you know that INT_MIN <= x - y <= INT_MAX, then you can use the following, 
        which are faster because (x - y) only needs to be evaluated once.
        
        r = y + ((x - y) & ((x - y) >> (sizeof(int) * CHAR_BIT - 1))); // min(x, y)
        r = x - ((x - y) & ((x - y) >> (sizeof(int) * CHAR_BIT - 1))); // max(x, y)

    Arguments:

        x - An arguement (integral).
        y - Another argument (integral).

    Return Value:

        The smaller of X and Y.
--*/
template<class T> std::enable_if_t<std::is_integral<T>::value, T>
    bithacks::Min(const T& x, const T& y)
{
    return y ^ ((x ^ y) & -(x < y)); // min(x, y)
}

/*++
        Returns the larger of two integral values.

    Arguments:

        x - An arguement (integral).
        y - Another argument (integral).

    Return Value:

        The larger of X and Y.
--*/
template<class T> std::enable_if_t<std::is_integral<T>::value, T>
    bithacks::Max(const T& x, const T& y)
{
    return x ^ ((x ^ y) & -(x < y)); // max(x, y)
}

/*++
        Returns the absolute value of integral argument provided.

    Arguments:

        x - An arguement (integral).

    Return Value:

        Abslute value of X.
--*/

template<class T> std::enable_if_t<std::is_integral<T>::value, T>
    bithacks::Abs(const T& x)
{
    int const mask = x >> sizeof(int) * CHAR_BIT - 1; 
    return (x + mask) ^ mask;
}

 /*++
        Creates a bit mask according to the size of integer variable passed

    Arguments:

        x - Integer value which we want to create a bit mask for.

    Return Value:

        bit mask with MSB set to 1.
--*/
    template <typename T> std::enable_if_t<std::is_integral<T>::value, T> 
        bithacks::bit_mask(T x)
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
