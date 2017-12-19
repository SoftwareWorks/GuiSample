#ifndef __H_RENDER__
#define __H_RENDER__

#include "Vec.h"
#include "ImageOp.h"
#include <GLFW/glfw3.h>

struct Rect
{
    // �ʒu�i���j
    int x;

    // �ʒu�i�c�j
    int y;

    // ��
    int width;

    // ����
    int height;

    // �f�t�H���g�R���X�g���N�^
    Rect() : x(0), y(0), width(0), height(0) {}

    // �T�C�Y�w��̃R���X�g���N�^
    Rect(int _x, int _y, int _width, int _height) : x(_x), y(_y), width(_width), height(_height) {}

    // �T�C�Y�̐ݒ�
    void set(int _x, int _y, int _width, int _height)
    {
        this->x = _x;
        this->y = _y;
        this->width = _width;
        this->height = _height;
    }

    // �f�o�b�O�p
    void print()
    {
        printf("[ x = %d, y = %d, w = %d, h = %d ]\n", this->x, this->y, this->width, this->height);
    }
};

template <typename T = double>
class ImageRenderer
{
private:

    // �e�N�X�`�� ID
    GLuint texId;

    // �e�N�X�`���T�C�Y
    Rect texRect;

public:

    // �f�t�H���g�R���X�g���N�^
    ImageRenderer();
    
    // �f�X�g���N�^
    ~ImageRenderer();

    // ������
    void init();

    // �e�N�X�`���̐ݒ�
    void setTextureImage(const ImageBase<T >& img);

    // �����_�����O
    void render();

    GLuint getTextureId()
    {
        return texId;
    }

    Rect getSize()
    {
        return texRect;
    }
};

void setGL2DViewMode(const Rect& viewport, const ImageSize& imgSize, const Vec2< >& disppos, const double& dispscale);

void setGL3DViewMode(const Rect& viewport, const Vec2< >& range, const Vec2< >& disppos, const double& dispscale);

void unsetGLView();

GLdouble* getPerspectiveMatrix(GLdouble* matrix, const double& left, const double& right, const double& bottom, const double& top, const double& near, const double& far);

GLdouble* getOrthogonalMatrix(GLdouble* matrix, const double& left, const double& right, const double& bottom, const double& top, const double& near, const double& far);


#endif
