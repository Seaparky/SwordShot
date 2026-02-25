#pragma once
#include "Vector4.h"
#include <cmath>
#include <algorithm>

using namespace CommonUtilities;

namespace CommonUtilities
{

	template<typename T>
	class Matrix4x4
	{
	public:
		union
		{
			struct
			{
				Vector4<T> myRow1;
				Vector4<T> myRow2;
				Vector4<T> myRow3;
				Vector4<T> myRow4;
			};
			struct
			{
				T m11; // Row 1
				T m21;
				T m31;
				T m41;

				T m12; // Row 2
				T m22;
				T m32;
				T m42;

				T m13; // Row 3
				T m23;
				T m33;
				T m43;

				T m14; // Row 4
				T m24;
				T m34;
				T m44;
			};
		};


	public:
		Matrix4x4(); // Create as identity
		Matrix4x4(Vector4<T> aRow1, Vector4<T> aRow2, Vector4<T> aRow3, Vector4<T> aRow4);
		Matrix4x4(const Matrix4x4&) = default;
		~Matrix4x4() {}

		Matrix4x4<T> CreatePerspective(T FoV, T aspectRatio, T near, T far);

		Matrix4x4<T> GetTranspose() const; // "Flip around identity"
		Matrix4x4<T> GetRotationInverse() const; // Only valid if this is a rotation only matrix
		Matrix4x4<T> GetScaleInverse() const; // Only valid if this is a scale only matrix
		Matrix4x4<T> GetTranslationInverse() const; // Only valid if this is a translation only matrix

		Matrix4x4<T> operator*(const Matrix4x4& aOther) const;
		Matrix4x4<T> operator*=(const Matrix4x4& aOther);
	};
	template<typename T>
	inline Matrix4x4<T>::Matrix4x4()
	{
		myRow1 = { 1,0,0,0 };
		myRow2 = { 0,1,0,0 };
		myRow3 = { 0,0,1,0 };
		myRow4 = { 0,0,0,1 };
	}
	template<typename T>
	inline Matrix4x4<T>::Matrix4x4(Vector4<T> aRow1, Vector4<T> aRow2, Vector4<T> aRow3, Vector4<T> aRow4)
	{
		myRow1 = aRow1;
		myRow2 = aRow2;
		myRow3 = aRow3;
		myRow4 = aRow4;
	}
	template<typename T>
	inline Matrix4x4<T> Matrix4x4<T>::CreatePerspective(T FoV, T aspectRatio, T near, T far)
	{
		T FoVX = (1 / tanf(static_cast<float>(FoV / 2)));
		T FoVY = (1 / aspectRatio * tanf(static_cast<float>(FoV / 2)));

		T DeapthNormalilse = (far / (far - near));
		T DeapthNearOffset = ((-near * far) / (far - near));

		Vector4<T> rowOne = { FoVX,0,0,0 };
		Vector4<T> rowTwo = { 0,FoVY,0,0 };
		Vector4<T> rowThree = { 0,0,DeapthNormalilse,1 };
		Vector4<T> rowFour = { 0,0,DeapthNearOffset,0 };

		return Matrix4x4<T>(rowOne, rowTwo, rowThree, rowFour);
	}
	template<typename T>
	inline Matrix4x4<T> Matrix4x4<T>::GetTranspose() const
	{
		Matrix4x4<T> m = Matrix4x4<T>{ *this };

		std::swap(m.m21, m.m12);
		std::swap(m.m13, m.m31);
		std::swap(m.m14, m.m41);
		std::swap(m.m32, m.m23);
		std::swap(m.m24, m.m42);
		std::swap(m.m34, m.m43);

		return m;
	}
	template<typename T>
	inline Matrix4x4<T> Matrix4x4<T>::GetRotationInverse() const
	{
		Matrix4x4<T> m = Matrix4x4<T>{ *this };

		m.myRow1 = { 1, 0, 0, -m.m41 };
		m.myRow2 = { 0, 1, 0, -m.m42 };
		m.myRow3 = { 0, 0, 1, -m.m43 };
		m.myRow4 = { 0, 0, 0, 1 };

		return m;
	}
	template<typename T>
	inline Matrix4x4<T> Matrix4x4<T>::GetScaleInverse() const
	{
		Matrix4x4<T> m = Matrix4x4<T>{ *this };

		m.m11 = 1 / m.m11;
		m.m22 = 1 / m.m22;
		m.m33 = 1 / m.m33;

		m.m12 = 0;
		m.m13 = 0;
		m.m14 = 0;

		m.m21 = 0;
		m.m23 = 0;
		m.m24 = 0;

		m.m31 = 0;
		m.m32 = 0;
		m.m34 = 0;

		m.m41 = 0;
		m.m42 = 0;
		m.m43 = 0;
		m.m44 = 1;

		return m;
	}
	template<typename T>
	inline Matrix4x4<T> Matrix4x4<T>::GetTranslationInverse() const
	{
		Matrix4x4<T> m = Matrix4x4<T>{ *this };

		m.myRow1 = { 1, 0, 0, -m.m41 };
		m.myRow2 = { 0, 1, 0, -m.m42 };
		m.myRow3 = { 0, 0, 1, -m.m43 };
		m.myRow4 = { 0, 0, 0, 1 };

		return m;
	}
	template<typename T>
	inline Matrix4x4<T> Matrix4x4<T>::operator*(const Matrix4x4& aOther) const
	{
		Matrix4x4<T> m = Matrix4x4<T>{ *this };

		m.m11 = aOther.myRow1.Dot(Vector4<T>{ m11, m12, m13, m14 });
		m.m12 = aOther.myRow1.Dot(Vector4<T>{ m21, m22, m23, m24 });
		m.m13 = aOther.myRow1.Dot(Vector4<T>{ m31, m32, m33, m34 });
		m.m14 = aOther.myRow4.Dot(Vector4<T>{ m41, m42, m43, m44 });

		m.m21 = aOther.myRow2.Dot(Vector4<T>{ m11, m12, m13, m14 });
		m.m22 = aOther.myRow2.Dot(Vector4<T>{ m21, m22, m23, m24 });
		m.m23 = aOther.myRow2.Dot(Vector4<T>{ m31, m32, m33, m34 });
		m.m24 = aOther.myRow4.Dot(Vector4<T>{ m41, m42, m43, m44 });

		m.m31 = aOther.myRow3.Dot(Vector4<T>{ m11, m12, m13, m14 });
		m.m32 = aOther.myRow3.Dot(Vector4<T>{ m21, m22, m23, m24 });
		m.m33 = aOther.myRow3.Dot(Vector4<T>{ m31, m32, m33, m34 });
		m.m34 = aOther.myRow4.Dot(Vector4<T>{ m41, m42, m43, m44 });

		m.m41 = aOther.myRow4.Dot(Vector4<T>{ m11, m12, m13, m14 });
		m.m42 = aOther.myRow4.Dot(Vector4<T>{ m21, m22, m23, m24 });
		m.m43 = aOther.myRow4.Dot(Vector4<T>{ m31, m32, m33, m34 });
		m.m44 = aOther.myRow4.Dot(Vector4<T>{ m41, m42, m43, m44 });

		return m;
	}
	template<typename T>
	inline Matrix4x4<T> Matrix4x4<T>::operator*=(const Matrix4x4& aOther)
	{
		Matrix4x4<T> m = Matrix4x4<T>{ *this };

		m = m * aOther;
		return m;
	}

	template<typename T>
	Vector4<T> operator*=(const Vector4<T>& aVector, const Matrix4x4<T>& aOther)
	{
		Vector4<T> m = aVector;

		m = m * aOther;
		return m;

	}

	template<typename T>
	Vector4<T> operator*(const Vector4<T>& aVector, const Matrix4x4<T>& aOther)
	{
		Vector4<T> result;

		result.x = (aVector.x * aOther.m11 + aVector.y * aOther.m12 + aVector.z * aOther.m13 + aVector.w * aOther.m14);
		result.y = (aVector.x * aOther.m21 + aVector.y * aOther.m22 + aVector.z * aOther.m23 + aVector.w * aOther.m24);
		result.z = (aVector.x * aOther.m31 + aVector.y * aOther.m32 + aVector.z * aOther.m33 + aVector.w * aOther.m34);
		result.w = (aVector.x * aOther.m41 + aVector.y * aOther.m42 + aVector.z * aOther.m43 + aVector.w * aOther.m44);

		return result;
	}

}