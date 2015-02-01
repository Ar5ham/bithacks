


class bithacks
{
public:
    static int ComputeSign(int v);
    static int ComputeSign_BitMask(int v);
    
    template<class T>
    std::enable_if_t<std::is_integral<T>::value, T>
        static Min(const T& x, const T& y); 
    
    template<class T>
    std::enable_if_t<std::is_integral<T>::value, T>
        static Max(const T& x, const T& y);

    template<class T>
    std::enable_if_t<std::is_integral<T>::value, T>
        static Abs(const T& x);

    template <typename T> static void showbits(T x);
   
    template <typename T> std::enable_if_t<std::is_integral<T>::value, T> 
        static bit_mask(T x);
};