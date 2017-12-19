#include "Render.h"
#include <typeinfo>

template <typename T>
ImageRenderer<T >::ImageRenderer()
{
}

template <typename T>
ImageRenderer<T >::~ImageRenderer()
{

}

template <typename T>
void ImageRenderer<T >::init()
{
    glGenTextures(1, &texId);
}

template <typename T>
void ImageRenderer<T >::setTextureImage(const ImageBase<T >& img)
{
    glPushAttrib(GL_ENABLE_BIT);
    glEnable(GL_TEXTURE_2D);

    texRect.set(0, 0, img.getWidth(), img.getHeight());

    // 生成
    glBindTexture(GL_TEXTURE_2D, texId);

    // 冗長になるのでオーバーロードしない
    GLenum type;
    if(typeid(T) == typeid(float)) {
        type = GL_FLOAT;
    } else if(typeid(T) == typeid(int)) {
        type = GL_INT;
    } else if(typeid(T) == typeid(unsigned int)){
        type = GL_UNSIGNED_INT;
    } else if(typeid(T) == typeid(short)) {
        type = GL_SHORT;
    } else if(typeid(T) == typeid(unsigned short)) {
        type = GL_UNSIGNED_SHORT;
    } else if(typeid(T) == typeid(unsigned char)) {
        type = GL_UNSIGNED_BYTE;
    //} else if(typeid(T) == typeid(double)) {  // double 型サポートの GPU?
    //    type = GL_DOUBLE;
    } else {
        return;
    }

    GLsizei texW = static_cast<GLsizei >(img.getWidth());
    GLsizei texH = static_cast<GLsizei >(img.getHeight());
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texW, texH, 0, GL_LUMINANCE, type, img.getPtr());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
    glPopAttrib();
}

template <typename T>
void ImageRenderer<T >::render()
{
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);

    glColor3f(1.0f, 1.0f, 1.0f);
    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_FLAT);

    glColorMask(1, 1, 1, 1);
    glDisable(GL_CULL_FACE);
    glBindTexture(GL_TEXTURE_2D, texId);

    glBegin(GL_QUADS);
    glTexCoord2i(0, 0);
    glVertex2d(texRect.x - 0.5, texRect.y - 0.5);
    glTexCoord2i(0, 1);
    glVertex2d(texRect.x - 0.5, texRect.y + texRect.height - 0.5);
    glTexCoord2i(1, 1);
    glVertex2d(texRect.x + texRect.width - 0.5, texRect.y + texRect.height - 0.5);
    glTexCoord2i(1, 0);
    glVertex2d(texRect.x + texRect.width - 0.5, texRect.y - 0.5);
    glEnd();

    // 解放
    glShadeModel(GL_SMOOTH);
    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);

    glFlush();

}

template class ImageRenderer<unsigned char >;
template class ImageRenderer<short >;
template class ImageRenderer<unsigned short >;
template class ImageRenderer<int >;
template class ImageRenderer<unsigned int >;
template class ImageRenderer<float >;
template class ImageRenderer<double >;


void setGL2DViewMode(const Rect& viewport, const ImageSize& imgSize, const Vec2< >& disppos, const double& dispscale)
{
    glPushAttrib(GL_ENABLE_BIT | GL_CURRENT_BIT | GL_VIEWPORT_BIT);
    glViewport(viewport.x, viewport.y, viewport.width, viewport.height);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glDisable(GL_CULL_FACE);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    glOrtho(-0.5, viewport.width - 0.5, viewport.height - 0.5, -0.5, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    Vec2< > imgCenter(imgSize.getWidth() / 2.0, imgSize.getHeight() / 2.0);
    Vec2< > st = disppos + Vec2< >(viewport.width / 2.0, viewport.height / 2.0) - imgCenter * dispscale;

    glTranslated(st.x, st.y, 0.0);
    glScaled(dispscale, dispscale, dispscale);
}

void setGL3DViewMode(const Rect& viewport, const Vec2< >& range, const Vec2< >& disppos, const double& dispscale)
{
    glPushAttrib(GL_ENABLE_BIT | GL_CURRENT_BIT | GL_VIEWPORT_BIT);
    glViewport(viewport.x, viewport.y, viewport.width, viewport.height);

#ifdef _DEBUG
    assert(range.x > 0.0 && range.y > 0.0);
#endif

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    double w2 = viewport.width / dispscale;
    double h2 = viewport.height / dispscale;
    double left = (-disppos.x / dispscale);
    double right = left + w2;
    double top = (disppos.y / dispscale);
    double bottom = -(h2 - top);

    double fpx = range.x / dispscale;
    double fpy = range.y / dispscale;

    double l = left * fpx;
    double r = right * fpx;
    double b = bottom * fpy;
    double t = top * fpy;
    double n = range.x;
    double f = range.y;

    GLdouble m[16];
    glLoadMatrixd(getPerspectiveMatrix(m, l, r, b, t, n, f));
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
}

void unsetGLView()
{
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glPopAttrib();
}

GLdouble* getPerspectiveMatrix(GLdouble* matrix, const double& left, const double& right, const double& bottom, const double& top, const double& near, const double& far)
{
    double dx = right - left;
    double dy = top - bottom;
    double dz = far - near;

#ifdef _DEBUG
    assert(dx != 0.0 && dy != 0.0 && dz != 0.0);
#endif

    matrix[0] =  2.0 * near / dx;
    matrix[5] =  2.0 * near / dy;
    matrix[8] =  (right + left) / dx;
    matrix[9] =  (top + bottom) / dy;
    matrix[10] = -(far + near) / dz;
    matrix[11] = -1.0;
    matrix[14] = -2.0 * far * near / dz;
    matrix[1] = matrix[2] = matrix[3] = matrix[4] =
        matrix[6] = matrix[7] = matrix[12] = matrix[13] = matrix[15] = 0.0;

    return matrix;
}

GLdouble* getOrthogonalMatrix(GLdouble* matrix, const double& left, const double& right, const double& bottom, const double& top, const double& near, const double& far)
{
    double dx = right - left;
    double dy = top - bottom;
    double dz = far - near;

#ifdef _DEBUG
    assert(dx != 0.0 && dy != 0.0 && dz != 0.0);
#endif

    matrix[0] =  2.0 / dx;
    matrix[5] =  2.0 / dy;
    matrix[10] = -2.0 / dz;
    matrix[12] = -(right + left) / dx;
    matrix[13] = -(top + bottom) / dy;
    matrix[14] = -(far + near) / dz;
    matrix[15] =  1.0;
    matrix[1] = matrix[2] = matrix[3] = matrix[4] =
        matrix[6] = matrix[7] = matrix[8] = matrix[9] = matrix[11] = 0.0;

    return matrix;
}
