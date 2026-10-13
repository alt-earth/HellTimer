#include "imgui/imgui.h"
#include <GLFW/glfw3.h>
#include "core/timer.hpp"

enum class AppState{
    MAIN
};


namespace WindowState{
    inline void RenderMainState(GLFWwindow* window, Timer& time){
        int seconds = time.getSeconds();
        ImGui::Text("seconds: %d", seconds);
    }
};
