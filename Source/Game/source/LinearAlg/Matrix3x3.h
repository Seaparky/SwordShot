#pragma once
#include "Vector3.h"
#include <cmath>
#include <algorithm>

using namespace CommonUtilities;

namespace CommonUtilities
{

	template <typename T>
	class Matrix3x3
	{
	public:
		union
		{
			struct
			{
				Vector3<T> myRow1;
				Vector3<T> myRow2;
				Vector3<T> myRow3;


			};
			struct
			{
				T m11;
				T m21;
				T m31;
				T m12;
				T m22;
				T m32;
				T m13;
				T m23;
				T m33;
			};
		};


	public:
		Matrix3x3();
		Matrix3x3(Vector3<T> aRow1, Vector3<T> aRow2, Vector3<T> aRow3);
		Matrix3x3(const Matrix3x3&) = default;
		~Matrix3x3() {}

		static Matrix3x3<T> CreateRotationX(T rotation);
		static Matrix3x3<T> CreateRotationY(T rotation);
		static Matrix3x3<T> CreateRotationZ(T rotation);

		Matrix3x3<T>& operator*=(const Matrix3x3& aOther);
		Matrix3x3<T> operator*(const Matrix3x3& aOther) const;


		Matrix3x3<T> GetTranspose() const;
	};

	template<typename T>
	inline Matrix3x3<T>::Matrix3x3()
	{
		myRow1 = { 1,0,0 };
		myRow2 = { 0,1,0 };
		myRow3 = { 0,0,1 };
	}

	template<typename T>
	inline Matrix3x3<T>::Matrix3x3(Vector3<T> aRow1, Vector3<T> aRow2, Vector3<T> aRow3)
	{
		myRow1 = aRow1;
		myRow2 = aRow2;
		myRow3 = aRow3;
	}

	template<typename T>
	inline Matrix3x3<T> Matrix3x3<T>::CreateRotationX(T rotation)
	{
		Vector3<T> line1 = { 1,0,0 };
		Vector3<T> line2 = (0, cos(rotation), sin(rotation));
		Vector3<T> line3 = (0, -sin(rotation), cos(rotation));

		return Matrix3x3(line1, line2, line3);
	}

	template<typename T>
	inline Matrix3x3<T> Matrix3x3<T>::CreateRotationY(T rotation)
	{
		Vector3<T> line1 = { cos(rotation),0,-sin(rotation) };
		Vector3<T> line2 = (0, 1, 0);
		Vector3<T> line3 = (sin(rotation), 0, cos(rotation));

		return Matrix3x3(line1, line2, line3);

	}
	template<typename T>
	inline Matrix3x3<T> Matrix3x3<T>::CreateRotationZ(T rotation)
	{
		Vector3<T> line1 = { cos(rotation),sin(rotation),0.0f };
		Vector3<T> line2 = { -sin(rotation), cos(rotation), 0.0f };
		Vector3<T> line3 = { 0.0f, 0.0f, 1.0f };

		return Matrix3x3(line1, line2, line3);
	}
	template<typename T>
	inline Matrix3x3<T>& Matrix3x3<T>::operator*=(const Matrix3x3& aOther)
	{
		Matrix3x3<T> m = Matrix3x3<T>(*this);

		m = m * aOther;
		return m;
	}
	template<typename T>
	inline Matrix3x3<T> Matrix3x3<T>::operator*(const Matrix3x3& aOther) const
	{
		Matrix3x3<T> m = Matrix3x3<T>(*this);

		m.m11 = aOther.myRow1.Dot(Vector3<T>{ m11, m12, m13 });
		m.m12 = aOther.myRow1.Dot(Vector3<T>{ m21, m22, m23 });
		m.m13 = aOther.myRow1.Dot(Vector3<T>{ m31, m32, m33 });

		m.m21 = aOther.myRow2.Dot(Vector3<T>{ m11, m12, m13 });
		m.m22 = aOther.myRow2.Dot(Vector3<T>{ m21, m22, m23 });
		m.m23 = aOther.myRow2.Dot(Vector3<T>{ m31, m32, m33 });

		m.m31 = aOther.myRow3.Dot(Vector3<T>{ m11, m12, m13 });
		m.m32 = aOther.myRow3.Dot(Vector3<T>{ m21, m22, m23 });
		m.m33 = aOther.myRow3.Dot(Vector3<T>{ m31, m32, m33 });

		return m;
	}

	template<typename T>
	Vector3<T> operator*=(const Vector3<T>& aVector, const Matrix3x3<T>& aOther)
	{
		Vector3<T> m = aVector;

		m = m * aOther;
		return m;

	}

	template<typename T>
	Vector3<T> operator*(const Vector3<T>& aVector, const Matrix3x3<T>& aOther)
	{
		Vector3<T> result;
		float fX = aVector.x;
		float fY = aVector.y;
		float fZ = aVector.z;

		result.x = (fX * aOther.m11 + fY * aOther.m12 + fZ * aOther.m13);
		result.y = (fX * aOther.m21 + fY * aOther.m22 + fZ * aOther.m23);
		result.z = (fX * aOther.m31 + fY * aOther.m32 + fZ * aOther.m33);

		return result;
	}

	template<typename T>
	inline Matrix3x3<T> Matrix3x3<T>::GetTranspose() const
	{
		Matrix3x3<T> m = Matrix3x3<T>{ *this };
		std::swap(m.m21, m.m12);
		std::swap(m.m13, m.m31);
		std::swap(m.m32, m.m23);

		return m;
	}
}
