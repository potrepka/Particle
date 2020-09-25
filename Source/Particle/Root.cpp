#include "Root.h"

particle::Root::Root()
        : nodeEditor(data) {
    imnodes::Initialize();
    imnodes::SetNodeGridSpacePos(0, ImVec2(100.0f, 100.0f));
}

particle::Root::~Root() {
    imnodes::Shutdown();
}

particle::Data &particle::Root::getData() {
    return data;
}

void particle::Root::draw() {
    // static bool show_demo_window = true;
    // if (show_demo_window) {
    //    ImGui::ShowDemoWindow(&show_demo_window);
    //}
    // ImGui::Begin("FPS Window");
    // ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
    // ImGui::Text("DOUBLE PRECISON for audio device processing: %d", audioProcessor.isUsingDoublePrecision());
    // ImGui::End();

    // static ImGuiID dockspaceID = 0;
    // if (ImGui::Begin("Master Window" /*, nullptr, ImGuiWindowFlags_MenuBar*/)) {
    //    ImGui::TextUnformatted("DockSpace below");

    //    // Declare Central dockspace
    //    dockspaceID = ImGui::GetID("HUB_DockSpace");
    //    ImGui::DockSpace(dockspaceID,
    //                     ImVec2(0.0f, 0.0f),
    //                     ImGuiDockNodeFlags_None |
    //                             ImGuiDockNodeFlags_PassthruCentralNode /*|ImGuiDockNodeFlags_NoResize*/);
    //}
    // ImGui::End();

    // ImGui::SetNextWindowDockID(dockspaceID, ImGuiCond_FirstUseEver);
    // if (ImGui::Begin("Dockable Window")) {
    //    ImGui::TextUnformatted("Test");
    //}
    // ImGui::End();

    nodeEditor.draw();
}
