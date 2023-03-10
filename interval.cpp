#include <iostream>
#include <algorithm>

namespace felipe
{
    
template< class T >
class interval
{
    private:
        T lower_;
        T upper_;
    public:
        interval( T lower, T upper ): lower_( lower ), upper_( upper ) {}
        ~interval() {} 

        T lower() const
        {
            return lower_;
        }

        T upper() const
        {
            return upper_;
        }

        friend std::ostream& operator<<( std::ostream& os, interval< T > const& x )
        {
            os << "[" << x.lower() << "," << x.upper() << "]" << std::endl;

            return os;
        }

        interval< T > operator*( interval< T > const& x ) const
        {
            T s1 = lower_ * x.lower(); 
            T s2 = lower_ * x.upper();
            T s3 = upper_ * x.lower();
            T s4 = upper_ * x.upper();
            
            interval<T> y(std::min({s1,s2,s3,s4}), std::max({s1,s2,s3,s4}));


            return y;
        }

        friend interval< T > operator*( T value, interval< T > const& x ) 
        {
            interval<T> y(value, value);

            return y*x;
        }

        interval< T > operator/( interval< T > const& x ) const
        {
            interval<T> y(1.0/x.upper(), 1.0/x.lower());

            return *this * y;
        }

        interval< T > operator+( interval< T > const& x ) const
        {
            interval<T> y(lower_ + x.lower(), upper_ + x.upper());

            return y;
        }

        interval< T > operator-( interval< T > const& x ) const
        {
            interval<T> y(lower_ - x.upper(), upper_ - x.lower());

            return y;
        }

        
};
} // namespace felipe


int main() {

    felipe::interval<double> x(-2,-1);
    felipe::interval<double> y(-5,-3);

    std::cout << "\nInterval X=";
    std::cout << x;

    std::cout << "\nInterval Y=";
    std::cout << y;

    std::cout << "\nInterval X.Y=";
    std::cout << x*y;

    std::cout << "\nInterval 2.Y=";
    std::cout << 2*y;

    std::cout << "\nInterval X+Y=";
    std::cout << x+y;

    std::cout << "\nInterval X-Y=";
    std::cout << x-y;

    std::cout << "\nInterval X/Y=";
    std::cout << x/y;

    return 0;
}
