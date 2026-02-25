#pragma once
#include <cmath>
namespace Tga
{
    template<typename T>
    class Vector3;
}



namespace CommonUtilities
{
    template<typename T>
    class Vector3
    {
    public:
        T x; // Explicitly public for direct access
        T y; // Explicitly public for direct access
        T z; // Explicitly public for direct access

        Vector3();
        Vector3(const T& aX, const T& aY, const T& aZ);

        // Default Copy Constructor and assignment
        Vector3(const Vector3<T>& aVector) = default;
        Vector3<T>& operator=(const Vector3<T>& aVector) = default;

        // Default destructor (compiler generated)
        ~Vector3();

        // Returns a Vector3 with a different component type
        // Useful to do i.e
        // Vector3<unsigned int> screenSize;
        // Vector3<float> floatSize = screenSize.ToType<float>();
        template<class TargetType>
        Vector3<TargetType> ToType() const;

        // Returns a copy converted to a TGE vector
        Tga::Vector3<T> ToTga() const;

        // Negate
        Vector3<T> operator-() const;

        // Returns length^2
        T LengthSqr() const;

        // Returns length (no function requirement for T = int)
        T Length() const;

        // Return a normalized copy of this vector
        // If length == 0, this should return a vector (0,0,0)
        Vector3<T> GetNormalized() const;

        // Normalize the vector
        // If length == 0, do nothing
        void Normalize();

        // Returns the dot-product of this vector and aVector
        T Dot(const Vector3<T>& aVector) const;

        // Returns the cross-product of this vector and aVector
        Vector3<T> Cross(const Vector3<T>& aVector) const;
    };

    //Returns the vector sum of aVector0 and aVector1 
    template <typename T>  
    Vector3<T> operator+(const Vector3<T>& aVector0, const Vector3<T>& aVector1); 

    //Returns the vector difference of aVector0 and aVector1 
    template <typename T>  
    Vector3<T> operator-(const Vector3<T>& aVector0, const Vector3<T>& aVector1); 

    //Returns the vector aVector0 component-multiplied by aVector1  
    template <typename T>  
    Vector3<T> operator*(const Vector3<T>& aVector0, const Vector3<T>& aVector1); 

    //Returns the vector aVector multiplied by the scalar aScalar. Vector * Scalar 
    template <typename T>  
    Vector3<T> operator*(const Vector3<T>& aVector, const T& aScalar); 

    //Returns the vector aVector multiplied by the scalar aScalar. Scalar * Vector 
    template <typename T>  
    Vector3<T> operator*(const T& aScalar, const Vector3<T>& aVector); 

    //Returns the vector aVector divided by the scalar aScalar 
    template <typename T>  
    Vector3<T> operator/(const Vector3<T>& aVector, const T& aScalar); 

    //Equivalent to setting aVector0 to (aVector0 + aVector1) 
    template <typename T>  
    void operator+=(Vector3<T>& aVector0, const Vector3<T>& aVector1); 

    //Equivalent to setting aVector0 to (aVector0 - aVector1) 
    template <typename T>  
    void operator-=(Vector3<T>& aVector0, const Vector3<T>& aVector1); 

    //Equivalent to setting aVector to (aVector * aScalar) 
    template <typename T>
    void operator*=(Vector3<T>& aVector, const T& aScalar); 

    //Equivalent to setting aVector to (aVector / aScalar) 
    template <typename T>  
    void operator/=(Vector3<T>& aVector, const T& aScalar);

    // TODO: Implementation below here
// ----------------------------------------------------------------------------------------------

    template<typename T>
    inline Vector3<T>::Vector3()
    {
        x = 0;
        y = 0;
        z = 0;
    }

    template<typename T>
    inline Vector3<T>::Vector3(const T& aX, const T& aY, const T& aZ)
    {
        x = aX;
        y = aY;
        z = aZ;
    }

    template<typename T>
    inline Vector3<T>::~Vector3()
    {

    }

    template<typename T>
    inline Tga::Vector3<T> Vector3<T>::ToTga() const
    {
        return Tga::Vector3<T>(x,y,z);
    }

    template<typename T>
    inline Vector3<T> Vector3<T>::operator-() const
    {
        return Vector3<T>(-x, -y, -z);
    }

    template<typename T>
    inline T Vector3<T>::LengthSqr() const
    {
        return T((x * x) + (y * y) + (z * z));
    }

    template<typename T>
    inline T Vector3<T>::Length() const
    {
        return T(sqrt((x * x) + (y * y) + (z*z)));
    }

    template<typename T>
    inline Vector3<T> Vector3<T>::GetNormalized() const
    {
        if (Length() == 0)
        {
            return Vector3<T>(0, 0, 0);
        }
        else
        {
            return  Vector3<T>(x / Length(), y / Length(), z / Length());
        }
    }

    template<typename T>
    inline void Vector3<T>::Normalize()
    {
        if (Length() == 0)
        {

        }
        else
        {
            T length = Length();
            ((x /= length) + (y /= length) + (z /= length));
        }
    }

    template<typename T>
    inline T Vector3<T>::Dot(const Vector3<T>& aVector) const
    {
        return T((x * aVector.x) + (y * aVector.y) + (z * aVector.z));
    }

    template<typename T>
    inline Vector3<T> Vector3<T>::Cross(const Vector3<T>& aVector) const
    {
        return Vector3<T>((y*aVector.z - z*aVector.y),(z * aVector.x - x * aVector.z),(x * aVector.y - y * aVector.x));
    }

    template<typename T>
    template<class TargetType>
    inline Vector3<TargetType> Vector3<T>::ToType() const
    {
        return Vector3<TargetType>(x,y,z);
    }

    template<typename T>
    Vector3<T> operator+(const Vector3<T>& aVector0, const Vector3<T>& aVector1)
    {
        return Vector3<T>(aVector0.x + aVector1.x, aVector0.y + aVector1.y, aVector0.z + aVector1.z);

    }

    template<typename T>
    Vector3<T> operator-(const Vector3<T>& aVector0, const Vector3<T>& aVector1)
    {
        return Vector3<T>(aVector0.x - aVector1.x, aVector0.y - aVector1.y, aVector0.z - aVector1.z);
    }

    template<typename T>
    Vector3<T> operator*(const Vector3<T>& aVector0, const Vector3<T>& aVector1)
    {
        return Vector3<T>(aVector0.x * aVector1.x, aVector0.y * aVector1.y, aVector0.z*aVector1.z);
    }

    template<typename T>
    Vector3<T> operator*(const Vector3<T>& aVector, const T& aScalar)
    {
        return Vector3<T>(aVector.x * aScalar, aVector.y * aScalar, aVector.z * aScalar);
    }

    template<typename T>
    Vector3<T> operator*(const T& aScalar, const Vector3<T>& aVector)
    {
        return aVector * aScalar;
    }

    template<typename T>
    Vector3<T> operator/(const Vector3<T>& aVector, const T& aScalar)
    {
        return Vector3<T>(aVector.x / aScalar, aVector.y / aScalar, aVector.z / aScalar);
    }

    template<typename T>
    void operator+=(Vector3<T>& aVector0, const Vector3<T>& aVector1)
    {
        aVector0.x = aVector0.x + aVector1.x;
        aVector0.y = aVector0.y + aVector1.y;
        aVector0.z = aVector0.z + aVector1.z;
    }

    template<typename T>
    void operator-=(Vector3<T>& aVector0, const Vector3<T>& aVector1)
    {
        aVector0.x = aVector0.x - aVector1.x;
        aVector0.y = aVector0.y - aVector1.y;
        aVector0.z = aVector0.z - aVector1.z;
    }

    template<typename T>
    void operator*=(Vector3<T>& aVector, const T& aScalar)
    {
        aVector = aVector * aScalar;
    }

    template<typename T>
    void operator/=(Vector3<T>& aVector, const T& aScalar)
    {
        aVector = aVector / aScalar;
    }

}