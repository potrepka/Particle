#include "RootView.h"

particle::RootView::RootView(juce::AudioProcessor *audioProcessor,
                             juce::AudioDeviceManager *audioDeviceManager,
                             dsp::NodeProcessor *nodeProcessor)
        : data(audioProcessor, audioDeviceManager, nodeProcessor)
        , audioSettings(data)
        , status(data)
        , nodeEditor(data) {}

particle::Data &particle::RootView::getData() {
    return data;
}

void particle::RootView::draw() {
    //static bool show_demo_window = true;
    //if (show_demo_window) {
    //ImGui::ShowDemoWindow(&show_demo_window);
    //}

    //static ImGuiID dockspaceID = 0;

    //if (ImGui::Begin("Master Window" /*, nullptr, ImGuiWindowFlags_MenuBar*/)) {
    //    ImGui::TextUnformatted("DockSpace below");

    //    // Declare Central dockspace
    //    dockspaceID = ImGui::GetID("HUB_DockSpace");
    //    ImGui::DockSpace(dockspaceID,
    //                     ImVec2(0.0f, 0.0f),
    //                     ImGuiDockNodeFlags_None |
    //                             ImGuiDockNodeFlags_PassthruCentralNode /*|ImGuiDockNodeFlags_NoResize*/);
    //}
    //ImGui::End();

    //static bool open = true;

    //if (open) {
    //    ImGui::SetNextWindowDockID(dockspaceID, ImGuiCond_FirstUseEver);
    //    if (ImGui::Begin("Dockable Window", &open)) {
    //        ImGui::TextUnformatted("Test");
    //    }
    //    ImGui::End();
    //}
    audioSettings.draw();
    status.draw();
    nodeEditor.draw();
}
