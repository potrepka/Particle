#include "AudioSettings.h"

particle::AudioSettings::AudioSettings(Data &data)
        : Frame(data, "Audio Settings") {}

void particle::AudioSettings::drawInternal() {
    auto deviceSetup = getData().getAudioDeviceManager()->getAudioDeviceSetup();

    ImGui::Text("Input Device: %s", deviceSetup.inputDeviceName);
    ImGui::Text("Output Device: %s", deviceSetup.outputDeviceName);
    if (getData().getAudioDeviceManager()->getCurrentAudioDevice() != nullptr) {
        ImGui::Text("Sample Rate: %d",
                    getData().getAudioDeviceManager()->getCurrentAudioDevice()->getCurrentSampleRate());
        ImGui::Text("Buffer Size: %d",
                    getData().getAudioDeviceManager()->getCurrentAudioDevice()->getCurrentBufferSizeSamples());
        ImGui::Text("Bit Depth: %d", getData().getAudioDeviceManager()->getCurrentAudioDevice()->getCurrentBitDepth());
    }

    ImGui::Text("Device is using double precision: %d", getData().getAudioProcessor()->isUsingDoublePrecision());
}
