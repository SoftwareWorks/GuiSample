#include "ImageOp.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

template <typename T>
ImageBase<T >::ImageBase() : data(nullptr), lowerLimit(ZERO)
{
}

template <typename T>
ImageBase<T >::ImageBase(int width, int height)
{
    ImageBase();
    resize(width, height);
}

template <typename T>
ImageBase<T >::ImageBase(const ImageSize& imgSize)
{
    ImageBase();
    resize(imgSize);
}

template <typename T>
ImageBase<T >::ImageBase(const ImageBase<T >& ref)
{
    resize(ref.getWidth(), ref.getHeight());
    this->lowerLimit = ref.lowerLimit;

    for(int pix = 0; pix < ref.getElmNum(); pix++) {
        data[pix] = ref[pix];
    }
}

template <typename T>
ImageBase<T >::~ImageBase()
{
    if(data != nullptr) {
        delete[] data;
        data = nullptr;
    }
}

template <typename T>
void ImageBase<T >::init()
{
    for(int pix = 0; pix < size.getElmNum(); pix++) {
        data[pix] = lowerLimit;
    }
}

template <typename T>
void ImageBase<T >::zero()
{
    for(int pix = 0; pix < size.getElmNum(); pix++) {
        data[pix] = ZERO;
    }
}

template <typename T>
bool ImageBase<T >::resize(int width, int height)
{
#ifdef _DEBUG
    assert(width >= 0 && height >= 0);
#endif
    if(data != nullptr) {
        delete[] data;
    }
    size.setSize(width, height);

    data = new T[size.getElmNum()];

    return true;
}

template <typename T>
bool ImageBase<T >::resize(const ImageSize& imgSize)
{
    return resize(imgSize.getWidth(), imgSize.getHeight());
}

template <typename T>
bool ImageBase<T >::loadBinaryImage(const char* filename, const ImageSize& imgSize)
{
    FILE*   fp;
    errno_t error;

    if(size != imgSize) {
        resize(imgSize.getWidth(), imgSize.getHeight());
    }

    if((error = fopen_s(&fp, filename, "rb")) != 0) {
        fprintf(stderr, "Error : File open [%s]\n", filename);
        return false;
    }

    fread(data, sizeof(T), size.getElmNum(), fp);
    fclose(fp);

    return true;
}

template <typename T>
bool ImageBase<T >::saveBinaryImage(const char* filename) const
{
    FILE*   fp;
    errno_t error;

    // ファイルオープン
    if((error = fopen_s(&fp, filename, "wb")) != 0) {
        fprintf(stderr, "Error : File open [%s]\n", filename);
        return false;
    }
    // ファイル書き込み
    fwrite(data, sizeof(T), size.getElmNum(), fp);
    // ファイルクローズ
    fclose(fp);
    return true;
}

template <typename T>
bool ImageBase<T >::loadAsciiImage(const char* filename, const ImageSize& imgSize)
{
    // サイズの確認
    if(size != imgSize) {
        resize(imgSize.getWidth(), imgSize.getHeight());
    }

    int i = 0;
    std::ifstream file(filename);
    std::string temp;
    while(getline(file, temp, ' ') && i < size.getElmNum()) {
        if(!temp.empty()) {
            data[i] = static_cast<T >(std::stod(temp));
            ++i;
        }
    }

    return true;
}

template <typename T>
bool ImageBase<T >::saveAsciiImage(const char* filename) const
{
    std::ofstream file(filename);

    for(int i = 0; i < size.getElmNum(); i++) {
        file << data[i] << " ";
    }

    return true;
}

IMG_TEMPLATE_DEFINE(ImageBase)

template <typename T>
ReconImage<T >::ReconImage() 
: ImageBase()
, x0(ZERO), y0(ZERO), radius(ZERO)
{
}

template <typename T>
ReconImage<T >::ReconImage(int width, int height) 
: ImageBase(width, height)
{
    x0 = static_cast<T >(size.getWidth() / 2.0);
    y0 = static_cast<T >(size.getHeight() / 2.0);
    radius = (x0 < y0) ? x0 : y0;
}

template <typename T>
ReconImage<T >::ReconImage(const ImageSize& imgSize)
: ImageBase(imgSize)
{
    x0 = static_cast<T >(size.getWidth() / 2.0);
    y0 = static_cast<T >(size.getHeight() / 2.0);
    radius = (x0 < y0) ? x0 : y0;
}

template <typename T>
ReconImage<T >::~ReconImage()
{
    ImageBase::~ImageBase();
}

template <typename T>
bool ReconImage<T >::resize(int width, int height)
{
    bool ret =ImageBase::resize(width, height);
    if(ret) {
        x0 = static_cast<T >(size.getWidth() / 2.0);
        y0 = static_cast<T >(size.getHeight() / 2.0);
        radius = (x0 < y0) ? x0 : y0;
    }
    return ret;
}

template <typename T>
bool ReconImage<T >::resize(const ImageSize& imgSize)
{
    bool ret = ImageBase::resize(imgSize);
    if(ret) {
        x0 = static_cast<T >(size.getWidth() / 2.0);
        y0 = static_cast<T >(size.getHeight() / 2.0);
        radius = (x0 < y0) ? x0 : y0;
    }
    return ret;
}

template <typename T>
bool ReconImage<T >::loadBinaryImage(const char* filename, const ImageSize& imgSize)
{
    bool ret = ImageBase::loadBinaryImage(filename, imgSize);
    if(ret) {
        x0 = static_cast<T >(size.getWidth() / 2.0);
        y0 = static_cast<T >(size.getHeight() / 2.0);
        radius = (x0 < y0) ? x0 : y0;
    }
    return ret;
}

template <typename T>
bool ReconImage<T >::loadAsciiImage(const char* filename, const ImageSize& imgSize)
{
    bool ret = ImageBase::loadAsciiImage(filename, imgSize);
    if(ret) {
        x0 = static_cast<T >(size.getWidth() / 2.0);
        y0 = static_cast<T >(size.getHeight() / 2.0);
        radius = (x0 < y0) ? x0 : y0;
    }
    return ret;
}

template <typename T>
bool ReconImage<T >::isReconRegion(const int& x, const int& y) const
{
    return (((x - x0) * (x - x0) + (y - y0) * (y - y0)) < (radius * radius));
}

IMG_TEMPLATE_DEFINE(ReconImage)

