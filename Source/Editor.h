#pragma once

#include "Processor.h"

#include "imgui_impl_opengl3.h"

namespace particle {

class Editor : public juce::AudioProcessorEditor, public juce::OpenGLRenderer, public juce::KeyListener {

public:
    Editor(Processor &p);
    ~Editor() override;

    //==============================================================================
    void paint(juce::Graphics &) override;
    void resized() override;

    void newOpenGLContextCreated() override;
    void renderOpenGL() override;
    void openGLContextClosing() override;

    bool keyPressed(const juce::KeyPress &key, Component *originatingComponent) override;
    bool keyStateChanged(bool isKeyDown, Component *originatingComponent) override;

    void mouseMove(const juce::MouseEvent &event) override;
    void mouseEnter(const juce::MouseEvent &event) override;
    void mouseExit(const juce::MouseEvent &event) override;
    void mouseDown(const juce::MouseEvent &event) override;
    void mouseDrag(const juce::MouseEvent &event) override;
    void mouseUp(const juce::MouseEvent &event) override;
    void mouseDoubleClick(const juce::MouseEvent &event) override;
    void mouseWheelMove(const juce::MouseEvent &event, const juce::MouseWheelDetails &wheel) override;
    void mouseMagnify(const juce::MouseEvent &event, float scaleFactor) override;

private:
    particle::Processor &processor;
    juce::OpenGLContext openGLContext;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(particle::Editor)
};

} // namespace particle
