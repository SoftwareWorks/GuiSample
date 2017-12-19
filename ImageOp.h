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

    // ��
    int width;

    // ����
    int height;

    // �v�f��
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

    // �ŏ��l�̎擾
    int min() const
    {
        return ((this->width < this->height) ? this->width : this->height);
    }

    // �ő�l�̎擾
    int max() const
    {
        return ((this->width > this->height) ? this->width : this->height);
    }

    // �[���ɏ�����
    inline void zero()
    {
        this->width = this->height = this->elmcnt = 0;
    }

    // ImageSize �ɂ����
    ImageSize& operator =(const ImageSize& ref)
    {
        this->width = ref.width;
        this->height = ref.height;
        this->elmcnt = this->width * this->height;
        return *this;
    }

    // Vec2 �ɂ����
    ImageSize& operator =(const Vec2<int >& ref)
    {
        this->width = ref.x;
        this->height = ref.y;
        this->elmcnt = this->width * this->height;
        return *this;
    }

    // ��r�ix, y �̗����������ɍ����Ƃ��� TRUE�j
    bool operator <(const ImageSize& ref)
    {
        return (this->width < ref.width && this->height < ref.height);
    }

    // ��r�ix, y �̗����������ɍ����Ƃ��� TRUE�j
    bool operator >(const ImageSize& ref)
    {
        return (this->width > ref.width && this->height > ref.height);
    }

    // ��r�ix, y �̗����������ɍ����Ƃ��� TRUE�j
    bool operator <=(const ImageSize& ref)
    {
        return (this->width <= ref.width && this->height <= ref.height);
    }

    // ��r�ix, y �̗����������ɍ����Ƃ��� TRUE�j
    bool operator >=(const ImageSize& ref)
    {
        return (this->width >= ref.width && this->height >= ref.height);
    }

    // ��r�ix, y �̗����������ɍ����Ƃ��� TRUE�j
    bool operator ==(const ImageSize& ref)
    {
        return (this->width == ref.width && this->height == ref.height);
    }

    // ��r�ix, y �̗����������ɍ����Ƃ��� TRUE�j
    bool operator !=(const ImageSize& ref)
    {
        return (this->width != ref.width || this->height != ref.height);
    }

    // �l�̐ݒ�
    inline void setSize(const int& _width, const int& _height)
    {
#ifdef _DEBUG
        assert(_width >= 0 && _height >= 0);
#endif
        this->width = _width;
        this->height = _height;
        this->elmcnt = this->width * this->height;
    }

    // ���̎擾
    const int& getWidth() const
    {
        return this->width;
    }

    // �����̎擾
    const int& getHeight() const
    {
        return this->height;
    }

    // �v�f���̎擾
    const int& getElmNum() const
    {
        return this->elmcnt;
    }

    // �f�o�b�O�p
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

    // �����l
    T lowerLimit;

protected:

    // �f�[�^�i�[�̈�
    T* data;

    // �摜�T�C�Y
    ImageSize size;


public:

    // �f�t�H���g�R���X�g���N�^
    ImageBase();

    // �T�C�Y�w��̃R���X�g���N�^
    ImageBase(int width, int height);

    // �T�C�Y�w��̃R���X�g���N�^
    ImageBase(const ImageSize& imgSize);

    // �T�C�Y�w��̃R���X�g���N�^
    ImageBase(const ImageBase<T >& ref);

    // �f�X�g���N�^
    virtual ~ImageBase();

    // �摜��萔�ŏ�����
    void init();

    // �摜���[���ŏ�����
    void zero();

    // �摜�T�C�Y�ύX�i�������m�ۂ̂݁j
    bool resize(int width, int height);

    // �摜�T�C�Y�ύX�i�������m�ۂ̂݁j
    bool resize(const ImageSize& imgSize);

    // �o�C�i���摜�̓Ǎ���
    bool loadBinaryImage(const char* filename, const ImageSize& imgSize);

    // �o�C�i���摜�̏�������
    bool saveBinaryImage(const char* filename) const;

    // �A�X�L�[�摜�̓Ǎ���
    bool loadAsciiImage(const char* filename, const ImageSize& imgSize);

    // �A�X�L�[�摜�̏�������
    bool saveAsciiImage(const char* filename) const;

    // �摜���
    void clear()
    { 
        if(data != nullptr)
        { 
            size.setSize(0, 0);
            delete[] data;
        }
    }

    // �摜�͈͓����ǂ���
    bool isIn(int x, int y) const
    {
        return ((x >= 0 && y >= 0) && (x < size.getWidth() && y < size.getHeight()));
    }

    // ���̂̃|�C���^�擾
    const T* getPtr() const
    {
        return &data[0];
    }

    // �摜�T�C�Y�̎擾
    ImageSize& getSize()
    {
        return size;
    }

    // �摜�T�C�Y�̎擾
    const ImageSize& getSize() const
    { 
        return size;
    }

    // �摜���̎擾
    const int& getWidth() const
    {
        return size.getWidth();
    }

    // �摜�����̎擾
    const int& getHeight() const
    {
        return size.getHeight();
    }

    // �v�f���̎擾
    const int& getElmNum() const
    {
        return size.getElmNum();
    }

    // �v�f�A�N�Z�X
    T& at(int idx)
    { 
#ifdef _DEBUG
        assert(idx < size.getElmNum());
#endif
        return data[idx];
    }

    // �v�f�A�N�Z�X
    const T& at(int idx) const
    { 
#ifdef _DEBUG
        assert(idx < size.getElmNum());
#endif
        return data[idx];
    }

    // �v�f�A�N�Z�X
    T& operator [](int idx)
    { 
#ifdef _DEBUG
        assert(idx < size.getElmNum());
#endif
        return data[idx];
    }

    // �v�f�A�N�Z�X
    const T& operator [](int idx) const
    { 
#ifdef _DEBUG
        assert(idx < size.getElmNum());
#endif
        return data[idx];
    }

    // �v�f�A�N�Z�X
    T& operator ()(int i, int j)
    {
#ifdef _DEBUG
        assert((i * size.getWidth() + j) < size.getElmNum());
#endif
        return data[i * size.getWidth() + j];
    }

    // �v�f�A�N�Z�X
    const T& operator ()(int i, int j) const
    {
#ifdef _DEBUG
        assert((i * size.getWidth() + j) < size.getElmNum());
#endif
        return data[i * size.getWidth() + j];
    }

    // �摜�̃R�s�[
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

    // �f�t�H���g�R���X�g���N�^
    ReconImage();

    // �T�C�Y�w��̃R���X�g���N�^
    ReconImage(int width, int height);

    // �T�C�Y�w��̃R���X�g���N�^
    ReconImage(const ImageSize& imgSize);

    // �f�X�g���N�^
    virtual ~ReconImage();

    // �摜�T�C�Y�ύX�i�������m�ۂ̂݁j
    bool resize(int width, int height);

    // �摜�T�C�Y�ύX�i�������m�ۂ̂݁j
    bool resize(const ImageSize& imgSize);

    // �o�C�i���摜�̓Ǎ���
    bool loadBinaryImage(const char* filename, const ImageSize& imgSize);

    // �A�X�L�[�摜�̓Ǎ���
    bool loadAsciiImage(const char* filename, const ImageSize& imgSize);

    // �č\���̈悩�ǂ���
    bool isReconRegion(const int& x, const int& y) const;

    // �摜���
    void clear()
    {
        if(data != nullptr) {
            size.setSize(0, 0);
            delete[] data;
        }
        radius = ZERO;
    }

    // �摜�̃R�s�[�iImageBase�j
    const ReconImage<T >& operator =(const ImageBase<T >& ref)
    {
        resize(ref.getSize());
        this->lowerLimit = ref.lowerLimit;
        for(int pix = 0; pix < getElmNum(); pix++) {
            this->data[pix] = ref[pix];
        }
        return *this;
    }

    // �摜�̃R�s�[�iReconImage�j
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

    // �摜���S�iX ���W�j
    T x0;

    // �摜���S�iY ���W�j
    T y0;

    // �č\�����a
    T radius;

};

IMG_DEFINE(ReconImage, RImage)


#endif
