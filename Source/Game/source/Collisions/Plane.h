#pragma once
#include "../LinearAlg/Vector3.h"

namespace CommonUtilities
{
    template<typename T>
    class Plane
    {
    public:
        Plane();
        Plane(const Vector3<T>& aPoint, const Vector3<T>& aNormal);
        Plane(const Vector3<T>& aPoint0, const Vector3<T>& aPoint1, const Vector3<T>& aPoint2);

        Vector3<T> MyPoint;
        Vector3<T> MyNormal;

        void InitWith3Points(const Vector3<T>& aPoint0, const Vector3<T>& aPoint1, const Vector3<T>& aPoint2);
        void InitWithPointAndNormal(const Vector3<T>& aPoint, const Vector3<T>& aNormal);

        bool IsInside(const Vector3<T>& aPosition) const;

        Vector3<T> GetNormal() const;
    };
    template<typename T>
    inline Plane<T>::Plane()
    {
        MyPoint = { 0,0,0 };
        MyNormal = { 0,0,0 };
    }
    template<typename T>
    inline Plane<T>::Plane(const Vector3<T>& aPoint, const Vector3<T>& aNormal)
    {
        MyPoint = aPoint;
        MyNormal = aNormal;
    }
    template<typename T>
    inline Plane<T>::Plane(const Vector3<T>& aPoint0, const Vector3<T>& aPoint1, const Vector3<T>& aPoint2)
    {
        MyPoint = aPoint0;
        MyNormal = ((aPoint1 - aPoint0).Cross(aPoint2 - aPoint0)).GetNormalized();
    }
    template<typename T>
    inline void Plane<T>::InitWith3Points(const Vector3<T>& aPoint0, const Vector3<T>& aPoint1, const Vector3<T>& aPoint2)
    {
        MyPoint = aPoint0;
        MyNormal = ((aPoint1 - aPoint0).Cross(aPoint2 - aPoint0)).GetNormalized();
    }
    template<typename T>
    inline void Plane<T>::InitWithPointAndNormal(const Vector3<T>& aPoint, const Vector3<T>& aNormal)
    {
        MyPoint = aPoint;
        MyNormal = aNormal;
    }
    template<typename T>
    inline bool Plane<T>::IsInside(const Vector3<T>& aPosition) const
    {
        if (MyNormal.LengthSqr() == 0)
        {
            return false;
        }
        if ((aPosition - MyPoint).Dot(MyNormal) <= 0)
        {
            return true;
        }
        return false;
    }
    template<typename T>
    inline Vector3<T> Plane<T>::GetNormal() const
    {
        return MyNormal;
    }
}