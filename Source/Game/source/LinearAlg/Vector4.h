#pragma once
#include <cmath>
namespace Tga
{
    template<typename T>
    class Vector4;
}

namespace CommonUtilities
{
    template<typename T>
    class Vector4
    {
    public:
        T x; // Explicitly public for direct access
        T y; // Explicitly public for direct access
        T z; // Explicitly public for direct access
        T w; // Explicitly public for direct access

        Vector4();
        Vector4(const T& aX, const T& aY, const T& aZ, const T& aW);

        // Default Copy Constructor and assignment
        Vector4(const Vector4<T>& aVector) = default;
        Vector4<T>& operator=(const Vector4<T>& aVector) = default;

        // Default destructor (compiler generated)
        ~Vector4();

        // Returns a Vector4 with a different component type
        // Useful to do i.e
        // Vector4<unsigned int> screenSize;
        // Vector4<float> floatSize = screenSize.ToType<float>();
        template<class TargetType>
        Vector4<TargetType> ToType() const;

        // Returns a copy converted to a TGE vector
        Tga::Vector4<T> ToTga() const;

        // Negate
        Vector4<T> operator-() const;

        // Returns length^2
        T LengthSqr() const;

        // Returns length (no function requirement for T = int)
        T Length() const;

        // Return a normalized copy of this vector
        // If length == 0, this should return a vector (0,0,0)
        Vector4<T> GetNormalized() const;

        // Normalize the vector
        // If length == 0, do nothing
        void Normalize();

        // Returns the dot-product of this vector and aVector
        T Dot(const Vector4<T>& aVector) const;
    };

    //Returns the vector sum of aVector0 and aVector1 
    template <typename T>  
    Vector4<T> operator+(const Vector4<T>& aVector0, const Vector4<T>& aVector1); 

    //Returns the vector difference of aVector0 and aVector1 
    template <typename T>  
    Vector4<T> operator-(const Vector4<T>& aVector0, const Vector4<T>& aVector1); 

    //Returns the vector aVector0 component-multiplied by aVector1  
    template <typename T>  
    Vector4<T> operator*(const Vector4<T>& aVector0, const Vector4<T>& aVector1); 

    //Returns the vector aVector multiplied by the scalar aScalar. Vector * Scalar 
    template <typename T>  
    Vector4<T> operator*(const Vector4<T>& aVector, const T& aScalar); 

    //Returns the vector aVector multiplied by the scalar aScalar. Scalar * Vector 
    template <typename T>  
    Vector4<T> operator*(const T& aScalar, const Vector4<T>& aVector); 

    //Returns the vector aVector divided by the scalar aScalar 
    template <typename T>  
    Vector4<T> operator/(const Vector4<T>& aVector, const T& aScalar); 

    //Equivalent to setting aVector0 to (aVector0 + aVector1) 
    template <typename T>  
    void operator+=(Vector4<T>& aVector0, const Vector4<T>& aVector1); 

    //Equivalent to setting aVector0 to (aVector0 - aVector1) 
    template <typename T>  
    void operator-=(Vector4<T>& aVector0, const Vector4<T>& aVector1); 

    //Equivalent to setting aVector to (aVector * aScalar) 
    template <typename T>
    void operator*=(Vector4<T>& aVector, const T& aScalar); 

    //Equivalent to setting aVector to (aVector / aScalar) 
    template <typename T>  
    void operator/=(Vector4<T>& aVector, const T& aScalar);

    // TODO: Implementation below here
// ----------------------------------------------------------------------------------------------

    template<typename T>
    inline Vector4<T>::Vector4()
    {
        x = 0;
        y = 0;
        z = 0;
        w = 0;
    }

    template<typename T>
    inline Vector4<T>::Vector4(const T& aX, const T& aY, const T& aZ, const T& aW)
    {
        x = aX;
        y = aY;
        z = aZ;
        w = aW;
    }

    template<typename T>
    inline Vector4<T>::~Vector4()
    {
    }

    template<typename T>
    inline Tga::Vector4<T> Vector4<T>::ToTga() const
    {
        return Tga::Vector4<T>(x,y,z,w);
    }

    template<typename T>
    inline Vector4<T> Vector4<T>::operator-() const
    {
        return Vector4<T>(-x,-y,-z,-w);
    }

    template<typename T>
    inline T Vector4<T>::LengthSqr() const
    {
        return T((x * x) + (y * y) + (z * z) + (w * w));
    }

    template<typename T>
    inline T Vector4<T>::Length() const
    {
        return T(sqrt((x * x) + (y * y) + (z * z) + (w*w)));
    }

    template<typename T>
    inline Vector4<T> Vector4<T>::GetNormalized() const
    {
        if (Length() == 0)
        {
            return Vector4<T>(0, 0, 0,0);
        }
        else
        {
            return Vector4<T>(x / Length(), y / Length(), z / Length(), w / Length());
        }
    }

    template<typename T>
    inline void Vector4<T>::Normalize()
    {
        if (Length() == 0)
        {

        }
        else
        {
            T length = Length();
            ((x /= length) , (y /= length) , (z /= length) , (w/= length));
        }
    }

    template<typename T>
    inline T Vector4<T>::Dot(const Vector4<T>& aVector) const
    {
        return T((x * aVector.x) + (y * aVector.y) + (z * aVector.z) + (w * aVector.w));
    }


    template<typename T>
    template<class TargetType>
    inline Vector4<TargetType> Vector4<T>::ToType() const
    {
        return Vector4<TargetType>(x,y,z,w);
    }

    template<typename T>
    Vector4<T> operator+(const Vector4<T>& aVector0, const Vector4<T>& aVector1)
    {
        return Vector4<T>(aVector0.x + aVector1.x, aVector0.y + aVector1.y, aVector0.z + aVector1.z, aVector0.w + aVector1.w);
    }

    template<typename T>
    Vector4<T> operator-(const Vector4<T>& aVector0, const Vector4<T>& aVector1)
    {
        return Vector4<T>(aVector0.x - aVector1.x, aVector0.y - aVector1.y, aVector0.z - aVector1.z, aVector0.w - aVector1.w);
    }

    template<typename T>
    Vector4<T> operator*(const Vector4<T>& aVector0, const Vector4<T>& aVector1)
    {
        return Vector4<T>(aVector0.x * aVector1.x, aVector0.y * aVector1.y, aVector0.z * aVector1.z, aVector0.w*aVector1.w);
    }

    template<typename T>
    Vector4<T> operator*(const Vector4<T>& aVector, const T& aScalar)
    {
        return Vector4<T>(aVector.x * aScalar, aVector.y * aScalar, aVector.z * aScalar, aVector.w * aScalar);
    }

    template<typename T>
    Vector4<T> operator*(const T& aScalar, const Vector4<T>& aVector)
    {
        return aVector * aScalar;
    }

    template<typename T>
    Vector4<T> operator/(const Vector4<T>& aVector, const T& aScalar)
    {
        return Vector4<T>(aVector.x / aScalar, aVector.y / aScalar, aVector.z / aScalar, aVector.w / aScalar);
    }

    template<typename T>
    void operator+=(Vector4<T>& aVector0, const Vector4<T>& aVector1)
    {
        aVector0.x = aVector0.x + aVector1.x;
        aVector0.y = aVector0.y + aVector1.y;
        aVector0.z = aVector0.z + aVector1.z;
        aVector0.w = aVector0.w + aVector1.w;
    }

    template<typename T>
    void operator-=(Vector4<T>& aVector0, const Vector4<T>& aVector1)
    {
        aVector0.x = aVector0.x - aVector1.x;
        aVector0.y = aVector0.y - aVector1.y;
        aVector0.z = aVector0.z - aVector1.z;
        aVector0.w = aVector0.w - aVector1.w;
    }

    template<typename T>
    void operator*=(Vector4<T>& aVector, const T& aScalar)
    {
        aVector = aVector * aScalar;
    }

    template<typename T>
    void operator/=(Vector4<T>& aVector, const T& aScalar)
    {
        aVector = aVector / aScalar;
    }

}