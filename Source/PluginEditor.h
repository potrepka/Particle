#pragma once

#include "PluginProcessor.h"

#include "imgui_impl_opengl3.h"

class ParticleAudioProcessorEditor : public juce::AudioProcessorEditor,
                                     public juce::OpenGLRenderer,
                                     public juce::KeyListener {
public:
    ParticleAudioProcessorEditor(ParticleAudioProcessor &);
    ~ParticleAudioProcessorEditor() override;

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
    ParticleAudioProcessor &audioProcessor;

    juce::OpenGLContext openGLContext;

    ImVec4 backgroundColor = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ParticleAudioProcessorEditor)
};
