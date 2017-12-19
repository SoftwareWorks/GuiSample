#ifndef __H_GUI_COMP__
#define __H_GUI_COMP__

// windows.h �̕ςȃ}�N��������
#define NOMINMAX

#include <imgui.h>
#include <Windows.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <string>

#include "Render.h"
#include <imgui_impl_glfw.h>

#define ARRAY_SIZE(ARR_)  (static_cast<int >(sizeof(ARR_) / sizeof(*ARR_)))

template <typename T>
struct ListComponent
{
    // ���ݎw���Ă���ʒu
    int cursor;

    // ���̃��X�g
    std::vector<T > materialList;

    // �\�������X�g
    char** nameList;

    // �f�t�H���g�R���X�g���N�^
    ListComponent() : cursor(0), nameList(nullptr) {}

    // �f�X�g���N�^
    ~ListComponent() {}

};

class GuiBase
{

protected:

    // ���C���E�C���h�E
    GLFWwindow* window;

    // �r���[�|�[�g
    Rect viewport;

    // �X�P�[��
    double dispscale;

    // �N���A�J���[
    ImVec4 clearColor;

public:

    // �f�t�H���g�R���X�g���N�^
    GuiBase();
    
    // �f�X�g���N�^
    virtual ~GuiBase();

    // ������
    bool init(int width, int height, const char* wintitle);

    // �E�C���h�E��Ԏ擾
    bool isActive();

};

// �t�@�C�����̎擾
void getFileNameList(ListComponent<std::string >& listComp, const std::string& dirName, const std::string& extension);

// �f�B���N�g���쐬
void createDirectory(const char* path);

#endif
