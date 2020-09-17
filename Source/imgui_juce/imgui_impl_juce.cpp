#include "imgui_impl_juce.h"
#include "imgui.h"

static juce::int64 g_Time = 0;
static juce::MouseCursor::StandardCursorType g_MouseCursors[ImGuiMouseCursor_COUNT] = {};
static bool g_MouseCursorHidden = false;

void ImGui_ImplJUCE_Init() {
    ImGuiIO &io = ImGui::GetIO();

    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
    // io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
    // io.BackendFlags |= ImGuiBackendFlags_PlatformHasViewports;
    // io.BackendFlags |= ImGuiBackendFlags_HasMouseHoveredViewport;
    io.BackendPlatformName = "imgui_impl_juce";

    const int offset_for_function_keys = 256 - 0xF700;
    io.KeyMap[ImGuiKey_Tab] = juce::KeyPress::tabKey;
    io.KeyMap[ImGuiKey_LeftArrow] = juce::KeyPress::leftKey + offset_for_function_keys;
    io.KeyMap[ImGuiKey_RightArrow] = juce::KeyPress::rightKey + offset_for_function_keys;
    io.KeyMap[ImGuiKey_UpArrow] = juce::KeyPress::upKey + offset_for_function_keys;
    io.KeyMap[ImGuiKey_DownArrow] = juce::KeyPress::downKey + offset_for_function_keys;
    io.KeyMap[ImGuiKey_PageUp] = juce::KeyPress::pageUpKey + offset_for_function_keys;
    io.KeyMap[ImGuiKey_PageDown] = juce::KeyPress::pageDownKey + offset_for_function_keys;
    io.KeyMap[ImGuiKey_Home] = juce::KeyPress::homeKey + offset_for_function_keys;
    io.KeyMap[ImGuiKey_End] = juce::KeyPress::endKey + offset_for_function_keys;
    io.KeyMap[ImGuiKey_Insert] = juce::KeyPress::insertKey + offset_for_function_keys;
    io.KeyMap[ImGuiKey_Delete] = juce::KeyPress::deleteKey + offset_for_function_keys;
    io.KeyMap[ImGuiKey_Backspace] = juce::KeyPress::backspaceKey;
    io.KeyMap[ImGuiKey_Space] = juce::KeyPress::spaceKey;
    io.KeyMap[ImGuiKey_Enter] = 13;
    io.KeyMap[ImGuiKey_Escape] = juce::KeyPress::escapeKey;
    io.KeyMap[ImGuiKey_KeyPadEnter] = 13;
    io.KeyMap[ImGuiKey_A] = 'A';
    io.KeyMap[ImGuiKey_C] = 'C';
    io.KeyMap[ImGuiKey_V] = 'V';
    io.KeyMap[ImGuiKey_X] = 'X';
    io.KeyMap[ImGuiKey_Y] = 'Y';
    io.KeyMap[ImGuiKey_Z] = 'Z';

    for (int n = 0; n < ImGuiKey_COUNT; ++n) {
        if (io.KeyMap[n] < -1 || io.KeyMap[n] >= IM_ARRAYSIZE(io.KeysDown)) {
            io.KeyMap[n] = -1;
        }
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

static void ImGui_ImplJUCE_UpdateMouseCursor(juce::Component *component) {
    ImGuiIO &io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_NoMouseCursorChange) {
        return;
    }
    ImGuiMouseCursor imgui_cursor = ImGui::GetMouseCursor();
    if (io.MouseDrawCursor || imgui_cursor == ImGuiMouseCursor_None) {
        if (!g_MouseCursorHidden) {
            g_MouseCursorHidden = true;
            component->setMouseCursor(juce::MouseCursor::StandardCursorType::NoCursor);
        }
    } else {
        component->setMouseCursor(g_MouseCursors[imgui_cursor]);
        if (g_MouseCursorHidden) {
            g_MouseCursorHidden = false;
        }
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

    ImGui_ImplJUCE_UpdateMouseCursor(component);
}

static int mapCharacterToKey(int c) {
    if (c >= 'a' && c <= 'z') {
        return c - 'a' + 'A';
    }
    if (c >= 0 && c < 256) {
        return c;
    }
    if (c >= 0xF700 && c < 0xF700 + 256) {
        return c - 0xF700 + 256;
    }
    return -1;
}

static void resetKeys() {
    ImGuiIO &io = ImGui::GetIO();
    for (int n = 0; n < IM_ARRAYSIZE(io.KeysDown); ++n) {
        io.KeysDown[n] = false;
    }
}

void ImGui_ImplJUCE_HandleKeyPress(const juce::KeyPress &key) {
    ImGuiIO &io = ImGui::GetIO();
    juce::juce_wchar c = key.getTextCharacter();
    if (key.isCurrentlyDown() && c >= 32 && c < 127) {
        io.AddInputCharacter((unsigned int)c);
    }
    int keyCode = mapCharacterToKey(c);
    if (keyCode != -1) {
        if (key.isCurrentlyDown() && !io.KeyCtrl) {
            resetKeys();
        }
        io.KeysDown[keyCode] = true;
    }
}

void ImGui_ImplJUCE_HandleMouseMove(const juce::MouseEvent &event) {
    ImGuiIO &io = ImGui::GetIO();
    io.MousePos = ImVec2((float)event.getPosition().getX(), (float)event.getPosition().getY());
}

void ImGui_ImplJUCE_HandleMouseEnter(const juce::MouseEvent &event) {}

void ImGui_ImplJUCE_HandleMouseExit(const juce::MouseEvent &event) {}

void ImGui_ImplJUCE_HandleMouseDown(const juce::MouseEvent &event) {
    ImGuiIO &io = ImGui::GetIO();

    bool oldKeyCtrl = io.KeyCtrl;
    bool oldKeyShift = io.KeyShift;
    bool oldKeyAlt = io.KeyAlt;
    bool oldKeySuper = io.KeySuper;
    io.KeyCtrl = event.mods.isCtrlDown();
    io.KeyShift = event.mods.isShiftDown();
    io.KeyAlt = event.mods.isAltDown();
    io.KeySuper = event.mods.isCommandDown();

    if ((oldKeyShift && !io.KeyShift) || (oldKeyCtrl && !io.KeyCtrl) || (oldKeyAlt && !io.KeyAlt) ||
        (oldKeySuper && !io.KeySuper)) {
        resetKeys();
    }

    if (event.mods.isLeftButtonDown()) {
        io.MouseDown[0] = true;
    }
    if (event.mods.isRightButtonDown()) {
        io.MouseDown[0] = true;
    }
    if (event.mods.isMiddleButtonDown()) {
        io.MouseDown[0] = true;
    }
}

void ImGui_ImplJUCE_HandleMouseDrag(const juce::MouseEvent &event) {
    ImGuiIO &io = ImGui::GetIO();
    io.MousePos = ImVec2((float)event.getPosition().getX(), (float)event.getPosition().getY());
}

void ImGui_ImplJUCE_HandleMouseUp(const juce::MouseEvent &event) {
    ImGuiIO &io = ImGui::GetIO();

    bool oldKeyCtrl = io.KeyCtrl;
    bool oldKeyShift = io.KeyShift;
    bool oldKeyAlt = io.KeyAlt;
    bool oldKeySuper = io.KeySuper;
    io.KeyCtrl = event.mods.isCtrlDown();
    io.KeyShift = event.mods.isShiftDown();
    io.KeyAlt = event.mods.isAltDown();
    io.KeySuper = event.mods.isCommandDown();

    if ((oldKeyShift && !io.KeyShift) || (oldKeyCtrl && !io.KeyCtrl) || (oldKeyAlt && !io.KeyAlt) ||
        (oldKeySuper && !io.KeySuper)) {
        resetKeys();
    }

    if (event.mods.isLeftButtonDown()) {
        io.MouseDown[0] = false;
    }
    if (event.mods.isRightButtonDown()) {
        io.MouseDown[0] = false;
    }
    if (event.mods.isMiddleButtonDown()) {
        io.MouseDown[0] = false;
    }
}

void ImGui_ImplJUCE_HandleMouseDoubleClick(const juce::MouseEvent &event) {}

void ImGui_ImplJUCE_HandleMouseWheelMove(const juce::MouseEvent &event, const juce::MouseWheelDetails &wheel) {
    ImGuiIO &io = ImGui::GetIO();
    if (fabs(wheel.deltaX) > 0.0) {
        io.MouseWheelH += wheel.deltaX * 0.1f;
    }
    if (fabs(wheel.deltaY) > 0.0) {
        io.MouseWheel += wheel.deltaY * 0.1f;
    }
}

void ImGui_ImplJUCE_HandleMouseMagnify(const juce::MouseEvent &event, float scaleFactor) {
    ImGuiIO &io = ImGui::GetIO();
    io.FontGlobalScale *= scaleFactor;
}
