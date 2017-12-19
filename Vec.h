#ifndef __H_VEC__
#define __H_VEC__

#include "ConstDef.h"
#include <assert.h>

template <typename T = double>
class Vec2
{
public:

    // X ����
    T x;

    // Y ����
    T y;

    // �v�f��
    const int elmcnt = 2;

public:

    // �f�t�H���g�R���X�g���N�^
    Vec2() : x(ZERO), y(ZERO) {}

    // �l�w��̃R���X�g���N�^
    Vec2(const T& _x, const T& _y) : x(_x), y(_y) {}

    // �f�X�g���N�^
    virtual ~Vec2() {}

    // �ŏ��l�̎擾
    T min() const
    {
        return ((this->x < this->y) ? this->x : this->y);
    }

    // �ő�l�̎擾
    T max() const
    {
        return ((this->x > this->y) ? this->x : this->y);
    }

    // ��]
    Vec2<T > rotate(const T& theta, bool bClockwise = true) const
    {
        Vec2<T > rotVec;

        if(bClockwise) {
            rotVec.x = static_cast<T >((::cos(static_cast<double >(theta)) * this->x) + (::sin(static_cast<double >(theta)) * this->y));
            rotVec.y = static_cast<T >((-::sin(static_cast<double >(theta)) * this->x) + (::cos(static_cast<double >(theta)) * this->y));
        } else {
            rotVec.x = static_cast<T >((::cos(static_cast<double >(theta)) * this->x) + (-::sin(static_cast<double >(theta)) * this->y));
            rotVec.y = static_cast<T >((::sin(static_cast<double >(theta)) * this->x) + (::cos(static_cast<double >(theta)) * this->y));
        }

        return rotVec;
    }

    // �����v�Z
    inline T norm() const
    {
        return static_cast<T >(::sqrt(static_cast<double >(this->x * this->x + this->y * this->y)));
    }

    // �����v�Z
    inline T length() const
    {
        return static_cast<T >(::sqrt(static_cast<double >(this->x * this->x + this->y * this->y)));
    }

    // �[���N���A
    inline void zero()
    {
        this->x = this->y = ZERO;
    }

    // ����
    T dot(const Vec2<T >& ref) const
    {
        return (this->x * ref.x + this->y * ref.y);
    }

    // ���K��
    Vec2<T > normalize() const
    {
        T len = length();

        assert(len > ZERO);

        return Vec2<T >(x / len, y / len);
    }

    // ���
    Vec2<T >& operator = (const Vec2<T >& ref)
    {
        this->x = ref.x;
        this->y = ref.y;
        return *this;
    }

    // �������t��
    Vec2<T > operator +() const
    {
        return *this;
    }

    // �������t��
    Vec2<T > operator -() const
    {
        return Vec2<T >(-this->x, -this->y);
    }

    // Vec2 ���m�̉��Z
    Vec2<T > operator +(const Vec2<T >& ref) const
    {
        return Vec2<T >(this->x + ref.x, this->y + ref.y);
    }

    // Vec2 ���m�̌��Z
    Vec2<T > operator -(const Vec2<T >& ref) const
    {
        return Vec2<T >(this->x - ref.x, this->y - ref.y);
    }

    // Vec2 ���m�̏�Z
    Vec2<T > operator *(const Vec2<T >& ref) const
    {
        return Vec2<T >(this->x * ref.x, this->y * ref.y);
    }

    // Vec2 ���m�̏�Z
    Vec2<T > operator /(const Vec2<T >& ref) const
    {
        return Vec2<T >(this->x / ref.x, this->y / ref.y);
    }

    // �萔�̉��Z
    Vec2<T > operator +(const T& s) const
    {
        return Vec2<T >(this->x + s, this->y + s);
    }

    // �萔�̌��Z
    Vec2<T > operator -(const T& s) const
    {
        return Vec2<T >(this->x - s, this->y - s);
    }

    // �萔�̏�Z
    Vec2<T > operator *(const T& s) const
    {
        return Vec2<T >(this->x * s, this->y * s);
    }

    // �萔�̏��Z
    Vec2<T > operator /(const T& s) const
    {
        return Vec2<T >(this->x / s, this->y / s);
    }

    // ���Z
    Vec2<T >& operator +=(const Vec2<T >& ref)
    {
        this->x += ref.x;
        this->y += ref.y;
        return *this;
    }

    // ���Z
    Vec2<T >& operator -=(const Vec2<T >& ref)
    {
        this->x -= ref.x;
        this->y -= ref.y;
        return *this;
    }

    // ��Z
    Vec2<T >& operator *=(const Vec2<T >& ref)
    {
        this->x *= ref.x;
        this->y *= ref.y;
        return *this;
    }

    // ���Z
    Vec2<T >& operator /=(const Vec2<T >& ref)
    {
        this->x /= ref.x;
        this->y /= ref.y;
        return *this;
    }

    // �萔�̉��Z
    Vec2<T >& operator +=(const T& s)
    {
        this->x += s;
        this->y += s;
        return *this;
    }

    // �萔�̌��Z
    Vec2<T >& operator -=(const T& s)
    {
        this->x -= s;
        this->y -= s;
        return *this;
    }

    // �萔�̏�Z
    Vec2<T >& operator *=(const T& s)
    {
        this->x *= s;
        this->y *= s;
        return *this;
    }

    // �萔�̏��Z
    Vec2<T >& operator /=(const T& s)
    {
        this->x /= s;
        this->y /= s;
        return *this;
    }

    // ��r�ix, y �̗����������ɍ����Ƃ��� TRUE�j
    bool operator <(const Vec2<T >& ref)
    {
        return (this->x < ref.x && this->y < ref.y);
    }

    // ��r�ix, y �̗����������ɍ����Ƃ��� TRUE�j
    bool operator >(const Vec2<T >& ref)
    {
        return (this->x > ref.x && this->y > ref.y);
    }

    // ��r�ix, y �̗����������ɍ����Ƃ��� TRUE�j
    bool operator <=(const Vec2<T >& ref)
    {
        return (this->x <= ref.x && this->y <= ref.y);
    }

    // ��r�ix, y �̗����������ɍ����Ƃ��� TRUE�j
    bool operator >=(const Vec2<T >& ref)
    {
        return (this->x >= ref.x && this->y >= ref.y);
    }

    // ��r�ix, y �̗����������ɍ����Ƃ��� TRUE�j
    bool operator ==(const Vec2<T >& ref)
    {
        return (this->x == ref.x && this->y == ref.y);
    }

    // ��r�ix, y �̗����������ɍ����Ƃ��� TRUE�j
    bool operator !=(const Vec2<T >& ref)
    {
        return (this->x != ref.x || this->y != ref.y);
    }

    // �l�̎Q��
    T& operator ()(int idx)
    {
#ifdef _DEBUG
        assert(idx < elmcnt);
#endif
        return ((idx == 0) ? this->x : this->y);
    }

    // �l�̎Q��
    const T& operator ()(int idx) const
    {
#ifdef _DEBUG
        assert(idx < elmcnt);
#endif
        return ((idx == 0) ? this->x : this->y);
    }

    // �l�̎Q��
    T& operator [](int idx)
    {
#ifdef _DEBUG
        assert(idx < elmcnt);
#endif
        return ((idx == 0) ? this->x : this->y);
    }

    // �l�̎Q��
    const T& operator [](int idx) const
    {
#ifdef _DEBUG
        assert(idx < elmcnt);
#endif
        return ((idx == 0) ? this->x : this->y);
    }

    // �l�̑��
    void setXY(const T& _x, const T& _y)
    {
        this->x = _x;
        this->y = _y;
    }

    // �f�o�b�O�p
    void print()
    {
        printf("[x, y] = [%g, %g]\n", this->x, this->y);
    }

};

template class Vec2<int >;
template class Vec2<float >;
template class Vec2<double >;

#endif
