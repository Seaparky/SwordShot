#pragma once
#include "Line.h"
#include "../LinearAlg/Vector2.h"
#include <vector>

namespace CommonUtilities
{
    template <typename T>
    class LineVolume
    {
    public:
        LineVolume();
        LineVolume(const std::vector<Line<T>>& aLineList);

        std::vector<Line<T>> MyVolume;

        void AddLine(const Line<T>& aLine);

        bool IsInside(const Vector2<T> aPoint) const;
    };
    template<typename T>
    inline LineVolume<T>::LineVolume()
    {

    }
    template<typename T>
    inline LineVolume<T>::LineVolume(const std::vector<Line<T>>& aLineList)
    {
        MyVolume = aLineList;
    }
    template<typename T>
    inline void LineVolume<T>::AddLine(const Line<T>& aLine)
    {
        MyVolume.push_back(aLine);
    }
    template<typename T>
    inline bool LineVolume<T>::IsInside(const Vector2<T> aPoint) const
    {
        for (size_t i = 0; i < MyVolume.size(); i++)
        {
            if (MyVolume[i].IsInside(aPoint) == false)
            {
                return false;
            }
        }
        return true;
    }
}