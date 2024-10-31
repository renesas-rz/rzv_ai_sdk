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
#include "face.h"

/*****************************************
 * Function Name : setImage_arr1
 * Description   : Setter for image_arr1
 * Arguments     : newValue = std::vector<float>
 ******************************************/
void Face::setImage_arr1(const std::vector<float> newValue) {
        image_arr1 = newValue;
}

/*****************************************
 * Function Name : setImage_arr2
 * Description   : Setter for image_arr2
 * Arguments     : newValue = std::vector<float>
 ******************************************/
void Face::setImage_arr2(const std::vector<float> newValue) {
        image_arr2 = newValue;
}

/*****************************************
 * Function Name : getImage_arr1
 * Description   : Getter for image_arr1
 * Return value  : image_arr1 = std::vector<float>
 ******************************************/
const std::vector<float>& Face::getImage_arr1() const {
        return image_arr1;
}

/*****************************************
 * Function Name : getImage_arr2
 * Description   : Getter for image_arr2
 * Return value  : image_arr2 = std::vector<float>
 ******************************************/
const std::vector<float>& Face::getImage_arr2() const {
        return image_arr2;
}

/*****************************************
 * Function Name : cosine_similarity
 * Description   : This function computes the cosine similarity between two input
 *                 feature vectors represented as std::vector<float>.
 * Return value  : float value that represents the cosine similarity
 *                 between the two input feature vectors.
 ******************************************/
float Face::cosine_similarity()
{
    if ((image_arr1.empty() || image_arr2.empty()) || (image_arr1.size() != image_arr2.size()))
        return 0.0;
    float dot_product = 0.0;
    for (int i = 0; i < image_arr1.size(); i++)
    {
        dot_product += image_arr1[i] * image_arr2[i];
    }
    float norm1 = 0.0;
    float norm2 = 0.0;
    for (int i = 0; i < image_arr1.size(); i++)
    {
        norm1 += image_arr1[i] * image_arr1[i];
        norm2 += image_arr2[i] * image_arr2[i];
    }
    norm1 = std::sqrt(norm1);
    norm2 = std::sqrt(norm2);
    float similarity = 0.0;
    if (norm1 != 0.0 && norm2 != 0.0)
    {
        similarity = dot_product / (norm1 * norm2);
    }
    return similarity;
}

/*****************************************
 * Function Name : euclidean_distance
 * Description   : This function takes two vectors of floats (a and b)
 *                 and an integer n as parameters and returns a float representing the Euclidean distance between the two vectors.
 * Arguments     : n = int, size of vector
 * Return value  : float value representing the Euclidean distance between the two input vectors a and b.
 ******************************************/
float Face::euclidean_distance(int n)
{
    float dist = 0.0;
    double length_a;
    double length_b;
    for (int i = 0; i < n; i++)
    {
        length_a += image_arr1[i] * image_arr1[i];
    }
    for (int i = 0; i < n; i++)
    {
        length_b += image_arr2[i] * image_arr2[i];
    }
    for (int i = 0; i < n; i++)
    {
        float diff = image_arr1[i] / sqrt(length_a) - image_arr2[i] / sqrt(length_b);
        dist += diff * diff;
    }
    return sqrt(dist);
}

/*****************************************
 * Function Name : compare_with_existing_faces
 * Description   : This function takes in a vector of floats floatarr representing the 
 *                 features of a face detected in an image,and compares it with the features of 
 *                 previously stored faces in text files located in the directory "faces/".
 * Arguments     : floatarr = vector<float>
 * Return value  : The return value of the function compare_with_existing_faces is a string.
 *                 It can be either the string "none" if there is no match or the path to the text file that 
 *                 contains the 512-dimensional feature vector of the matching face.
 ******************************************/
std::string Face::compare_with_existing_faces()
{
    float co_thresh = 0.23; 
    float eu_thresh = 10.0;
    float max_value_co = 0.0;
    float min_value_eu = 10000000.0;
    float co_score = 0.0;
    float eu_distance = 0.0;
    co_score = cosine_similarity();
    eu_distance = euclidean_distance(512);
    if (co_score > max_value_co)
        max_value_co = co_score;
    if (eu_distance < min_value_eu)
        min_value_eu = eu_distance;
    std::cout << "cosine similarity  : " << co_score <<"\n";
    std::cout << "euclidean_distance : " << eu_distance <<"\n";
    if ((min_value_eu < eu_thresh) && (max_value_co > co_thresh))
    {
        return "match";
    }
    else
    {
        return "none";
    }
}