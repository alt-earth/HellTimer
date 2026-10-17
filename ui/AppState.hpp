#include "imgui/imgui.h"
#include <GLFW/glfw3.h>
#include "core/timer.hpp"
#include <string>

enum class AppState{
    MAIN
};

namespace WindowState {
    inline void ApplyHellishStyle() {
        ImGuiStyle& style = ImGui::GetStyle();
        ImVec4* colors = style.Colors;

        style.WindowRounding = 0.0f;
        style.FrameRounding = 0.0f;
        style.GrabRounding = 0.0f;
        style.WindowBorderSize = 1.0f;
        style.FrameBorderSize = 1.0f;

        colors[ImGuiCol_Text]                   = ImVec4(0.85f, 0.00f, 0.00f, 1.00f);
        colors[ImGuiCol_TextDisabled]           = ImVec4(0.40f, 0.05f, 0.05f, 1.00f);
        colors[ImGuiCol_WindowBg]               = ImVec4(0.04f, 0.01f, 0.01f, 1.00f);
        colors[ImGuiCol_Border]                 = ImVec4(0.55f, 0.00f, 0.00f, 0.60f);
        colors[ImGuiCol_FrameBg]                = ImVec4(0.12f, 0.02f, 0.02f, 0.60f);
        colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.25f, 0.04f, 0.04f, 0.80f);
        colors[ImGuiCol_FrameBgActive]          = ImVec4(0.45f, 0.00f, 0.00f, 1.00f);

        colors[ImGuiCol_Button]                 = ImVec4(0.18f, 0.02f, 0.02f, 1.00f);
        colors[ImGuiCol_ButtonHovered]          = ImVec4(0.35f, 0.04f, 0.04f, 1.00f);
        colors[ImGuiCol_ButtonActive]           = ImVec4(0.55f, 0.00f, 0.00f, 1.00f);
    }

    inline void RenderMainState(GLFWwindow* window, Timer& time) {
        ApplyHellishStyle();

        int seconds = time.getSeconds();
        int minutes = time.getMinutes();
        int countRelax = time.getCountToRelax();

        bool isStarted = time.isStarted();
        std::string status = isStarted ? time.getStatus() : " ";

        float winW = ImGui::GetWindowWidth();
        float winH = ImGui::GetWindowHeight();

        std::string relaxStr = "SACRIFICES: " + std::to_string(countRelax) + " / 4";
        float relaxW = ImGui::CalcTextSize(relaxStr.c_str()).x;
        ImGui::SetCursorPos(ImVec2(winW - relaxW - 20.0f, 20.0f));


        ImVec4 relaxColor = (countRelax > 0) ? ImVec4(1.0f, 0.1f, 0.1f, 1.0f) : ImVec4(0.5f, 0.05f, 0.05f, 1.0f);
        ImGui::TextColored(relaxColor, "%s", relaxStr.c_str());

        float statusW = ImGui::CalcTextSize(status.c_str()).x;
        ImGui::SetCursorPos(ImVec2((winW - statusW) * 0.5f, winH * 0.5f - 60.0f));

        if (!isStarted) {
            ImGui::TextUnformatted(status.c_str());
        } else if (status == "Work") {
            ImGui::TextColored(ImVec4(1.0f, 0.45f, 0.0f, 1.0f), "%s", status.c_str());
        } else {
            ImGui::TextColored(ImVec4(0.2f, 0.75f, 0.2f, 1.0f), "%s", status.c_str());
        }

        char timeBuf[32];
        snprintf(timeBuf, sizeof(timeBuf), "[ %02d:%02d ]", minutes, seconds);
        float timeW = ImGui::CalcTextSize(timeBuf).x;
        ImGui::SetCursorPos(ImVec2((winW - timeW) * 0.5f, winH * 0.5f - 20.0f));

        if (!isStarted) {
            ImGui::TextColored(ImVec4(0.35f, 0.02f, 0.02f, 1.00f), "%s", timeBuf);
        } else if (status == "Work") {
            ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.00f), "%s", timeBuf);
        } else {
            ImGui::TextColored(ImVec4(0.0f, 0.9f, 0.1f, 1.00f), "%s", timeBuf);
        }

        if (!isStarted) {
            ImVec2 btnSize(130.0f, 40.0f);
            ImGui::SetCursorPos(ImVec2((winW - btnSize.x) * 0.5f, winH * 0.5f + 40.0f));

            if (ImGui::Button("INITIALIZE", btnSize)) {
                time.start();
            }
        }
    }
};
