#ifndef __H_RENDER__
#define __H_RENDER__

#include "Vec.h"
#include "ImageOp.h"
#include <GLFW/glfw3.h>

struct Rect
{
    // 位置（横）
    int x;

    // 位置（縦）
    int y;

    // 幅
    int width;

    // 高さ
    int height;

    // デフォルトコンストラクタ
    Rect() : x(0), y(0), width(0), height(0) {}

    // サイズ指定のコンストラクタ
    Rect(int _x, int _y, int _width, int _height) : x(_x), y(_y), width(_width), height(_height) {}

    // サイズの設定
    void set(int _x, int _y, int _width, int _height)
    {
        this->x = _x;
        this->y = _y;
        this->width = _width;
        this->height = _height;
    }

    // デバッグ用
    void print()
    {
        printf("[ x = %d, y = %d, w = %d, h = %d ]\n", this->x, this->y, this->width, this->height);
    }
};

template <typename T = double>
class ImageRenderer
{
private:

    // テクスチャ ID
    GLuint texId;

    // テクスチャサイズ
    Rect texRect;

public:

    // デフォルトコンストラクタ
    ImageRenderer();
    
    // デストラクタ
    ~ImageRenderer();

    // 初期化
    void init();

    // テクスチャの設定
    void setTextureImage(const ImageBase<T >& img);

    // レンダリング
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
