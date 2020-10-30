#include "imgui_impl_juce.h"
#include "imgui.h"

static juce::int64 g_Time = 0;
static juce::MouseCursor::StandardCursorType g_MouseCursors[ImGuiMouseCursor_COUNT] = {};
static bool g_MouseCursorHidden = false;
static bool g_MouseJustPressed[ImGuiMouseButton_COUNT] = {};
static bool g_MouseDown[ImGuiMouseButton_COUNT] = {};

void ImGui_ImplJUCE_Init() {
    ImGuiIO &io = ImGui::GetIO();

    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
    // io.BackendFlags |= ImGuiBackendFlags_PlatformHasViewports;
    // io.BackendFlags |= ImGuiBackendFlags_RendererHasViewports;
    io.BackendPlatformName = "imgui_impl_juce";
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    // io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    //io.KeyMap[ImGuiKey_Tab] = juce::KeyPress::tabKey;
    //io.KeyMap[ImGuiKey_LeftArrow] = juce::KeyPress::leftKey;
    //io.KeyMap[ImGuiKey_RightArrow] = juce::KeyPress::rightKey;
    //io.KeyMap[ImGuiKey_UpArrow] = juce::KeyPress::upKey;
    //io.KeyMap[ImGuiKey_DownArrow] = juce::KeyPress::downKey;
    //io.KeyMap[ImGuiKey_PageUp] = juce::KeyPress::pageUpKey;
    //io.KeyMap[ImGuiKey_PageDown] = juce::KeyPress::pageDownKey;
    //io.KeyMap[ImGuiKey_Home] = juce::KeyPress::homeKey;
    //io.KeyMap[ImGuiKey_End] = juce::KeyPress::endKey;
    //io.KeyMap[ImGuiKey_Insert] = juce::KeyPress::insertKey;
    //io.KeyMap[ImGuiKey_Delete] = juce::KeyPress::deleteKey;
    //io.KeyMap[ImGuiKey_Backspace] = juce::KeyPress::backspaceKey;
    //io.KeyMap[ImGuiKey_Space] = juce::KeyPress::spaceKey;
    //io.KeyMap[ImGuiKey_Enter] = 13;
    //io.KeyMap[ImGuiKey_Escape] = juce::KeyPress::escapeKey;
    //io.KeyMap[ImGuiKey_KeyPadEnter] = 13;
    //io.KeyMap[ImGuiKey_A] = 'A';
    //io.KeyMap[ImGuiKey_C] = 'C';
    //io.KeyMap[ImGuiKey_V] = 'V';
    //io.KeyMap[ImGuiKey_X] = 'X';
    //io.KeyMap[ImGuiKey_Y] = 'Y';
    //io.KeyMap[ImGuiKey_Z] = 'Z';

    for (int i = 0; i < IM_ARRAYSIZE(io.KeyMap); ++i) {
        io.KeyMap[i] = i + 256;
    }

    g_MouseCursorHidden = false;
    g_MouseCursors[ImGuiMouseCursor_Arrow] = juce::MouseCursor::StandardCursorType::NormalCursor;
    g_MouseCursors[ImGuiMouseCursor_TextInput] = juce::MouseCursor::StandardCursorType::IBeamCursor;
    g_MouseCursors[ImGuiMouseCursor_ResizeAll] = juce::MouseCursor::StandardCursorType::DraggingHandCursor;
    g_MouseCursors[ImGuiMouseCursor_Hand] = juce::MouseCursor::StandardCursorType::PointingHandCursor;
    g_MouseCursors[ImGuiMouseCursor_NotAllowed] = juce::MouseCursor::StandardCursorType::NoCursor;
    g_MouseCursors[ImGuiMouseCursor_ResizeNS] = juce::MouseCursor::StandardCursorType::UpDownResizeCursor;
    g_MouseCursors[ImGuiMouseCursor_ResizeEW] = juce::MouseCursor::StandardCursorType::LeftRightResizeCursor;
    g_MouseCursors[ImGuiMouseCursor_ResizeNESW] = juce::MouseCursor::StandardCursorType::TopRightCornerResizeCursor;
    g_MouseCursors[ImGuiMouseCursor_ResizeNWSE] = juce::MouseCursor::StandardCursorType::TopLeftCornerResizeCursor;

    io.SetClipboardTextFn = [](void *, const char *str) -> void { juce::SystemClipboard::copyTextToClipboard(str); };

    io.GetClipboardTextFn = [](void *) -> const char * {
        return juce::SystemClipboard::getTextFromClipboard().toUTF8();
    };
}

void ImGui_ImplJUCE_Shutdown() {}

static void ImGui_ImplJUCE_UpdateMouseCursorAndButtons(juce::Component *component) {
    ImGuiIO &io = ImGui::GetIO();
    for (int i = 0; i < IM_ARRAYSIZE(io.MouseDown); i++) {
        io.MouseDown[i] = g_MouseJustPressed[i] || g_MouseDown[i];
        g_MouseJustPressed[i] = false;
    }
    if (io.ConfigFlags & ImGuiConfigFlags_NoMouseCursorChange) {
        return;
    }
    ImGuiMouseCursor imgui_cursor = ImGui::GetMouseCursor();
    if (io.MouseDrawCursor || imgui_cursor == ImGuiMouseCursor_None) {
        if (!g_MouseCursorHidden) {
            g_MouseCursorHidden = true;
            component->setMouseCursor(juce::MouseCursor(juce::MouseCursor::StandardCursorType::NoCursor));
        }
    } else {
        if (g_MouseCursorHidden) {
            g_MouseCursorHidden = false;
        }
        component->setMouseCursor(juce::MouseCursor(g_MouseCursors[imgui_cursor]));
    }
}

void ImGui_ImplJUCE_NewFrame(juce::Component *component) {
    ImGuiIO &io = ImGui::GetIO();
    if (component) {
        io.DisplaySize = ImVec2((float)component->getWidth(), (float)component->getHeight());
    }
    juce::int64 current_time = juce::Time::currentTimeMillis();
    if (g_Time == 0.0) {
        g_Time = current_time;
    }
    if (current_time > g_Time) {
        io.DeltaTime = (current_time - g_Time) * 0.001f;
    } else {
        io.DeltaTime = 1.0f / 60.0f;
    }
    g_Time = current_time;

    ImGui_ImplJUCE_UpdateMouseCursorAndButtons(component);
}

bool ImGui_ImplJUCE_HandleKeyPressed(const juce::KeyPress &key, juce::Component *originatingComponent) {
    ImGuiIO &io = ImGui::GetIO();
    unsigned int c = static_cast<unsigned int>(key.getTextCharacter());
    io.AddInputCharacter(c);
    return c == '\t' || io.WantCaptureKeyboard;
}

bool ImGui_ImplJUCE_HandleKeyStateChanged(const bool isKeyDown, juce::Component *originatingComponent) {
    ImGuiIO &io = ImGui::GetIO();
    io.KeyShift = juce::KeyPress::isKeyCurrentlyDown(16);
    io.KeyCtrl = juce::KeyPress::isKeyCurrentlyDown(17);
    io.KeyAlt = juce::KeyPress::isKeyCurrentlyDown(18);
    io.KeySuper = juce::KeyPress::isKeyCurrentlyDown(91) || juce::KeyPress::isKeyCurrentlyDown(92) ||
                  juce::KeyPress::isKeyCurrentlyDown(93);
    io.KeyMods = ImGuiKeyModFlags_None;
    if (io.KeyShift) {
        io.KeyMods |= ImGuiKeyModFlags_Shift;
    }
    if (io.KeyCtrl) {
        io.KeyMods |= ImGuiKeyModFlags_Ctrl;
    }
    if (io.KeyAlt) {
        io.KeyMods |= ImGuiKeyModFlags_Alt;
    }
    if (io.KeySuper) {
        io.KeyMods |= ImGuiKeyModFlags_Super;
    }
    for (int i = 8; i < 256; ++i) {
        io.KeysDown[i] = juce::KeyPress::isKeyCurrentlyDown(i);
    }
    for (int i = 0; i < IM_ARRAYSIZE(io.KeyMap); ++i) {
        int key;
        switch (i) {
            case ImGuiKey_Tab: key = juce::KeyPress::tabKey; break;
            case ImGuiKey_LeftArrow: key = juce::KeyPress::leftKey; break;
            case ImGuiKey_RightArrow: key = juce::KeyPress::rightKey; break;
            case ImGuiKey_UpArrow: key = juce::KeyPress::upKey; break;
            case ImGuiKey_DownArrow: key = juce::KeyPress::downKey; break;
            case ImGuiKey_PageUp: key = juce::KeyPress::pageUpKey; break;
            case ImGuiKey_PageDown: key = juce::KeyPress::pageDownKey; break;
            case ImGuiKey_Home: key = juce::KeyPress::homeKey; break;
            case ImGuiKey_End: key = juce::KeyPress::endKey; break;
            case ImGuiKey_Insert: key = juce::KeyPress::insertKey; break;
            case ImGuiKey_Delete: key = juce::KeyPress::deleteKey; break;
            case ImGuiKey_Backspace: key = juce::KeyPress::backspaceKey; break;
            case ImGuiKey_Space: key = juce::KeyPress::spaceKey; break;
            case ImGuiKey_Enter: key = 13; break;
            case ImGuiKey_Escape: key = juce::KeyPress::escapeKey; break;
            case ImGuiKey_KeyPadEnter: key = 13; break;
            case ImGuiKey_A: key = 'A'; break;
            case ImGuiKey_C: key = 'C'; break;
            case ImGuiKey_V: key = 'V'; break;
            case ImGuiKey_X: key = 'X'; break;
            case ImGuiKey_Y: key = 'Y'; break;
            case ImGuiKey_Z: key = 'Z'; break;
        }
        io.KeysDown[io.KeyMap[i]] = juce::KeyPress::isKeyCurrentlyDown(key);
    }
    return io.WantCaptureKeyboard;
}

void ImGui_ImplJUCE_HandleMouseMove(const juce::MouseEvent &event) {
    ImGuiIO &io = ImGui::GetIO();
    io.MousePos = ImVec2((float)event.getPosition().getX(), (float)event.getPosition().getY());
}

void ImGui_ImplJUCE_HandleMouseEnter(const juce::MouseEvent &event) {}

void ImGui_ImplJUCE_HandleMouseExit(const juce::MouseEvent &event) {}

void ImGui_ImplJUCE_HandleMouseDown(const juce::MouseEvent &event) {
    if (event.mods.isLeftButtonDown()) {
        g_MouseJustPressed[0] = true;
        g_MouseDown[0] = true;
    }
    if (event.mods.isRightButtonDown()) {
        g_MouseJustPressed[1] = true;
        g_MouseDown[1] = true;
    }
    if (event.mods.isMiddleButtonDown()) {
        g_MouseJustPressed[2] = true;
        g_MouseDown[2] = true;
    }
}

void ImGui_ImplJUCE_HandleMouseDrag(const juce::MouseEvent &event) {
    ImGuiIO &io = ImGui::GetIO();
    io.MousePos = ImVec2((float)event.getPosition().getX(), (float)event.getPosition().getY());
}

void ImGui_ImplJUCE_HandleMouseUp(const juce::MouseEvent &event) {
    if (event.mods.isLeftButtonDown()) {
        g_MouseDown[0] = false;
    }
    if (event.mods.isRightButtonDown()) {
        g_MouseDown[1] = false;
    }
    if (event.mods.isMiddleButtonDown()) {
        g_MouseDown[2] = false;
    }
}

void ImGui_ImplJUCE_HandleMouseDoubleClick(const juce::MouseEvent &event) {}

void ImGui_ImplJUCE_HandleMouseWheelMove(const juce::MouseEvent &event, const juce::MouseWheelDetails &wheel) {
    ImGuiIO &io = ImGui::GetIO();
    if (fabs(wheel.deltaX) > 0.0) {
        io.MouseWheelH += wheel.deltaX * 2.5;
    }
    if (fabs(wheel.deltaY) > 0.0) {
        io.MouseWheel += wheel.deltaY * 2.5;
    }
}

void ImGui_ImplJUCE_HandleMouseMagnify(const juce::MouseEvent &event, float scaleFactor) {
    ImGuiIO &io = ImGui::GetIO();
    io.FontGlobalScale *= scaleFactor;
}
