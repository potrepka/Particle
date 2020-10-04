#include "RootView.h"

particle::RootView::RootView(juce::AudioProcessor *audioProcessor,
                             juce::AudioDeviceManager *audioDeviceManager,
                             dsp::NodeProcessor *nodeProcessor)
        : data(audioProcessor, audioDeviceManager, nodeProcessor)
        , audioSettings(data)
        , status(data)
        , nodeEditor(data) {
    audioSettings.show();
    status.show();
    nodeEditor.show();
}

particle::Data &particle::RootView::getData() {
    return data;
}

void particle::RootView::draw() {
    //static bool show_demo_window = true;
    //if (show_demo_window) {
    //ImGui::ShowDemoWindow(&show_demo_window);
    //}

    ImGui::DockSpaceOverViewport();

    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit")) {
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    audioSettings.draw();
    status.draw();
    nodeEditor.draw();
}
