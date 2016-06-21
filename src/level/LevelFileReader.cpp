#include "LevelFileReader.h"
#include "ResourceManager.h"
#include "fstream"
#include "constants.h"
#include <StandardRenderer.h>

LevelFileReader::LevelFileReader() {
}

void LevelFileReader::parseObjects(const std::vector<std::vector<std::string>> &lines,
                      std::unordered_map<std::string, Mesh*> &meshMap, Scene* scene) {

    ShaderProgram* standardShader = ResourceManager::getShader(SIMPLE_SHADER_NAME);
    for (auto lineWords : lines) {
        std::string firstWord = lineWords.front();

        GameObject *g;
        if (firstWord == "Collider") {
            string mesh = lineWords[1];
            float lx = std::stof(lineWords[2]);
            float ly = std::stof(lineWords[3]);
            float lz = std::stof(lineWords[4]);

            float rx = std::stof(lineWords[5]);
            float ry = std::stof(lineWords[6]);
            float rz = std::stof(lineWords[7]);
            float ra = std::stof(lineWords[8]);

            float sx = std::stof(lineWords[9]);
            float sy = std::stof(lineWords[10]);
            float sz = std::stof(lineWords[11]);

            g = new GameObject(meshMap[mesh]);
            StandardRenderer *stdrenderer =
                    new StandardRenderer(meshMap[mesh], g, standardShader);
            g->addRenderComponent(stdrenderer);
            g->setLocation(make_vector(lx, ly, lz));
            g->setRotation(make_quaternion_axis_angle(make_vector(rx, ry, rz), ra));
            g->setScale(make_vector(sx, sy, sz));
        } else if (firstWord == "Trigger") {
            string mesh  = lineWords[1];
            string type  = lineWords[2];
            string value = lineWords[3];
            float lx = std::stof(lineWords[4]);
            float ly = std::stof(lineWords[5]);
            float lz = std::stof(lineWords[6]);

            float rx = std::stof(lineWords[7]);
            float ry = std::stof(lineWords[8]);
            float rz = std::stof(lineWords[9]);
            float ra = std::stof(lineWords[10]);

            float sx = std::stof(lineWords[11]);
            float sy = std::stof(lineWords[12]);
            float sz = std::stof(lineWords[13]);

            g = new GameObject(meshMap[mesh]);
            g->setLocation(make_vector(lx, ly, lz));
            g->setRotation(make_quaternion_axis_angle(make_vector(rx, ry, rz), ra));
            g->setScale(make_vector(sx, sy, sz));

            if (type == "BattleZone") {
                // Add components that handle battle spawning when walking in the zone
                // value can be used to determine what enemies to face
            } else if( type == "SceneSwitch" ) {
                // Component for switching to the Scene provided by value
            }

        } else {
            Logger::logWarning(firstWord + " is not a supported Level object type");
        }
        scene->addShadowCaster(g);
    }
}

Scene* LevelFileReader::read(const std::string &filename) {
    Scene* scene = new Scene();
    std::unordered_map<std::string, Mesh*> meshMap;
    std::vector<std::vector<std::string>> lines;

    std::string line;
    ifstream levelFile(filename.c_str());
    if (levelFile.is_open()) {
        while ( getline (levelFile,line) ) {
            std::vector<std::string> lineWords = words(line);
            std::string firstWord = lineWords.front();

            if (firstWord.front() != '#' && lineWords.size() > 0) {
                // Skip all comments and empty lines

                if (firstWord == "Mesh") {
                    // If we found a mesh we load it directly
                    Mesh *m = ResourceManager::loadAndFetchMesh(lineWords[2]);
                    meshMap.insert({lineWords[1], m});
                } else {
                    // Otherwise save it for later analysis after all meshes are loaded
                    lines.push_back(lineWords);
                }
            }
        }
        levelFile.close();
    }

    parseObjects(lines, meshMap, scene);

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
