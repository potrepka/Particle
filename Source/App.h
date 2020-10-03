#pragma once

#include <JuceHeader.h>

#if JUCE_USE_CUSTOM_PLUGIN_STANDALONE_APP

#include <juce_audio_plugin_client/Standalone/juce_StandaloneFilterWindow.h>

namespace particle {

class App : public juce::JUCEApplication {

public:
    App();

    const juce::String getApplicationName() override;
    const juce::String getApplicationVersion() override;

    bool moreThanOneInstanceAllowed() override;
    void anotherInstanceStarted(const juce::String &) override;

    virtual juce::StandaloneFilterWindow *createWindow();

    void initialise(const juce::String &) override;
    void shutdown() override;
    void systemRequestedQuit() override;

protected:
    juce::ApplicationProperties appProperties;
    std::unique_ptr<juce::StandaloneFilterWindow> mainWindow;
};

} // namespace particle

#if JucePlugin_Build_Standalone && JUCE_IOS
bool JUCE_CALLTYPE juce_isInterAppAudioConnected() {
    if (auto holder = juce::StandalonePluginHolder::getInstance()) {
        return holder->isInterAppAudioConnected();
    }
    return false;
}

void JUCE_CALLTYPE juce_switchToHostApplication() {
    if (auto holder = juce::StandalonePluginHolder::getInstance()) {
        holder->switchToHostApplication();
    }
}

juce::Image JUCE_CALLTYPE juce_getIAAHostIcon(int size) {
    if (auto holder = juce::StandalonePluginHolder::getInstance()) {
        return holder->getIAAHostIcon(size);
    }
    return juce::Image();
}
#endif

#endif

START_JUCE_APPLICATION(particle::App)
