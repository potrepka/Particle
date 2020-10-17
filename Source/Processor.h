#pragma once

#include "imgui_impl_opengl3.h"

#if !defined(IMGUI_IMPL_OPENGL_ES2) && !defined(IMGUI_IMPL_OPENGL_ES3)
#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h>
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h>
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD2)
#include <glad/gl.h>
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING2)
#include <glbinding/Binding.h>

#include <glbinding/gl/gl.h>
using namespace gl;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING3)
#include <glbinding/glbinding.h>

#include <glbinding/gl/gl.h>
using namespace gl;
#endif
#endif

#include "DSP.h"
#include "Particle.h"

#include "imgui_impl_juce.h"
#include "imnodes.h"
#include "implot.h"

#include "juce_audio_plugin_client/Standalone/juce_StandaloneFilterWindow.h"

namespace particle {

class Processor : public juce::AudioProcessor {

public:
    Processor();
    ~Processor() override;

    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

#ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported(const BusesLayout &layouts) const override;
#endif

    void processBlock(juce::AudioBuffer<float> &, juce::MidiBuffer &) override;
    void processBlock(juce::AudioBuffer<double> &, juce::MidiBuffer &) override;

    juce::AudioProcessorEditor *createEditor() override;
    bool hasEditor() const override;

    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram(int index) override;
    const juce::String getProgramName(int index) override;
    void changeProgramName(int index, const juce::String &newName) override;

    void getStateInformation(juce::MemoryBlock &destData) override;
    void setStateInformation(const void *data, int sizeInBytes) override;

    juce::AudioDeviceManager *getAudioDeviceManager();

    dsp::NodeProcessor &getNodeProcessor();
    particle::View &getView();

private:
    dsp::NodeProcessor nodeProcessor;
    particle::View view;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(particle::Processor)
};

} // namespace particle