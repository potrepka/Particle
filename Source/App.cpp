#include "App.h"

#if JUCE_USE_CUSTOM_PLUGIN_STANDALONE_APP

particle::App::App() {
    juce::PluginHostType::jucePlugInClientCurrentWrapperType = juce::AudioProcessor::wrapperType_Standalone;
    juce::PropertiesFile::Options options;
    options.applicationName = getApplicationName();
    options.filenameSuffix = ".settings";
    options.osxLibrarySubFolder = "Application Support";
#if JUCE_LINUX
    options.folderName = "~/.config";
#else
    options.folderName = "";
#endif
    appProperties.setStorageParameters(options);
}

const juce::String particle::App::getApplicationName() {
    return JucePlugin_Name;
}

const juce::String particle::App::getApplicationVersion() {
    return JucePlugin_VersionString;
}

bool particle::App::moreThanOneInstanceAllowed() {
    return true;
}

void particle::App::anotherInstanceStarted(const juce::String &) {}

juce::StandaloneFilterWindow *particle::App::createWindow() {
#ifdef JucePlugin_PreferredChannelConfigurations
    StandalonePluginHolder::PluginInOuts channels[] = { JucePlugin_PreferredChannelConfigurations };
#endif
    return new juce::StandaloneFilterWindow(
            getApplicationName(),
            juce::LookAndFeel::getDefaultLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId),
            appProperties.getUserSettings(),
            false,
            {},
            nullptr
#ifdef JucePlugin_PreferredChannelConfigurations
            ,
            juce::Array<StandalonePluginHolder::PluginInOuts>(channels, juce::numElementsInArray(channels))
#else
            ,
            {}
#endif
#if JUCE_DONT_AUTO_OPEN_MIDI_DEVICES_ON_MOBILE
            ,
            false
#endif
    );
}

void particle::App::initialise(const juce::String &) {
    mainWindow.reset(createWindow());
#if JUCE_STANDALONE_FILTER_WINDOW_USE_KIOSK_MODE
    Desktop::getInstance().setKioskModeComponent(mainWindow.get(), false);
#endif
    mainWindow->setVisible(true);
}

void particle::App::shutdown() {
    mainWindow = nullptr;
    appProperties.saveIfNeeded();
}

void particle::App::systemRequestedQuit() {
    if (mainWindow.get() != nullptr) {
        mainWindow->pluginHolder->savePluginState();
    }
    if (juce::ModalComponentManager::getInstance()->cancelAllModalComponents()) {
        juce::Timer::callAfterDelay(100, []() {
            if (auto app = JUCEApplicationBase::getInstance()) {
                app->systemRequestedQuit();
            }
        });
    } else {
        quit();
    }
}

#endif
