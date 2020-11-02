#pragma once

#include "imgui.h"
#include "imnodes.h"
#include "implot.h"

#include <ctime>

namespace particle {

class Style {

public:
    enum class Theme { CUSTOM, DARK, LIGHT };

    static const float GRAY_0;
    static const float GRAY_1;
    static const float GRAY_2;
    static const float GRAY_3;
    static const float GRAY_4;
    static const float GRAY_5;
    static const float GRAY_6;
    static const float GRAY_7;
    static const float GRAY_8;
    static const float GRAY_9;
    static const float GRAY_10;
    static const float GRAY_11;
    static const float GRAY_12;
    static const float GRAY_13;
    static const float GRAY_14;
    static const float GRAY_15;
    static const float GRAY_16;
    static const ImColor TRANSPARENT;

    ImVec4 backgroundColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

    const ImVec2 windowPadding = ImVec2(8.0f, 8.0f);
    const ImVec2 framePadding = ImVec2(4.0f, 4.0f);
    const ImVec2 nodeFramePadding = ImVec2(4.0f, 2.0f);

    const float windowRounding = 0.0f;
    const float frameRounding = 0.0f;
    const float tabRounding = 0.0f;
    const float gridSize = 300.0f;
    const float nodeCornerRounding = 6.0f;
    const float nodeBorderThickness = 1.25f;
    const float linkThickness = 2.5f;
    const float pinSize = 7.5f;

    Style();

    void setup();

    Theme getTheme() const;
    float getTransparency() const;

    void dark(const float transparency = 1.0f);
    void light(const float transparency = 1.0f);
    void custom(const ImColor &background,
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
                const float transparency = 1.0f);

private:
    Theme theme;
    float transparency;

    void setColors(const ImColor &background,
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
                   const ImColor &text_disabled);
    void setSizes();
};

} // namespace particle
