#include "GuiComp.h"
#include <imgui_impl_glfw.h>

#include <sys/stat.h>
#include <stdexcept>
#include <locale> 
#include <codecvt> 
#include <cstdio>

GuiBase::GuiBase() : clearColor(ImColor(84, 84, 84)), dispscale(1.0)
{
}

GuiBase::~GuiBase()
{
    // 終了処理
    ImGui_ImplGlfw_Shutdown();
    glfwTerminate();
}

bool GuiBase::init(int width, int height, const char* wintitle)
{
    if(!glfwInit()) {
        return false;
    }

    // ウインドウ生成
    window = glfwCreateWindow(width, height, wintitle, nullptr, nullptr);

    if(window == nullptr) {
        return false;
    }

    // VSYNC 有効化
    glfwSwapInterval(1);

    // アスペクト比固定
    glfwSetWindowAspectRatio(window, 5, 4);

    glfwMakeContextCurrent(window);

    // ImGui のバインディング設定
    ImGui_ImplGlfw_Init(window, true);

    return true;
}

bool GuiBase::isActive()
{
    return (!glfwWindowShouldClose(window));
}

void getFileNameList(ListComponent<std::string >& listComp, const std::string& dirName, const std::string& extension)
{
    if(listComp.nameList != nullptr) {
        for(int i = 0; i < listComp.materialList.size(); i++) {
            delete[] listComp.nameList[i];
        }
        listComp.materialList.clear();
    }

    HANDLE hFind;
    WIN32_FIND_DATA win32fd;

    // 拡張子の設定
    std::wstring_convert<std::codecvt_utf8<wchar_t >, wchar_t > cv;
    std::string searchName = dirName + "/*." + extension;
    std::wstring wsn = cv.from_bytes(searchName);

    hFind = FindFirstFile(wsn.c_str(), &win32fd);
    if(hFind == INVALID_HANDLE_VALUE) {
        return;
        //throw std::runtime_error("file not found");
    }

    // ファイル名取得
    std::vector<std::string > list;
    do {
        if(win32fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
        } else {
            std::string fname = cv.to_bytes(win32fd.cFileName);
            list.push_back(fname);
        }
    } while(FindNextFile(hFind, &win32fd));

    // データ成形
    listComp.nameList = new char*[list.size()];
    for(int i = 0; i < static_cast<int >(list.size()); i++) {
        listComp.nameList[i] = new char[list[i].size() + 1];
        std::char_traits<char >::copy(listComp.nameList[i], list[i].c_str(), list[i].size() + 1);
        listComp.materialList.push_back(dirName + "/" + list[i]);
    }
    FindClose(hFind);
}

void createDirectory(const char* path) {
    struct stat buff;
    char inst[BUFF_SZ];

    // ディレクトリ作成
    sprintf_s(inst, sizeof(inst), "mkdir %s", path);
    if(stat(path, &buff) != 0) {
        if(system(inst) != 0) {
            exit(EXIT_FAILURE);
        }
    }
}