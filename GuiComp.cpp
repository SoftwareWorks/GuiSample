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
    // �I������
    ImGui_ImplGlfw_Shutdown();
    glfwTerminate();
}

bool GuiBase::init(int width, int height, const char* wintitle)
{
    if(!glfwInit()) {
        return false;
    }

    // �E�C���h�E����
    window = glfwCreateWindow(width, height, wintitle, nullptr, nullptr);

    if(window == nullptr) {
        return false;
    }

    // VSYNC �L����
    glfwSwapInterval(1);

    // �A�X�y�N�g��Œ�
    glfwSetWindowAspectRatio(window, 5, 4);

    glfwMakeContextCurrent(window);

    // ImGui �̃o�C���f�B���O�ݒ�
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

    // �g���q�̐ݒ�
    std::wstring_convert<std::codecvt_utf8<wchar_t >, wchar_t > cv;
    std::string searchName = dirName + "/*." + extension;
    std::wstring wsn = cv.from_bytes(searchName);

    hFind = FindFirstFile(wsn.c_str(), &win32fd);
    if(hFind == INVALID_HANDLE_VALUE) {
        return;
        //throw std::runtime_error("file not found");
    }

    // �t�@�C�����擾
    std::vector<std::string > list;
    do {
        if(win32fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
        } else {
            std::string fname = cv.to_bytes(win32fd.cFileName);
            list.push_back(fname);
        }
    } while(FindNextFile(hFind, &win32fd));

    // �f�[�^���`
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

    // �f�B���N�g���쐬
    sprintf_s(inst, sizeof(inst), "mkdir %s", path);
    if(stat(path, &buff) != 0) {
        if(system(inst) != 0) {
            exit(EXIT_FAILURE);
        }
    }
}