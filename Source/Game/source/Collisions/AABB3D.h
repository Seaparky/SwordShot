#pragma once
#include "../LinearAlg/Vector3.h"

namespace CommonUtilities
{
    template<typename T>
    class AABB3D
    {
    public:
        AABB3D();
        AABB3D(const Vector3<T>& aMin, const Vector3<T>& aMax);

        void InitWithMinAndMax(const Vector3<T>& aMin, const Vector3<T>& aMax);
        
        Vector3<T> myMax;
        Vector3<T> myMin;


        Vector3<T> GetMin() const;
        Vector3<T> GetMax() const;

        inline bool IsInside(const Vector3<T>& aPoint) const;
    };
    template<typename T>
    inline AABB3D<T>::AABB3D()
    {
        myMax = { 0,0,0 };
        myMin = { 0,0,0 };
    }
    template<typename T>
    inline AABB3D<T>::AABB3D(const Vector3<T>& aMin, const Vector3<T>& aMax)
    {
        myMax = aMax;
        myMin = aMin;
    }
    template<typename T>
    inline void AABB3D<T>::InitWithMinAndMax(const Vector3<T>& aMin, const Vector3<T>& aMax)
    {
        myMax = aMax;
        myMin = aMin;
    }
    template<typename T>
    inline Vector3<T> AABB3D<T>::GetMin() const
    {
        return myMin;
    }
    template<typename T>
    inline Vector3<T> AABB3D<T>::GetMax() const
    {
        return myMax;
    }
    template<typename T>
    inline bool AABB3D<T>::IsInside(const Vector3<T>& aPoint) const
    {
        if (myMax.x < aPoint.x)
        {
            return false;
        }
        if (myMin.x > aPoint.x)
        {
            return false;
        }
        if (myMax.y < aPoint.y)
        {
            return false;
        }
        if (myMin.y > aPoint.y) {
            return false;
        }
        if (myMax.z < aPoint.z)
        {
            return false;
        }
        if (myMin.z > aPoint.z) {
            return false;
        }
        return true;
    }
}