#pragma once
#include "../LinearAlg/Vector2.h"

namespace CommonUtilities
{
    template<typename T>
    class Line
    {
    public:
        Line();
        Line(const Vector2<T>& aPoint0, const Vector2<T>& aPoint1);

        Vector2<T> MyPoint;
        Vector2<T> MyDirection;

        void InitWithTwoPoints(const Vector2<T>& aPoint0, const Vector2<T>& aPoint1);
        void InitWithPointAndNormal(const Vector2<T>& aPoint, const Vector2<T>& aNormal);
        void InitWithPointAndDirection(const Vector2<T>& aPoint, const Vector2<T>& aDirection);

        bool IsInside(const Vector2<T>& aPosition) const;

        Vector2<T> GetDirection() const;
        Vector2<T> GetNormal() const;
    };
    template<typename T>
    inline Line<T>::Line()
    {
        MyPoint = { 0, 0 };
        MyDirection = { 0, 0 };
    }
    template<typename T>
    inline Line<T>::Line(const Vector2<T>& aPoint0, const Vector2<T>& aPoint1)
    {
        MyPoint = aPoint0;
        MyDirection = (aPoint1 - aPoint0);
    }
    template<typename T>
    inline void Line<T>::InitWithTwoPoints(const Vector2<T>& aPoint0, const Vector2<T>& aPoint1)
    {
        MyPoint = aPoint0;
        MyDirection = aPoint1 - aPoint0;
    }
    template<typename T>
    inline void Line<T>::InitWithPointAndNormal(const Vector2<T>& aPoint, const Vector2<T>& aNormal)
    {
        MyPoint = aPoint;
        MyDirection = { aNormal.y, aNormal.x*-1 };
    }
    template<typename T>
    inline void Line<T>::InitWithPointAndDirection(const Vector2<T>& aPoint, const Vector2<T>& aDirection)
    {
        MyPoint = aPoint;
        MyDirection = aDirection;
    }
    template<typename T>
    inline bool Line<T>::IsInside(const Vector2<T>& aPosition) const
    {
        if (MyDirection.LengthSqr() == 0)
        {
            return false;
        }
        if (GetNormal().Dot(aPosition - MyPoint) <= 0)
        {
            return true;
        }
        return false;
    }
    template<typename T>
    inline Vector2<T> Line<T>::GetDirection() const
    {
        return MyDirection;
    }
    template<typename T>
    inline Vector2<T> Line<T>::GetNormal() const
    {
        return Vector2<T>(MyDirection.y *-1, MyDirection.x);
    }
}