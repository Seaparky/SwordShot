#pragma once
#include <cmath>

namespace Tga
{
    template<typename T>
    class Vector2;
}

namespace CommonUtilities
{
    template<typename T>
    class Vector2
    {
    public:
        T x; // Explicitly public for direct access
        T y; // Explicitly public for direct access

        Vector2();
        Vector2(const T& aX, const T& aY);

        // Default Copy Constructor and assignment
        Vector2(const Vector2<T>& aVector) = default;
        Vector2<T>& operator=(const Vector2<T>& aVector) = default;

        // Default destructor (compiler generated)
        ~Vector2();

        // Returns a Vector2 with a different component type
        // Useful to do i.e
        // Vector2<unsigned int> screenSize;
        // Vector2<float> floatSize = screenSize.ToType<float>();
        template<class TargetType>
        Vector2<TargetType> ToType() const;

        // Returns a copy converted to a TGE vector
        Tga::Vector2<T> ToTga() const;

        // Negate
        Vector2<T> operator-() const;

        // Returns length^2
        T LengthSqr() const;

        // Returns length (no function requirement for T = int)
        T Length() const;

        // Return a normalized copy of this vector
        // If length == 0, this should return a vector (0,0,0)
        Vector2<T> GetNormalized() const;

        // Normalize the vector
        // If length == 0, do nothing
        void Normalize();

        // Returns the dot-product of this vector and aVector
        T Dot(const Vector2<T>& aVector) const;
    };

    //Returns the vector sum of aVector0 and aVector1 
    template <typename T>  
    Vector2<T> operator+(const Vector2<T>& aVector0, const Vector2<T>& aVector1); 

    //Returns the vector difference of aVector0 and aVector1 
    template <typename T>  
    Vector2<T> operator-(const Vector2<T>& aVector0, const Vector2<T>& aVector1); 

    //Returns the vector aVector0 component-multiplied by aVector1  
    template <typename T>  
    Vector2<T> operator*(const Vector2<T>& aVector0, const Vector2<T>& aVector1); 

    //Returns the vector aVector multiplied by the scalar aScalar. Vector * Scalar 
    template <typename T>  
    Vector2<T> operator*(const Vector2<T>& aVector, const T& aScalar); 

    //Returns the vector aVector multiplied by the scalar aScalar. Scalar * Vector 
    template <typename T>  
    Vector2<T> operator*(const T& aScalar, const Vector2<T>& aVector); 

    //Returns the vector aVector divided by the scalar aScalar 
    template <typename T>  
    Vector2<T> operator/(const Vector2<T>& aVector, const T& aScalar); 

    //Equivalent to setting aVector0 to (aVector0 + aVector1) 
    template <typename T>  
    void operator+=(Vector2<T>& aVector0, const Vector2<T>& aVector1); 

    //Equivalent to setting aVector0 to (aVector0 - aVector1) 
    template <typename T>  
    void operator-=(Vector2<T>& aVector0, const Vector2<T>& aVector1); 

    //Equivalent to setting aVector to (aVector * aScalar) 
    template <typename T>
    void operator*=(Vector2<T>& aVector, const T& aScalar); 

    //Equivalent to setting aVector to (aVector / aScalar) 
    template <typename T>  
    void operator/=(Vector2<T>& aVector, const T& aScalar);


    // TODO: Implementation below here
    // ----------------------------------------------------------------------------------------------



    template<typename T>
    inline Vector2<T>::Vector2()
    {
        x = 0;
        y = 0;
    }

    template<typename T>
    inline Vector2<T>::Vector2(const T& aX, const T& aY)
    {
        x = aX;
        y = aY;
    }

    template<typename T>
    inline Vector2<T>::~Vector2()
    {
        
    }

    template<typename T>
    inline Tga::Vector2<T> Vector2<T>::ToTga() const
    {
        return Tga::Vector2<T>(x,y);
    }

    template<typename T>
    inline Vector2<T> Vector2<T>::operator-() const
    {
        return Vector2<T>(-x,-y);
    }

    template<typename T>
    inline T Vector2<T>::LengthSqr() const
    {
        return T((x * x) + (y * y));
    }

    template<typename T>
    inline T Vector2<T>::Length() const
    {
        return T(sqrt((x * x) + (y * y)));
    }

    template<typename T>
    inline Vector2<T> Vector2<T>::GetNormalized() const
    {
        if (Length() == 0)
        {
        return Vector2<T>(0,0);
        }
        else
        {
            return Vector2<T>(x / Length() , y / Length());
        }
    }

    template<typename T>
    inline void Vector2<T>::Normalize()
    {
        if (Length() == 0)
        {
        }
        else
        {
            T length = Length();
            ((x/=length),(y/=length));
        }
    }

    template<typename T>
    inline T Vector2<T>::Dot(const Vector2<T>& aVector) const
    {
        return T((x * aVector.x) + (y * aVector.y));
    }

    template<typename T>
    template<class TargetType>
    inline Vector2<TargetType> Vector2<T>::ToType() const
    {
        return Vector2<TargetType>(x,y);
    }


    template<typename T>
    Vector2<T> operator+(const Vector2<T>& aVector0, const Vector2<T>& aVector1)
    {
        return Vector2<T>(aVector0.x + aVector1.x, aVector0.y + aVector1.y);
    }

    template<typename T>
    Vector2<T> operator-(const Vector2<T>& aVector0, const Vector2<T>& aVector1)
    {
        return Vector2<T>(aVector0.x - aVector1.x, aVector0.y - aVector1.y);
    }

    template<typename T>
    Vector2<T> operator*(const Vector2<T>& aVector0, const Vector2<T>& aVector1)
    {
        return Vector2<T>(aVector0.x*aVector1.x, aVector0.y*aVector1.y);
    }

    template<typename T>
    Vector2<T> operator*(const Vector2<T>& aVector, const T& aScalar)
    {
        return Vector2<T>(aVector.x * aScalar, aVector.y * aScalar);
    }

    template<typename T>
    Vector2<T> operator*(const T& aScalar, const Vector2<T>& aVector)
    {
        return aVector * aScalar;
    }

    template<typename T>
    Vector2<T> operator/(const Vector2<T>& aVector, const T& aScalar)
    {
        return Vector2<T>(aVector.x / aScalar, aVector.y / aScalar) ;
    }

    template<typename T>
    void operator+=(Vector2<T>& aVector0, const Vector2<T>& aVector1)
    {
        aVector0.x += aVector1.x;
        aVector0.y += aVector1.y;
    }

    template<typename T>
    void operator-=(Vector2<T>& aVector0, const Vector2<T>& aVector1)
    {
        aVector0.x -= aVector1.x;
        aVector0.y -= aVector1.y;
    }

    template<typename T>
    void operator*=(Vector2<T>& aVector, const T& aScalar)
    {
        aVector = aVector * aScalar;
    }

    template<typename T>
    void operator/=(Vector2<T>& aVector, const T& aScalar)
    {
        aVector = aVector / aScalar;
    }

}

