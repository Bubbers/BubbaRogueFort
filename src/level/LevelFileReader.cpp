#include "LevelFileReader.h"
#include "ResourceManager.h"
#include "fstream"
#include "constants.h"
#include <StandardRenderer.h>

LevelFileReader::LevelFileReader() {
}

void LevelFileReader::parseMeshes(const std::vector<std::string> &lines,
                                  std::unordered_map<std::string, Mesh *> &meshMap) {
    for (auto line : lines) {
        std::vector<string> lineWords = words(line);
        if (lineWords[0] == "Mesh") {
            Mesh *m = ResourceManager::loadAndFetchMesh(lineWords[2]);
            meshMap.insert({lineWords[1], m});
        }
    }
}

void LevelFileReader::parseGameObjects(const std::vector<std::string> &lines,
                      std::unordered_map<std::string, Mesh*> &meshMap, Scene* scene) {
    for (auto line : lines) {
        std::vector<string> lineWords = words(line);
        if (lineWords[0] == "GameObject") {
            GameObject *g;
            const std::string name = lineWords[1];

            /* Shader setup done once for all meshes that use it */
            ShaderProgram* standardShader = ResourceManager::getShader(SIMPLE_SHADER_NAME);

            if (lineWords.size() == 2) {
                g = new GameObject();
            } else if (lineWords.size() > 2) {
                string mesh = lineWords[2];
                if (lineWords.size() == 3) {
                    g = new GameObject(meshMap[mesh]);
                } else if (lineWords.size() == 4) {
                    string collider = lineWords[3];
                    g = new GameObject(meshMap[mesh], meshMap[collider]);
                }
                StandardRenderer* stdrenderer = new StandardRenderer(meshMap[mesh], g, standardShader);
                g->addRenderComponent(stdrenderer);

            } else {
                exit(-1);
            }

            g->setLocation(make_vector(0.0f, 0.0f, 0.0f));
            scene->addShadowCaster(g);
        }
    }
}

Scene* LevelFileReader::read(const std::string &filename) {
    Scene* scene = new Scene();
    std::unordered_map<std::string, Mesh*> meshMap;
    std::vector<std::string> lines;

    std::string line;
    ifstream levelFile(filename.c_str());
    if (levelFile.is_open()) {
        while ( getline (levelFile,line) ) {
            if (words(line).front().front() != '#') {
                lines.push_back(line);
            }
        }
        levelFile.close();
    }

    parseMeshes(lines, meshMap);
    parseGameObjects(lines, meshMap, scene);

    return scene;
}

std::vector<std::string> LevelFileReader::words(const std::string &str) {
    std::vector<std::string> words;
    words.push_back("");

    for (auto ch : str) {
        if (ch == ' ' || ch == '\n' || ch == '\t') {
            if (words.back().length() > 0) {
                words.push_back("");
            }
        } else {
            words.back().push_back(ch);
        }
    }

    if (words.back().empty()) {
        words.pop_back();
    }

    return words;
}
