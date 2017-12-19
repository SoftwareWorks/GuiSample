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

class Mouse
{
private:

    ImGuiIO* io_;

    enum
    {
        LEFT_BUTTON,
        RIGHT_BUTTON,
        MIDDLE_BUTTON
    };

public:

    ImVec2* pos;

public:

    Mouse()
    {
        io_ = &ImGui::GetIO();
        pos = &io_->MousePos;
    }

    bool leftButtonDown()
    {
        return ImGui::IsMouseDown(LEFT_BUTTON);
    }

    bool rightButtonDown()
    {
        return ImGui::IsMouseDown(RIGHT_BUTTON);
    }

    bool isMiddleButtonDown()
    {
        return ImGui::IsMouseDown(MIDDLE_BUTTON);
    }

    bool isLeftButtonClicked()
    {
        return ImGui::IsMouseClicked(LEFT_BUTTON);
    }

    bool isRightButtonClicked()
    {
        return ImGui::IsMouseClicked(RIGHT_BUTTON);
    }

    bool isMiddleButtonClicked()
    {
        return ImGui::IsMouseClicked(MIDDLE_BUTTON);
    }

    bool isLeftButtonDoubleClicked()
    {
        return ImGui::IsMouseDoubleClicked(LEFT_BUTTON);
    }

    bool isRightButtonDoubleClicked()
    {
        return ImGui::IsMouseDoubleClicked(RIGHT_BUTTON);
    }

    bool isMiddleButtonDoubleClicked()
    {
        return ImGui::IsMouseDoubleClicked(MIDDLE_BUTTON);
    }

    bool isLeftButtonReleased()
    {
        return ImGui::IsMouseReleased(LEFT_BUTTON);
    }

    bool isRightButtonReleased()
    {
        return ImGui::IsMouseReleased(RIGHT_BUTTON);
    }

    bool isMiddleButtonReleased()
    {
        return ImGui::IsMouseReleased(MIDDLE_BUTTON);
    }

    const float& leftButtonDuration() const {
        return io_->MouseDownDuration[LEFT_BUTTON];
    }

    const float& rightButtonDuration() const
    {
        return io_->MouseDownDuration[RIGHT_BUTTON];
    }

    const float& middleButtonDuration() const
    {
        return io_->MouseDownDuration[MIDDLE_BUTTON];
    }

    const float& wheel() const
    {
        return io_->MouseWheel;
    }

};

class Keyboard
{
private:

    ImGuiIO* io_;

    enum
    {
        KEY_STATE_DOWN,
        KEY_STATE_UP
    };

public:
    Keyboard()
    {
        io_ = &ImGui::GetIO();
    }

    bool isCtrlKeyPressed()
    {
        return io_->KeyCtrl;
    }

    bool isShiftKeyPressed()
    {
        return io_->KeyShift;
    }

    bool isAltKeyPressed()
    {
        return io_->KeyAlt;
    }

    bool isSuperKeyPressed()
    {
        return io_->KeySuper;
    }

    bool isKeyPressed(unsigned char key)
    {
        return ImGui::IsKeyPressed(key);
    }

    bool isKeyReleased(unsigned char key)
    {
        return ImGui::IsKeyReleased(key);
    }

    const float& keyDownDuration(unsigned char key)
    {
        return io_->KeysDownDuration[key];
    }

    //ImGui::Text("WantCaptureMouse: %d", io.WantCaptureMouse);
    //ImGui::Text("WantCaptureKeyboard: %d", io.WantCaptureKeyboard);
    //ImGui::Text("WantTextInput: %d", io.WantTextInput);
    //ImGui::Text("WantMoveMouse: %d", io.WantMoveMouse);

    //if(ImGui::TreeNode("Keyboard & Mouse State")) {


    //    ImGui::Button("Hovering me sets the\nkeyboard capture flag");
    //    if(ImGui::IsItemHovered())
    //        ImGui::CaptureKeyboardFromApp(true);
    //    ImGui::SameLine();
    //    ImGui::Button("Holding me clears the\nthe keyboard capture flag");
    //    if(ImGui::IsItemActive())
    //        ImGui::CaptureKeyboardFromApp(false);

    //    ImGui::TreePop();
    //}
    //*/


};

class GuiBase
{

protected:

    Mouse mouse;

    Keyboard* keyboard;

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
