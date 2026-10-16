#include "imgui/imgui.h"
#include <GLFW/glfw3.h>
#include "core/timer.hpp"

enum class AppState{
    MAIN
};


namespace WindowState{
    inline void RenderMainState(GLFWwindow* window, Timer& time){
        int seconds = time.getSeconds();
        int minutes = time.getMinutes();
        ImGui::Text("%02d:%02d", minutes, seconds);
    }
};
