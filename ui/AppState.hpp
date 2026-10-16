#include "imgui/imgui.h"
#include <GLFW/glfw3.h>
#include "core/timer.hpp"
#include <string>

enum class AppState{
    MAIN
};


namespace WindowState{
    inline void RenderMainState(GLFWwindow* window, Timer& time){
        int seconds = time.getSeconds();
        int minutes = time.getMinutes();

        std::string status = time.isStarted() ? time.getStatus() : "Press start";
        ImGui::TextUnformatted(status.c_str());


        ImGui::Text("%02d:%02d", minutes, seconds);
        if(ImGui::Button("Start")){
            time.start();
        }
    }
};
