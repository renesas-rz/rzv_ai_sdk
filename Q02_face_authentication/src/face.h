/***********************************************************************************************************************
* Copyright 2024 Renesas Electronics Corporation
* 
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
* 
* http://www.apache.org/licenses/LICENSE-2.0
* 
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
***********************************************************************************************************************/

#ifndef FACE_H
#define FACE_H
#include <vector>
#include <string>
#include <cmath>
#include <iostream>

class Face
{
    public:
        Face(): image_arr1(512), image_arr2(512) {}
        std::string compare_with_existing_faces();
        void setImage_arr1(std::vector<float> newValue);
        void setImage_arr2(std::vector<float> newValue);
        const std::vector<float>& getImage_arr1() const;
        const std::vector<float>& getImage_arr2() const;

    private:
        std::vector<float> image_arr1;
        std::vector<float> image_arr2;
        float euclidean_distance(int n);
        float cosine_similarity();
};

#endif