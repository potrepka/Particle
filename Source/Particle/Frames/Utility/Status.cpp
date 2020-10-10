#include "Status.h"

particle::Status::Status(Data &data)
        : Frame(data, "Status")
        , cpu(0.0)
        , fps(0.0) {}

void particle::Status::drawInternal() {
    getData().getNodeProcessor()->lock();
    std::vector<std::shared_ptr<dsp::Node>> &nodes = getData().getNodeProcessor()->getNodes();
    size_t numNodes = 0;
    size_t numActiveNodes = 0;
    size_t numConnections = 0;
    size_t numActiveConnections = 0;
    std::queue<std::shared_ptr<dsp::Node>> frontier;
    for (std::shared_ptr<dsp::Node> node : nodes) {
        frontier.push(node);
    }
    while (!frontier.empty()) {
        std::shared_ptr<dsp::Node> node = frontier.front();
        node->lock();
        ++numNodes;
        if (node->isActive()) {
            ++numActiveNodes;
        }
        for (std::shared_ptr<dsp::Input> input : node->getInputs()) {
            input->lock();
            for (std::shared_ptr<dsp::Output> output : input->getConnections()) {
                ++numConnections;
                if (node->isActive()) {
                    ++numActiveConnections;
                }
            }
            input->unlock();
        }
        for (std::shared_ptr<dsp::Node> child : node->getChildren()) {
            frontier.push(child);
        }
        node->unlock();
        frontier.pop();
    }
    getData().getNodeProcessor()->getAudioOutput()->lock();
    for (std::shared_ptr<dsp::Output> output : getData().getNodeProcessor()->getAudioOutput()->getConnections()) {
        ++numConnections;
        ++numActiveConnections;
    }
    getData().getNodeProcessor()->getAudioOutput()->unlock();
    getData().getNodeProcessor()->unlock();
    if (getData().getAudioDeviceManager() != nullptr) {
        cpu = getData().getAudioDeviceManager()->getCpuUsage();
    }
    fps = ImGui::GetIO().Framerate;
    ImGui::ProgressBar(cpu, ImVec2(-1, 0));
    ImGui::Text("%.f FPS", fps);
    ImGui::Text("Nodes: %ld/%ld", numActiveNodes, numNodes);
    ImGui::Text("Connections: %ld/%ld", numActiveConnections, numConnections);
}
