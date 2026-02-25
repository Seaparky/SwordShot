#pragma once
#include "Plane.h"
#include "../LinearAlg/Vector3.h"
#include <vector>

namespace CommonUtilities
{
    template <typename T>
    class PlaneVolume
    {
    public:
        PlaneVolume();
        PlaneVolume(const std::vector<Plane<T>>& aPlaneList);

        std::vector<Plane<T>> MyVolume;

        void AddPlane(const Plane<T>& aPlane);

        bool IsInside(const Vector3<T> aPoint) const;
    };
    template<typename T>
    inline PlaneVolume<T>::PlaneVolume()
    {
    }
    template<typename T>
    inline PlaneVolume<T>::PlaneVolume(const std::vector<Plane<T>>& aPlaneList)
    {
        MyVolume = aPlaneList;
    }
    template<typename T>
    inline void PlaneVolume<T>::AddPlane(const Plane<T>& aPlane)
    {
        MyVolume.push_back(aPlane);
    }
    template<typename T>
    inline bool PlaneVolume<T>::IsInside(const Vector3<T> aPoint) const
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