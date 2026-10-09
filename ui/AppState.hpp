#include "imgui/imgui.h"
#include <GLFW/glfw3.h>

enum class AppState{
    MAIN
};


namespace WindowState{

    inline void RenderMainState(GLFWwindow* window){
        ImGui::Spacing();
        ImGui::Text("hello world");
    }
};
