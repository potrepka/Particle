#include "NodeEditor.h"

particle::NodeEditor::NodeEditor(Data &data)
        : Frame(data, "Node Editor") {}

void particle::NodeEditor::drawInternal() {
    imnodes::BeginNodeEditor();

    int id = 0;

    // NODE 1
    imnodes::BeginNode(id++);

    imnodes::BeginNodeTitleBar();
    ImGui::TextUnformatted("sample");
    imnodes::EndNodeTitleBar();

    ImGui::BeginGroup();

    imnodes::BeginInputAttribute(id++);
    ImGui::Text("freq");
    imnodes::EndInputAttribute();
    
    imnodes::BeginInputAttribute(id++);
    ImGui::Text("amp");
    imnodes::EndInputAttribute();

    ImGui::EndGroup();

    ImGui::SameLine(0);

    ImGui::BeginChild("Child", ImVec2(200, 200));
    ImGui::EndChild();

    ImGui::SameLine(0);

    ImGui::BeginGroup();

    imnodes::BeginOutputAttribute(id++);
    ImGui::Text("output");
    imnodes::EndOutputAttribute();

    imnodes::BeginOutputAttribute(id++);
    ImGui::Text("time");
    imnodes::EndOutputAttribute();

    ImGui::EndGroup();

    imnodes::EndNode();

    // NODE 2
    imnodes::BeginNode(id++);

    imnodes::BeginNodeTitleBar();
    ImGui::TextUnformatted("example");
    imnodes::EndNodeTitleBar();

    ImGui::BeginGroup();

    imnodes::BeginInputAttribute(id++);
    ImGui::Text("trigger");
    imnodes::EndInputAttribute();

    ImGui::EndGroup();

    ImGui::SameLine();

    ImGui::BeginGroup();

    imnodes::BeginOutputAttribute(id++);
    ImGui::Text("phase");
    imnodes::EndOutputAttribute();

    ImGui::EndGroup();

    imnodes::EndNode();

    imnodes::EndNodeEditor();
}
