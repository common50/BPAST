// self made .obj parser for my other stuff lmk if im messing up with legal (other ppls stuff) cus im 
// going to do this inn like the standard way so i might accidentally copy some1 else so pls lmk

// idk what im doinggg ghhghghhghhhhgghgghhgh

#pragma once
#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>

struct Meowdel {
    std::vector<float> vertexData;
    std::vector<unsigned int> indices;
};

Meowdel loadObj(const char* path) {
    Meowdel model;

    std::vector<glm::vec3> positions; // thanks glm
    std::vector<glm::vec3> normals;

    std::unordered_map<std::string, unsigned int> combinedLookup; // where does this one go??? ehh whatever it works

    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "obj loading isnt loading " << path << std::endl;
        return model;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string tag;
        ss >> tag;




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        // k no bs comments for this part cus its lowk hard we need to lock in
        // and no stupid names (ok maybe 1)
       if (tag == "v") {
            glm::vec3 pos;
            ss >> pos.x >> pos.y >> pos.z;
            positions.push_back(pos);

        } else if (tag == "vn") {
            glm::vec3 norm;
            ss >> norm.x >> norm.y >> norm.z;
            normals.push_back(norm);

        } else if (tag == "f") {
            std::string token;
            std::vector<unsigned int> faceIndices;

            while (ss >> token) {

                // so the f line looks like 1//3 or 1/2/3 (pos/tex/norm)
                // 1//3 means that there is no texcoord and 1/2/3 means that there is a texcoord
                // to get the pos n norm we gotta to find the first and second slash and then just
                // take everything before the first slash as pos and everything after the second as norm

                size_t firstMeow = token.find('/');
                // if we dont find a slash for some reason:
                if (firstMeow == std::string::npos) {
                    // so apparently it means the whole token is just the pos
                    // shouldnt happen with real files though
                    int posIdx = std::stoi(token);
                } else { // else if we DO find a slash
                    int posIdx = std::stoi(token.substr(0, firstMeow));
                    size_t secondMeow = token.find('/', firstMeow + 1);

                    // now we check the shape, whether its 1//3 or 1/2/3
                    if (secondMeow == firstMeow + 1) { // check if the slashes are adjecent

                        // if this is true there is no texcoord
                        // this means that the shape is 1//3 (cus the slashes are adjecent)

                        // so what we do is index it like this:
                        // 1 2 3 4
                        // 1 / / 3
                        // so the pos is 1, first slash is 2, second is 3 and the norm is 4

                        // so then we take chars 1-2 which are pos and 3-4 which are norm
                        int normIdx = std::stoi(token.substr(secondMeow + 1));
                        std::string key = std::to_string(posIdx) + "_" + std::to_string(normIdx);
                        auto it = combinedLookup.find(key); // dont ask me what auto means
                        if (it != combinedLookup.end()) {
                                faceIndices.push_back(it->second);
                        } else {
                            glm::vec3 pos = positions[posIdx - 1];
                            glm::vec3 norm = normals[normIdx - 1];
                            // push
                            model.vertexData.insert(model.vertexData.end(), {
                                pos.x, pos.y, pos.z,
                                0.7f, 0.7f, 0.7f, // hardcoded 4 now lmk if i forgot
                                norm.x, norm.y, norm.z
                            });

                            unsigned int newIndex = (unsigned int)(model.vertexData.size() / 9 - 1);
                            combinedLookup[key] = newIndex;
                            faceIndices.push_back(newIndex);
                        }


                    } else { // if has a texcoord:
                        
                        // in this case there is a texcoord because the slashes arent adjecent
                        // (since there is a texcoord in between them, duh)
                        // so the shape is 1/2/3

                        // first we go find the texcoord and subtract:
                        int texIdx = std::stoi(token.substr(firstMeow + 1, secondMeow - firstMeow - 1));

                        // so we make it look like this:
                        // 1 2   3 4
                        // 1 / 2 / 3
                        // so we skip the texcoord

                        // and then we do it as if there is no texcoord (since we skip the texcoord ofc)
                        int normIdx = std::stoi(token.substr(secondMeow + 1));
                        std::string key = std::to_string(posIdx) + "_" + std::to_string(normIdx);
                        auto it = combinedLookup.find(key);
                        if (it != combinedLookup.end()) {
                                faceIndices.push_back(it->second);
                        } else {
                            glm::vec3 pos = positions[posIdx - 1];
                            glm::vec3 norm = normals[normIdx - 1];
                            // pushggVG
                            model.vertexData.insert(model.vertexData.end(), {
                                pos.x, pos.y, pos.z,
                                0.7f, 0.7f, 0.7f, // same as b4
                                norm.x, norm.y, norm.z
                            });

                            unsigned int newIndex = (unsigned int)(model.vertexData.size() / 9 - 1);
                            combinedLookup[key] = newIndex;
                            faceIndices.push_back(newIndex);
                        }
                    }
                }
            }

            for (size_t i = 1; i + 1 < faceIndices.size(); i++) {
                model.indices.push_back(faceIndices[0]);
                model.indices.push_back(faceIndices[i]);
                model.indices.push_back(faceIndices[i + 1]);
            }
        }
    }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::cout << "parsed " << positions.size() << " positions, " << normals.size() << " normals" << std::endl;
    return model;
}

// -common50

// i just found out that "f 1 2 3" is also valid! isnt that great? because now my shitty parser wont work! fucking amazing!