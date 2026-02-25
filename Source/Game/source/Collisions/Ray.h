#pragma once
#include "../LinearAlg/Vector3.h"

namespace CommonUtilities
{
    template<typename T>
    class Ray
    {
    public:
        Ray();
        Ray(const Vector3<T>& aOrigin, const Vector3<T>& aDirection);

        Vector3<T> myOrigin;
        Vector3<T> myDirection;

        void InitWithTwoPoints(const Vector3<T>& aPoint0, const Vector3<T>& aPoint1);
        void InitWithOriginAndDirection(const Vector3<T>& aPoint, const Vector3<T>& aDirection);
        
        const Vector3<T> GetOrigin() const;
        const Vector3<T> GetDirection() const;

        inline const bool IsInFront(const Vector3<T>& aPoint);
    };
    template<typename T>
    inline Ray<T>::Ray()
    {
        myDirection = { 0,0,0 };
        myOrigin = { 0,0,0 };
    }
    template<typename T>
    inline Ray<T>::Ray(const Vector3<T>& aOrigin, const Vector3<T>& aDirection)
    {
        myDirection = aDirection;
        myOrigin = aOrigin;
    }
    template<typename T>
    inline void Ray<T>::InitWithTwoPoints(const Vector3<T>& aPoint0, const Vector3<T>& aPoint1)
    {
        myOrigin = aPoint0;
        if (aPoint0.x < aPoint1.x)
        {
            myDirection.x = 1;
        }
        if (aPoint0.y < aPoint1.y)
        {
            myDirection.y = 1;
        }
        if (aPoint0.z < aPoint1.z)
        {
            myDirection.z = 1;
        }

        if (aPoint0.x > aPoint1.x)
        {
            myDirection.x = -1;
        }
        if (aPoint0.y > aPoint1.y)
        {
            myDirection.y = -1;
        }
        if (aPoint0.z > aPoint1.z)
        {
            myDirection.z = -1;
        }

        if (aPoint0.x == aPoint1.x)
        {
            myDirection.x = 0;
        }
        if (aPoint0.y == aPoint1.y)
        {
            myDirection.y = 0;
        }
        if (aPoint0.z == aPoint1.z)
        {
            myDirection.z = 0;
        }
    }
    template<typename T>
    inline void Ray<T>::InitWithOriginAndDirection(const Vector3<T>& aPoint, const Vector3<T>& aDirection)
    {
        myOrigin = aPoint;
        myDirection = aDirection;
    }
    template<typename T>
    inline const Vector3<T> Ray<T>::GetOrigin() const
    {
        return myOrigin;
    }
    template<typename T>
    inline const Vector3<T> Ray<T>::GetDirection() const
    {
        return myDirection;
    }
    template<typename T>
    inline const bool Ray<T>::IsInFront(const Vector3<T>& aPoint)
    {
        if (myDirection.x == 0 && myDirection.y == 0 && myDirection.z == 0)
        {
            return false;
        }
        Ray<T> aNewRay;
        aNewRay.InitWithOriginAndDirection(myOrigin, aPoint);
        if (aNewRay.myDirection.Dot(myDirection) >= 0)
        {
            return true;
        }
        return false;
    }
}