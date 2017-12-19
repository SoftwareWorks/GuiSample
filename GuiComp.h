#ifndef __H_GUI_COMP__
#define __H_GUI_COMP__

// windows.h の変なマクロを消す
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
    // 現在指している位置
    int cursor;

    // 実体リスト
    std::vector<T > materialList;

    // 表示名リスト
    char** nameList;

    // デフォルトコンストラクタ
    ListComponent() : cursor(0), nameList(nullptr) {}

    // デストラクタ
    ~ListComponent() {}

};

class GuiBase
{

protected:

    // メインウインドウ
    GLFWwindow* window;

    // ビューポート
    Rect viewport;

    // スケール
    double dispscale;

    // クリアカラー
    ImVec4 clearColor;

public:

    // デフォルトコンストラクタ
    GuiBase();
    
    // デストラクタ
    virtual ~GuiBase();

    // 初期化
    bool init(int width, int height, const char* wintitle);

    // ウインドウ状態取得
    bool isActive();

};

// ファイル名の取得
void getFileNameList(ListComponent<std::string >& listComp, const std::string& dirName, const std::string& extension);

// ディレクトリ作成
void createDirectory(const char* path);

#endif
