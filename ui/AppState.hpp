#include "imgui/imgui.h"
#include <GLFW/glfw3.h>
#include "core/timer.hpp"
#include <string>

enum class AppState{
    MAIN
};

namespace WindowState {
    inline void RenderMainState(GLFWwindow* window, Timer& time) {
        int seconds = time.getSeconds();
        int minutes = time.getMinutes();
        int countRelax = time.getCountToRelax();
        std::string status = time.isStarted() ? time.getStatus() : " ";

        float scrW = ImGui::GetIO().DisplaySize.x;
        float scrH = ImGui::GetIO().DisplaySize.y;

        // 1. Counter relax
        std::string relaxStr = std::to_string(countRelax);
        float relaxW = ImGui::CalcTextSize(relaxStr.c_str()).x;
        ImGui::SetCursorPos(ImVec2(scrW - relaxW - 20.0f, 20.0f));
        ImGui::TextUnformatted(relaxStr.c_str());

        // 2. Status
        float statusW = ImGui::CalcTextSize(status.c_str()).x;
        ImGui::SetCursorPos(ImVec2((scrW - statusW) * 0.5f, scrH * 0.5f - 60.0f));
        ImGui::TextUnformatted(status.c_str());

        // 3. Timer
        char timeBuf[16];
        snprintf(timeBuf, sizeof(timeBuf), "%02d:%02d", minutes, seconds);
        float timeW = ImGui::CalcTextSize(timeBuf).x;
        ImGui::SetCursorPos(ImVec2((scrW - timeW) * 0.5f, scrH * 0.5f - 20.0f));
        ImGui::TextUnformatted(timeBuf);

        static bool showButton = true;
        if (showButton) {
            ImVec2 btnSize(100.0f, 35.0f);
            ImGui::SetCursorPos(ImVec2((scrW - btnSize.x) * 0.5f, scrH * 0.5f + 30.0f));
            if (ImGui::Button("Start", btnSize)) {
                time.start();
                showButton = false;
            }
        }
    }
};
