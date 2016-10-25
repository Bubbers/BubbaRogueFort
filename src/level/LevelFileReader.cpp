#include <Scene.h>
#include "LevelFileReader.h"
#include "ResourceManager.h"
#include "fstream"
#include "constants.h"
#include "components/SceneSwitchOnCollisionComponent.h"
#include <StandardRenderer.h>
#include "Logger.h"
#include "GameObject.h"
#include "scenes/RogueFortScene.h"

using namespace chag;
using namespace std;

LevelFileReader::LevelFileReader() {
}

void LevelFileReader::parseObjects(const std::vector<std::vector<std::string>> &lines,
                      std::unordered_map<std::string, std::shared_ptr<Mesh>> &meshMap, Scene* scene, RogueFortScene *rogueFortScene) {

    std::shared_ptr<ShaderProgram> standardShader = ResourceManager::loadAndFetchShaderProgram(SIMPLE_SHADER_NAME, "../shader/simple.vert", "../shader/simple.frag");
    for (auto lineWords : lines) {
        std::string firstWord = lineWords.front();

        std::shared_ptr<GameObject> g;
        if (firstWord == "Collider") {
            string mesh = lineWords[1];
            bool   transparent = lineWords[2] == "true";
            float lx = std::stof(lineWords[3]);
            float ly = std::stof(lineWords[4]);
            float lz = std::stof(lineWords[5]);

            float rx = std::stof(lineWords[6]);
            float ry = std::stof(lineWords[7]);
            float rz = std::stof(lineWords[8]);
            float ra = std::stof(lineWords[9]);

            float sx = std::stof(lineWords[10]);
            float sy = std::stof(lineWords[11]);
            float sz = std::stof(lineWords[12]);

            g = std::make_shared<GameObject>(meshMap[mesh]);
            g->setIdentifier(1);

            StandardRenderer *stdrenderer =
                    new StandardRenderer(meshMap[mesh], standardShader);
            g->addRenderComponent(stdrenderer);
            g->setLocation(make_vector(lx, ly, lz));
            g->setRotation(make_quaternion_axis_angle(make_vector(rx, ry, rz), ra));
            g->setScale(make_vector(sx, sy, sz));

            if (transparent) {
                scene->addTransparentObject(g);
            } else {
                scene->addShadowCaster(g);
            }
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

            g = std::make_shared<GameObject>(meshMap[mesh]);
            g->setLocation(make_vector(lx, ly, lz));
            g->setRotation(make_quaternion_axis_angle(make_vector(rx, ry, rz), ra));
            g->setScale(make_vector(sx, sy, sz));
            g->setIdentifier(3);
            g->addCollidesWith(0);

            if (type == "BattleZone") {
                // Add components that handle battle spawning when walking in the zone
                // value can be used to determine what enemies to face
            } else if( type == "SceneSwitch" ) {
                // Component for switching to the Scene provided by value
                g->addComponent(new SceneSwitchOnCollisionComponent(rogueFortScene, value));
            }

            scene->addShadowCaster(g);


        } else {
            Logger::logWarning(firstWord + " is not a supported Level object type");
        }

    }
}

Scene* LevelFileReader::read(const std::string &filename, RogueFortScene *rogueFortScene) {
    Scene* scene = new Scene();
    std::unordered_map<std::string, std::shared_ptr<Mesh>> meshMap;
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
                    std::shared_ptr<Mesh> m = ResourceManager::loadAndFetchMesh(lineWords[2]);
                    meshMap.insert({lineWords[1], m});
                } else {
                    // Otherwise save it for later analysis after all meshes are loaded
                    lines.push_back(lineWords);
                }
            }
        }
        levelFile.close();
    }

    parseObjects(lines, meshMap, scene, rogueFortScene);

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
