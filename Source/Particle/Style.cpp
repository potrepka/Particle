#include "Style.h"

const float particle::Style::GRAY_0 = 0.0f;
const float particle::Style::GRAY_1 = 0.0625f;
const float particle::Style::GRAY_2 = 0.125f;
const float particle::Style::GRAY_3 = 0.1875f;
const float particle::Style::GRAY_4 = 0.25f;
const float particle::Style::GRAY_5 = 0.3125f;
const float particle::Style::GRAY_6 = 0.375f;
const float particle::Style::GRAY_7 = 0.4375f;
const float particle::Style::GRAY_8 = 0.5f;
const float particle::Style::GRAY_9 = 0.5625f;
const float particle::Style::GRAY_10 = 0.625f;
const float particle::Style::GRAY_11 = 0.6875f;
const float particle::Style::GRAY_12 = 0.75f;
const float particle::Style::GRAY_13 = 0.8125f;
const float particle::Style::GRAY_14 = 0.875f;
const float particle::Style::GRAY_15 = 0.9375f;
const float particle::Style::GRAY_16 = 1.0f;
const ImColor particle::Style::TRANSPARENT = ImColor(0.0f, 0.0f, 0.0f, 0.0f);

particle::Style::Style()
        : theme(Theme::CUSTOM)
        , transparency(1.0f) {}

void particle::Style::setup() {
    // TODO: persist theme between runs
    light();

    setSizes();
}

particle::Style::Theme particle::Style::getTheme() const {
    return theme;
}

float particle::Style::getTransparency() const {
    return transparency;
}

void particle::Style::dark(const float transparency) {
    theme = Theme::DARK;
    this->transparency = transparency;

    ImVec4 background = ImVec4(GRAY_1, GRAY_1, GRAY_1, transparency);
    ImVec4 background_active = ImVec4(GRAY_3, GRAY_3, GRAY_3, transparency);

    ImVec4 frame = ImVec4(GRAY_4, GRAY_4, GRAY_4, transparency);
    ImVec4 frame_hover = ImVec4(GRAY_3, GRAY_3, GRAY_3, transparency);
    ImVec4 frame_active = ImVec4(GRAY_2, GRAY_2, GRAY_2, transparency);

    ImVec4 item = ImVec4(GRAY_7, GRAY_7, GRAY_7, transparency);
    ImVec4 item_hover = ImVec4(GRAY_6, GRAY_6, GRAY_6, transparency);
    ImVec4 item_active = ImVec4(GRAY_5, GRAY_5, GRAY_5, transparency);

    ImVec4 accent = ImColor(GRAY_14, GRAY_0, GRAY_0, transparency);
    ImVec4 accent_hover = ImColor(GRAY_13, GRAY_0, GRAY_0, transparency);
    ImVec4 accent_active = ImColor(GRAY_12, GRAY_0, GRAY_0, transparency);

    ImVec4 text = ImVec4(GRAY_16, GRAY_16, GRAY_16, GRAY_16);
    ImVec4 text_disabled = ImVec4(GRAY_10, GRAY_10, GRAY_10, GRAY_16);

    setColors(background,
              background_active,
              frame,
              frame_hover,
              frame_active,
              item,
              item_hover,
              item_active,
              accent,
              accent_hover,
              accent_active,
              text,
              text_disabled);
}

void particle::Style::light(const float transparency) {
    theme = Theme::LIGHT;
    this->transparency = transparency;

    ImVec4 background = ImColor(GRAY_15, GRAY_15, GRAY_15, transparency);
    ImVec4 background_active = ImColor(GRAY_13, GRAY_13, GRAY_13, transparency);

    ImVec4 frame = ImColor(GRAY_12, GRAY_12, GRAY_12, transparency);
    ImVec4 frame_hover = ImColor(GRAY_13, GRAY_13, GRAY_13, transparency);
    ImVec4 frame_active = ImColor(GRAY_14, GRAY_14, GRAY_14, transparency);

    ImVec4 item = ImColor(GRAY_9, GRAY_9, GRAY_9, transparency);
    ImVec4 item_hover = ImColor(GRAY_10, GRAY_10, GRAY_10, transparency);
    ImVec4 item_active = ImColor(GRAY_11, GRAY_11, GRAY_11, transparency);

    ImVec4 accent = ImColor(GRAY_16, GRAY_0, GRAY_0, transparency);
    ImVec4 accent_hover = ImColor(GRAY_15, GRAY_0, GRAY_0, transparency);
    ImVec4 accent_active = ImColor(GRAY_14, GRAY_0, GRAY_0, transparency);

    ImVec4 text = ImColor(GRAY_0, GRAY_0, GRAY_0, GRAY_16);
    ImVec4 text_disabled = ImColor(GRAY_6, GRAY_6, GRAY_6, GRAY_16);

    setColors(background,
              background_active,
              frame,
              frame_hover,
              frame_active,
              item,
              item_hover,
              item_active,
              accent,
              accent_hover,
              accent_active,
              text,
              text_disabled);
}

void particle::Style::custom(const ImColor &background,
                             const ImColor &background_active,
                             const ImColor &frame,
                             const ImColor &frame_hover,
                             const ImColor &frame_active,
                             const ImColor &item,
                             const ImColor &item_hover,
                             const ImColor &item_active,
                             const ImColor &accent,
                             const ImColor &accent_hover,
                             const ImColor &accent_active,
                             const ImColor &text,
                             const ImColor &text_disabled,
                             const float transparency) {
    theme = Theme::CUSTOM;
    this->transparency = transparency;

    ImVec4 background_w = ImColor(background.Value.x, background.Value.y, background.Value.z, transparency);
    ImVec4 background_active_w =
            ImColor(background_active.Value.x, background_active.Value.y, background_active.Value.z, transparency);

    ImVec4 frame_w = ImColor(frame.Value.x, frame.Value.y, frame.Value.z, transparency);
    ImVec4 frame_hover_w = ImColor(frame_hover.Value.x, frame_hover.Value.y, frame_hover.Value.z, transparency);
    ImVec4 frame_active_w = ImColor(frame_active.Value.x, frame_active.Value.y, frame_active.Value.z, transparency);

    ImVec4 item_w = ImColor(item.Value.x, item.Value.y, item.Value.z, transparency);
    ImVec4 item_hover_w = ImColor(item_hover.Value.x, item_hover.Value.y, item_hover.Value.z, transparency);
    ImVec4 item_active_w = ImColor(item_active.Value.x, item_active.Value.y, item_active.Value.z, transparency);

    ImVec4 accent_w = ImColor(accent.Value.x, accent.Value.y, accent.Value.z, transparency);
    ImVec4 accent_hover_w = ImColor(accent_hover.Value.x, accent_hover.Value.y, accent_hover.Value.z, transparency);
    ImVec4 accent_active_w = ImColor(accent_active.Value.x, accent_active.Value.y, accent_active.Value.z, transparency);

    ImVec4 text_w = ImColor(text.Value.x, text.Value.y, text.Value.z, GRAY_16);
    ImVec4 text_disabled_w = ImColor(text_disabled.Value.x, text_disabled.Value.y, text_disabled.Value.z, GRAY_16);

    setColors(background_w,
              background_active_w,
              frame_w,
              frame_hover_w,
              frame_active_w,
              item_w,
              item_hover_w,
              item_active_w,
              accent_w,
              accent_hover_w,
              accent_active_w,
              text_w,
              text_disabled_w);
}

void particle::Style::setColors(const ImColor &background,
                                const ImColor &background_active,
                                const ImColor &frame,
                                const ImColor &frame_hover,
                                const ImColor &frame_active,
                                const ImColor &item,
                                const ImColor &item_hover,
                                const ImColor &item_active,
                                const ImColor &accent,
                                const ImColor &accent_hover,
                                const ImColor &accent_active,
                                const ImColor &text,
                                const ImColor &text_disabled) {
    {
        ImGuiStyle &style = ImGui::GetStyle();
        style.Colors[ImGuiCol_Text] = text;
        style.Colors[ImGuiCol_TextDisabled] = text_disabled;
        style.Colors[ImGuiCol_WindowBg] = background;
        style.Colors[ImGuiCol_ChildBg] = TRANSPARENT;
        style.Colors[ImGuiCol_PopupBg] = background;
        style.Colors[ImGuiCol_Border] = item_active;
        style.Colors[ImGuiCol_BorderShadow] = TRANSPARENT;
        style.Colors[ImGuiCol_FrameBg] = frame;
        style.Colors[ImGuiCol_FrameBgHovered] = frame_hover;
        style.Colors[ImGuiCol_FrameBgActive] = frame_active;
        style.Colors[ImGuiCol_TitleBg] = background;
        style.Colors[ImGuiCol_TitleBgActive] = background_active;
        style.Colors[ImGuiCol_TitleBgCollapsed] = background;
        style.Colors[ImGuiCol_MenuBarBg] = background;
        style.Colors[ImGuiCol_ScrollbarBg] = background;
        style.Colors[ImGuiCol_ScrollbarGrab] = frame_active;
        style.Colors[ImGuiCol_ScrollbarGrabHovered] = frame_hover;
        style.Colors[ImGuiCol_ScrollbarGrabActive] = frame;
        style.Colors[ImGuiCol_CheckMark] = item;
        style.Colors[ImGuiCol_SliderGrab] = item;
        style.Colors[ImGuiCol_SliderGrabActive] = item;
        style.Colors[ImGuiCol_Button] = frame;
        style.Colors[ImGuiCol_ButtonHovered] = frame_hover;
        style.Colors[ImGuiCol_ButtonActive] = frame_active;
        style.Colors[ImGuiCol_Header] = background;
        style.Colors[ImGuiCol_HeaderHovered] = background_active;
        style.Colors[ImGuiCol_HeaderActive] = background_active;
        style.Colors[ImGuiCol_Separator] = item_active;
        style.Colors[ImGuiCol_SeparatorHovered] = item_hover;
        style.Colors[ImGuiCol_SeparatorActive] = item;
        style.Colors[ImGuiCol_ResizeGrip] = TRANSPARENT;
        style.Colors[ImGuiCol_ResizeGripHovered] = item_hover;
        style.Colors[ImGuiCol_ResizeGripActive] = item;
        style.Colors[ImGuiCol_Tab] = background_active;
        style.Colors[ImGuiCol_TabHovered] = background;
        style.Colors[ImGuiCol_TabActive] = background;
        style.Colors[ImGuiCol_TabUnfocused] = background;
        style.Colors[ImGuiCol_TabUnfocusedActive] = background_active;
        style.Colors[ImGuiCol_DockingPreview] = item_hover;
        style.Colors[ImGuiCol_DockingEmptyBg] = ImColor(0.0f, 1.0f, 0.0f, 1.0f);
        style.Colors[ImGuiCol_PlotLines] = item;
        style.Colors[ImGuiCol_PlotLinesHovered] = accent_hover;
        style.Colors[ImGuiCol_PlotHistogram] = item;
        style.Colors[ImGuiCol_PlotHistogramHovered] = accent_hover;
        style.Colors[ImGuiCol_TextSelectedBg] = background;
        style.Colors[ImGuiCol_DragDropTarget] = background;
        style.Colors[ImGuiCol_NavHighlight] = ImColor(1.0f, 0.0f, 0.0f, 1.0f);
        style.Colors[ImGuiCol_NavWindowingHighlight] = TRANSPARENT;
        style.Colors[ImGuiCol_NavWindowingDimBg] = ImColor(1.0f, 0.0f, 1.0f, 1.0f);
        style.Colors[ImGuiCol_ModalWindowDimBg] = background_active;
    }
    {
        imnodes::Style &style = imnodes::GetStyle();
        style.colors[imnodes::ColorStyle_NodeBackground] = background;
        style.colors[imnodes::ColorStyle_NodeBackgroundHovered] = background;
        style.colors[imnodes::ColorStyle_NodeBackgroundSelected] = background;
        style.colors[imnodes::ColorStyle_NodeOutline] = item_active;
        style.colors[imnodes::ColorStyle_TitleBar] = background;
        style.colors[imnodes::ColorStyle_TitleBarHovered] = background;
        style.colors[imnodes::ColorStyle_TitleBarSelected] = background_active;
        style.colors[imnodes::ColorStyle_Link] = item;
        style.colors[imnodes::ColorStyle_LinkHovered] = item_hover;
        style.colors[imnodes::ColorStyle_LinkSelected] = accent_active;
        style.colors[imnodes::ColorStyle_Pin] = item;
        style.colors[imnodes::ColorStyle_PinHovered] = item_hover;
        style.colors[imnodes::ColorStyle_BoxSelector] = TRANSPARENT;
        style.colors[imnodes::ColorStyle_BoxSelectorOutline] = item_active;
        style.colors[imnodes::ColorStyle_GridBackground] = TRANSPARENT;
        style.colors[imnodes::ColorStyle_GridLine] = frame;
    }
}

void particle::Style::setSizes() {
    {
        ImGuiStyle &style = ImGui::GetStyle();
        // TODO: You can remove this whole block, or add more
        style.TabRounding = 4.0f;
    }
    {
        imnodes::Style &style = imnodes::GetStyle();
        style.grid_spacing = 20.0f;
        style.node_corner_rounding = 7.0f;
        style.link_thickness = 2.5f;
        style.pin_quad_side_length = 7.5f;
        style.pin_offset = 0.0f;
    }
}
