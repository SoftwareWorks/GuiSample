#ifndef __H_IMAGE_OP__
#define __H_IMAGE_OP__

#include "Vec.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <vector>

class ImageSize
{
private:

    // 幅
    int width;

    // 高さ
    int height;

    // 要素数
    int elmcnt;

public:

    ImageSize() : width(0), height(0), elmcnt(0) {}

    ImageSize(int _width, int _height) : width(_width), height(_height) 
    {
#ifdef _DEBUG
        assert(_width >= 0 && _height >= 0);
#endif
    }

    virtual ~ImageSize() {}

    // 最小値の取得
    int min() const
    {
        return ((this->width < this->height) ? this->width : this->height);
    }

    // 最大値の取得
    int max() const
    {
        return ((this->width > this->height) ? this->width : this->height);
    }

    // ゼロに初期化
    inline void zero()
    {
        this->width = this->height = this->elmcnt = 0;
    }

    // ImageSize による代入
    ImageSize& operator =(const ImageSize& ref)
    {
        this->width = ref.width;
        this->height = ref.height;
        this->elmcnt = this->width * this->height;
        return *this;
    }

    // Vec2 による代入
    ImageSize& operator =(const Vec2<int >& ref)
    {
        this->width = ref.x;
        this->height = ref.y;
        this->elmcnt = this->width * this->height;
        return *this;
    }

    // 比較（x, y の両方が条件に合うときに TRUE）
    bool operator <(const ImageSize& ref)
    {
        return (this->width < ref.width && this->height < ref.height);
    }

    // 比較（x, y の両方が条件に合うときに TRUE）
    bool operator >(const ImageSize& ref)
    {
        return (this->width > ref.width && this->height > ref.height);
    }

    // 比較（x, y の両方が条件に合うときに TRUE）
    bool operator <=(const ImageSize& ref)
    {
        return (this->width <= ref.width && this->height <= ref.height);
    }

    // 比較（x, y の両方が条件に合うときに TRUE）
    bool operator >=(const ImageSize& ref)
    {
        return (this->width >= ref.width && this->height >= ref.height);
    }

    // 比較（x, y の両方が条件に合うときに TRUE）
    bool operator ==(const ImageSize& ref)
    {
        return (this->width == ref.width && this->height == ref.height);
    }

    // 比較（x, y の両方が条件に合うときに TRUE）
    bool operator !=(const ImageSize& ref)
    {
        return (this->width != ref.width || this->height != ref.height);
    }

    // 値の設定
    inline void setSize(const int& _width, const int& _height)
    {
#ifdef _DEBUG
        assert(_width >= 0 && _height >= 0);
#endif
        this->width = _width;
        this->height = _height;
        this->elmcnt = this->width * this->height;
    }

    // 幅の取得
    const int& getWidth() const
    {
        return this->width;
    }

    // 高さの取得
    const int& getHeight() const
    {
        return this->height;
    }

    // 要素数の取得
    const int& getElmNum() const
    {
        return this->elmcnt;
    }

    // デバッグ用
    void print() const
    {
        printf("[x, y] = [%d, %d]\n", this->width, this->height);
    }

};

#define IMG_DEFINE(CLASS_NAME_, NAME_) \
    typedef class CLASS_NAME_<unsigned char> NAME_ ## 8U; \
    typedef class CLASS_NAME_<unsigned short> NAME_ ## 16U; \
    typedef class CLASS_NAME_<unsigned int> NAME_ ## 32U; \
    typedef class CLASS_NAME_<float > NAME_ ## 32F; \
    typedef class CLASS_NAME_<double > NAME_ ## 64F;

#define IMG_TEMPLATE_DEFINE(CLASS_NAME_) \
    template class CLASS_NAME_<unsigned char >; \
    template class CLASS_NAME_<short >; \
    template class CLASS_NAME_<unsigned short >; \
    template class CLASS_NAME_<int >; \
    template class CLASS_NAME_<unsigned int >; \
    template class CLASS_NAME_<float >; \
    template class CLASS_NAME_<double >; \

template <typename T = double>
class ImageBase
{

public:

    // 下限値
    T lowerLimit;

protected:

    // データ格納領域
    T* data;

    // 画像サイズ
    ImageSize size;


public:

    // デフォルトコンストラクタ
    ImageBase();

    // サイズ指定のコンストラクタ
    ImageBase(int width, int height);

    // サイズ指定のコンストラクタ
    ImageBase(const ImageSize& imgSize);

    // サイズ指定のコンストラクタ
    ImageBase(const ImageBase<T >& ref);

    // デストラクタ
    virtual ~ImageBase();

    // 画像を定数で初期化
    void init();

    // 画像をゼロで初期化
    void zero();

    // 画像サイズ変更（メモリ確保のみ）
    bool resize(int width, int height);

    // 画像サイズ変更（メモリ確保のみ）
    bool resize(const ImageSize& imgSize);

    // バイナリ画像の読込み
    bool loadBinaryImage(const char* filename, const ImageSize& imgSize);

    // バイナリ画像の書き込み
    bool saveBinaryImage(const char* filename) const;

    // アスキー画像の読込み
    bool loadAsciiImage(const char* filename, const ImageSize& imgSize);

    // アスキー画像の書き込み
    bool saveAsciiImage(const char* filename) const;

    // 画像解放
    void clear()
    { 
        if(data != nullptr)
        { 
            size.setSize(0, 0);
            delete[] data;
        }
    }

    // 画像範囲内かどうか
    bool isIn(int x, int y) const
    {
        return ((x >= 0 && y >= 0) && (x < size.getWidth() && y < size.getHeight()));
    }

    // 実体のポインタ取得
    const T* getPtr() const
    {
        return &data[0];
    }

    // 画像サイズの取得
    ImageSize& getSize()
    {
        return size;
    }

    // 画像サイズの取得
    const ImageSize& getSize() const
    { 
        return size;
    }

    // 画像幅の取得
    const int& getWidth() const
    {
        return size.getWidth();
    }

    // 画像高さの取得
    const int& getHeight() const
    {
        return size.getHeight();
    }

    // 要素数の取得
    const int& getElmNum() const
    {
        return size.getElmNum();
    }

    // 要素アクセス
    T& at(int idx)
    { 
#ifdef _DEBUG
        assert(idx < size.getElmNum());
#endif
        return data[idx];
    }

    // 要素アクセス
    const T& at(int idx) const
    { 
#ifdef _DEBUG
        assert(idx < size.getElmNum());
#endif
        return data[idx];
    }

    // 要素アクセス
    T& operator [](int idx)
    { 
#ifdef _DEBUG
        assert(idx < size.getElmNum());
#endif
        return data[idx];
    }

    // 要素アクセス
    const T& operator [](int idx) const
    { 
#ifdef _DEBUG
        assert(idx < size.getElmNum());
#endif
        return data[idx];
    }

    // 要素アクセス
    T& operator ()(int i, int j)
    {
#ifdef _DEBUG
        assert((i * size.getWidth() + j) < size.getElmNum());
#endif
        return data[i * size.getWidth() + j];
    }

    // 要素アクセス
    const T& operator ()(int i, int j) const
    {
#ifdef _DEBUG
        assert((i * size.getWidth() + j) < size.getElmNum());
#endif
        return data[i * size.getWidth() + j];
    }

    // 画像のコピー
    const ImageBase<T >& operator =(const ImageBase<T >& ref)
    {
        resize(ref.getSize());
        this->lowerLimit = ref.lowerLimit;
        for(int pix = 0; pix < getElmNum(); pix++) {
            this->data[pix] = ref[pix];
        }
        return *this;
    }

};

IMG_DEFINE(ImageBase, Image)

template <typename T = double>
class ReconImage : public ImageBase<T >
{

public:

    // デフォルトコンストラクタ
    ReconImage();

    // サイズ指定のコンストラクタ
    ReconImage(int width, int height);

    // サイズ指定のコンストラクタ
    ReconImage(const ImageSize& imgSize);

    // デストラクタ
    virtual ~ReconImage();

    // 画像サイズ変更（メモリ確保のみ）
    bool resize(int width, int height);

    // 画像サイズ変更（メモリ確保のみ）
    bool resize(const ImageSize& imgSize);

    // バイナリ画像の読込み
    bool loadBinaryImage(const char* filename, const ImageSize& imgSize);

    // アスキー画像の読込み
    bool loadAsciiImage(const char* filename, const ImageSize& imgSize);

    // 再構成領域かどうか
    bool isReconRegion(const int& x, const int& y) const;

    // 画像解放
    void clear()
    {
        if(data != nullptr) {
            size.setSize(0, 0);
            delete[] data;
        }
        radius = ZERO;
    }

    // 画像のコピー（ImageBase）
    const ReconImage<T >& operator =(const ImageBase<T >& ref)
    {
        resize(ref.getSize());
        this->lowerLimit = ref.lowerLimit;
        for(int pix = 0; pix < getElmNum(); pix++) {
            this->data[pix] = ref[pix];
        }
        return *this;
    }

    // 画像のコピー（ReconImage）
    const ReconImage<T >& operator =(const ReconImage<T >& ref)
    {
        resize(ref.getSize());
        this->lowerLimit = ref.lowerLimit;
        for(int pix = 0; pix < getElmNum(); pix++) {
            this->data[pix] = ref[pix];
        }
        return *this;
    }

private:

    // 画像中心（X 座標）
    T x0;

    // 画像中心（Y 座標）
    T y0;

    // 再構成半径
    T radius;

};

IMG_DEFINE(ReconImage, RImage)


#endif
