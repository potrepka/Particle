#include "imgui.h"
#include <juce_gui_basics/juce_gui_basics.h>

IMGUI_IMPL_API void ImGui_ImplJUCE_Init();
IMGUI_IMPL_API void ImGui_ImplJUCE_Shutdown();
IMGUI_IMPL_API void ImGui_ImplJUCE_NewFrame(juce::Component *component);
IMGUI_IMPL_API bool ImGui_ImplJUCE_HandleKeyPressed(const juce::KeyPress &key, juce::Component *originatingComponent);
IMGUI_IMPL_API bool ImGui_ImplJUCE_HandleKeyStateChanged(const bool isKeyDown, juce::Component *originatingComponent);
IMGUI_IMPL_API void ImGui_ImplJUCE_HandleMouseMove(const juce::MouseEvent &event);
IMGUI_IMPL_API void ImGui_ImplJUCE_HandleMouseEnter(const juce::MouseEvent &event);
IMGUI_IMPL_API void ImGui_ImplJUCE_HandleMouseExit(const juce::MouseEvent &event);
IMGUI_IMPL_API void ImGui_ImplJUCE_HandleMouseDown(const juce::MouseEvent &event);
IMGUI_IMPL_API void ImGui_ImplJUCE_HandleMouseDrag(const juce::MouseEvent &event);
IMGUI_IMPL_API void ImGui_ImplJUCE_HandleMouseUp(const juce::MouseEvent &event);
IMGUI_IMPL_API void ImGui_ImplJUCE_HandleMouseDoubleClick(const juce::MouseEvent &event);
IMGUI_IMPL_API void ImGui_ImplJUCE_HandleMouseWheelMove(const juce::MouseEvent &event,
                                                        const juce::MouseWheelDetails &wheel);
IMGUI_IMPL_API void ImGui_ImplJUCE_HandleMouseMagnify(const juce::MouseEvent &event, float scaleFactor);
