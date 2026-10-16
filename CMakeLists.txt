cmake_minimum_required(VERSION 3.15)
project(ImGuiGlfwExample CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Поиск GLFW и OpenGL
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

# 2. Пути к исходникам ImGui
set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/imgui)

# 3. Список файлов ImGui, которые нужно скомпилировать
set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    # Бэкенды для GLFW и OpenGL3
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

# 4. Создание исполняемого файла (ДОБАВИЛИ core/audioEngine.cpp)
add_executable(${PROJECT_NAME}
    main.cpp
    core/audioEngine.cpp  # <-- Добавили наш новый .cpp файл
    ${IMGUI_SOURCES}
)

# 5. Указываем папки с хедерами (ДОБАВИЛИ папку core)
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/core # <-- Чтобы компилятор видел audioEngine.hpp и miniaudio.h
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
)

# 6. Линковка библиотек
target_link_libraries(${PROJECT_NAME} PRIVATE
    glfw
    OpenGL::GL
    ${CMAKE_DL_LIBS}
)
