#ifndef __H_VEC__
#define __H_VEC__

#include "ConstDef.h"
#include <assert.h>

template <typename T = double>
class Vec2
{
public:

    // X 成分
    T x;

    // Y 成分
    T y;

    // 要素数
    const int elmcnt = 2;

public:

    // デフォルトコンストラクタ
    Vec2() : x(ZERO), y(ZERO) {}

    // 値指定のコンストラクタ
    Vec2(const T& _x, const T& _y) : x(_x), y(_y) {}

    // デストラクタ
    virtual ~Vec2() {}

    // 最小値の取得
    T min() const
    {
        return ((this->x < this->y) ? this->x : this->y);
    }

    // 最大値の取得
    T max() const
    {
        return ((this->x > this->y) ? this->x : this->y);
    }

    // 回転
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

    // 距離計算
    inline T norm() const
    {
        return static_cast<T >(::sqrt(static_cast<double >(this->x * this->x + this->y * this->y)));
    }

    // 距離計算
    inline T length() const
    {
        return static_cast<T >(::sqrt(static_cast<double >(this->x * this->x + this->y * this->y)));
    }

    // ゼロクリア
    inline void zero()
    {
        this->x = this->y = ZERO;
    }

    // 内積
    T dot(const Vec2<T >& ref) const
    {
        return (this->x * ref.x + this->y * ref.y);
    }

    // 正規化
    Vec2<T > normalize() const
    {
        T len = length();

        assert(len > ZERO);

        return Vec2<T >(x / len, y / len);
    }

    // 代入
    Vec2<T >& operator = (const Vec2<T >& ref)
    {
        this->x = ref.x;
        this->y = ref.y;
        return *this;
    }

    // 正符号付加
    Vec2<T > operator +() const
    {
        return *this;
    }

    // 負符号付加
    Vec2<T > operator -() const
    {
        return Vec2<T >(-this->x, -this->y);
    }

    // Vec2 同士の加算
    Vec2<T > operator +(const Vec2<T >& ref) const
    {
        return Vec2<T >(this->x + ref.x, this->y + ref.y);
    }

    // Vec2 同士の減算
    Vec2<T > operator -(const Vec2<T >& ref) const
    {
        return Vec2<T >(this->x - ref.x, this->y - ref.y);
    }

    // Vec2 同士の乗算
    Vec2<T > operator *(const Vec2<T >& ref) const
    {
        return Vec2<T >(this->x * ref.x, this->y * ref.y);
    }

    // Vec2 同士の乗算
    Vec2<T > operator /(const Vec2<T >& ref) const
    {
        return Vec2<T >(this->x / ref.x, this->y / ref.y);
    }

    // 定数の加算
    Vec2<T > operator +(const T& s) const
    {
        return Vec2<T >(this->x + s, this->y + s);
    }

    // 定数の減算
    Vec2<T > operator -(const T& s) const
    {
        return Vec2<T >(this->x - s, this->y - s);
    }

    // 定数の乗算
    Vec2<T > operator *(const T& s) const
    {
        return Vec2<T >(this->x * s, this->y * s);
    }

    // 定数の除算
    Vec2<T > operator /(const T& s) const
    {
        return Vec2<T >(this->x / s, this->y / s);
    }

    // 加算
    Vec2<T >& operator +=(const Vec2<T >& ref)
    {
        this->x += ref.x;
        this->y += ref.y;
        return *this;
    }

    // 減算
    Vec2<T >& operator -=(const Vec2<T >& ref)
    {
        this->x -= ref.x;
        this->y -= ref.y;
        return *this;
    }

    // 乗算
    Vec2<T >& operator *=(const Vec2<T >& ref)
    {
        this->x *= ref.x;
        this->y *= ref.y;
        return *this;
    }

    // 除算
    Vec2<T >& operator /=(const Vec2<T >& ref)
    {
        this->x /= ref.x;
        this->y /= ref.y;
        return *this;
    }

    // 定数の加算
    Vec2<T >& operator +=(const T& s)
    {
        this->x += s;
        this->y += s;
        return *this;
    }

    // 定数の減算
    Vec2<T >& operator -=(const T& s)
    {
        this->x -= s;
        this->y -= s;
        return *this;
    }

    // 定数の乗算
    Vec2<T >& operator *=(const T& s)
    {
        this->x *= s;
        this->y *= s;
        return *this;
    }

    // 定数の除算
    Vec2<T >& operator /=(const T& s)
    {
        this->x /= s;
        this->y /= s;
        return *this;
    }

    // 比較（x, y の両方が条件に合うときに TRUE）
    bool operator <(const Vec2<T >& ref)
    {
        return (this->x < ref.x && this->y < ref.y);
    }

    // 比較（x, y の両方が条件に合うときに TRUE）
    bool operator >(const Vec2<T >& ref)
    {
        return (this->x > ref.x && this->y > ref.y);
    }

    // 比較（x, y の両方が条件に合うときに TRUE）
    bool operator <=(const Vec2<T >& ref)
    {
        return (this->x <= ref.x && this->y <= ref.y);
    }

    // 比較（x, y の両方が条件に合うときに TRUE）
    bool operator >=(const Vec2<T >& ref)
    {
        return (this->x >= ref.x && this->y >= ref.y);
    }

    // 比較（x, y の両方が条件に合うときに TRUE）
    bool operator ==(const Vec2<T >& ref)
    {
        return (this->x == ref.x && this->y == ref.y);
    }

    // 比較（x, y の両方が条件に合うときに TRUE）
    bool operator !=(const Vec2<T >& ref)
    {
        return (this->x != ref.x || this->y != ref.y);
    }

    // 値の参照
    T& operator ()(int idx)
    {
#ifdef _DEBUG
        assert(idx < elmcnt);
#endif
        return ((idx == 0) ? this->x : this->y);
    }

    // 値の参照
    const T& operator ()(int idx) const
    {
#ifdef _DEBUG
        assert(idx < elmcnt);
#endif
        return ((idx == 0) ? this->x : this->y);
    }

    // 値の参照
    T& operator [](int idx)
    {
#ifdef _DEBUG
        assert(idx < elmcnt);
#endif
        return ((idx == 0) ? this->x : this->y);
    }

    // 値の参照
    const T& operator [](int idx) const
    {
#ifdef _DEBUG
        assert(idx < elmcnt);
#endif
        return ((idx == 0) ? this->x : this->y);
    }

    // 値の代入
    void setXY(const T& _x, const T& _y)
    {
        this->x = _x;
        this->y = _y;
    }

    // デバッグ用
    void print()
    {
        printf("[x, y] = [%g, %g]\n", this->x, this->y);
    }

};

template class Vec2<int >;
template class Vec2<float >;
template class Vec2<double >;

#endif
