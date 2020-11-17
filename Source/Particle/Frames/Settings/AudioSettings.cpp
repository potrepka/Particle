#include "AudioSettings.h"

particle::AudioSettings::AudioSettings(Data &data)
        : Frame(data, "Audio Settings") {}

void particle::AudioSettings::drawInternal() {
    if (getData().getAudioDeviceManager() != nullptr) {
        auto deviceSetup = getData().getAudioDeviceManager()->getAudioDeviceSetup();

        ImGui::Text("Input Device: %s", deviceSetup.inputDeviceName.toStdString().c_str());
        ImGui::Text("Output Device: %s", deviceSetup.outputDeviceName.toStdString().c_str());
        if (getData().getAudioDeviceManager()->getCurrentAudioDevice() != nullptr) {
            ImGui::Text("Sample Rate: %.0f",
                        getData().getAudioDeviceManager()->getCurrentAudioDevice()->getCurrentSampleRate());
            ImGui::Text("Buffer Size: %d",
                        getData().getAudioDeviceManager()->getCurrentAudioDevice()->getCurrentBufferSizeSamples());
            ImGui::Text("Bit Depth: %d",
                        getData().getAudioDeviceManager()->getCurrentAudioDevice()->getCurrentBitDepth());
        }
    }

    ImGui::Text("Device is using double precision: %d", getData().getAudioProcessor()->isUsingDoublePrecision());
}
