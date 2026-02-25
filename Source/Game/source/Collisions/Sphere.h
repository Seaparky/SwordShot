#pragma once
#include "../LinearAlg/Vector3.h"

namespace CommonUtilities
{
    template<typename T>
    class Sphere
    {
    public:
        Sphere();
        Sphere(const Vector3<T>& aCenter, T aRadius);
        
        Vector3<T> myCentre;
        T myRadius;

        void InitWithCenterAndRadius(const Vector3<T>& aCenter, T aRadius);

        Vector3<T> GetCenter() const;
        T GetRadius() const;

        inline bool IsInside(const Vector3<T>& aPoint) const;
    };
    template<typename T>
    inline Sphere<T>::Sphere()
    {
        myCentre = { 0,0,0 };
        myRadius = { 0 };
    }
    template<typename T>
    inline Sphere<T>::Sphere(const Vector3<T>& aCenter, T aRadius)
    {
        myCentre = aCenter;
        myRadius = aRadius;
    }
    template<typename T>
    inline void Sphere<T>::InitWithCenterAndRadius(const Vector3<T>& aCenter, T aRadius)
    {
        myCentre = aCenter;
        myRadius = aRadius;
    }
    template<typename T>
    inline Vector3<T> Sphere<T>::GetCenter() const
    {
        return Vector3<T>(myCentre);
    }
    template<typename T>
    inline T Sphere<T>::GetRadius() const
    {
        return myRadius;
    }
    template<typename T>
    inline bool Sphere<T>::IsInside(const Vector3<T>& aPoint) const
    {
        Vector3<T> vectorBetween = aPoint - myCentre;
        T distanceBetween = vectorBetween.Length();
        if (distanceBetween <= myRadius)
        {
            return true;
        }
        return false;
    }
}