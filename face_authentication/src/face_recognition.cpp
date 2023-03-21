#include <builtin_fp16.h>
#include <fstream>
#include <sys/time.h>
#include <climits>
#include <cstdlib>
#include <cstring>
#include "MeraDrpRuntimeWrapper.h"
#include "opencv2/core.hpp"
#include "iostream"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <vector>
#include <glob.h>
#include <cmath>
using namespace cv;
using namespace std;
MeraDrpRuntimeWrapper runtime;
std::string model_dir = "facenet_model";
std::string text_input;
Scalar GREEN(0, 255, 0);
Scalar RED(0, 0, 255);
cv::Mat img;
cv::Mat image;
/* Image buffer (u-dma-buf) */
unsigned char *img_buffer;
unsigned int try_cnt;
bool add_face_clicked = false;
bool recognize_face_clicked = false;
bool add_face_from_dir_clicked = false;
/*****************************************
 * Function Name : hwc2chw
 * Description   : This function takes an input image in HWC (height, width, channels)
 *                 format and returns an output image in CHW (channels, height, width) format.
 * Arguments     : image = cv::Mat
 ******************************************/
cv::Mat hwc2chw(const cv::Mat &image)
{
    std::vector<cv::Mat> rgb_images;
    cv::split(image, rgb_images);
    cv::Mat m_flat_r = rgb_images[0].reshape(1, 1);
    cv::Mat m_flat_g = rgb_images[1].reshape(1, 1);
    cv::Mat m_flat_b = rgb_images[2].reshape(1, 1);
    cv::Mat matArray[] = {m_flat_r, m_flat_g, m_flat_b};
    cv::Mat flat_image;
    cv::hconcat(matArray, 3, flat_image);
    return flat_image;
}
/*****************************************
 * Function Name : cosine_similarity
 * Description   : This function computes the cosine similarity between two input
 *                 feature vectors represented as std::vector<float>.
 * Arguments     : features1 = std::vector<float>
 *                 features2 = std::vector<float>
 * Return value  : float value that represents the cosine similarity
 *                 between the two input feature vectors.
 ******************************************/
float cosine_similarity(const std::vector<float> &features1, const std::vector<float> &features2)
{
    if ((features1.empty() || features2.empty()) || (features1.size() != features2.size()))
        return 0.0;
    float dot_product = 0.0;
    for (int i = 0; i < features1.size(); i++)
    {
        dot_product += features1[i] * features2[i];
    }
    float norm1 = 0.0;
    float norm2 = 0.0;
    for (int i = 0; i < features1.size(); i++)
    {
        norm1 += features1[i] * features1[i];
        norm2 += features2[i] * features2[i];
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
 * Function Name : cosine_similarity
 * Description   : This function takes two vectors of floats (a and b)
 *                 and an integer n as parameters and returns a float representing the Euclidean distance between the two vectors.
 * Arguments     : vector<float> a: a vector of float values representing the first vector for which to compute the Euclidean distance.
 *                 vector<float> b: a vector of float values representing the second vector for which to compute the Euclidean distance.
 * Return value  : float value representing the Euclidean distance between the two input vectors a and b.
 ******************************************/
float euclidean_distance(vector<float> a, vector<float> b, int n)
{
    float dist = 0.0;
    double length_a;
    double length_b;
    for (int i = 0; i < n; i++)
    {
        length_a += a[i] * a[i];
    }
    for (int i = 0; i < n; i++)
    {
        length_b += b[i] * b[i];
    }
    for (int i = 0; i < n; i++)
    {
        float diff = a[i] / sqrt(length_a) - b[i] / sqrt(length_b);
        dist += diff * diff;
    }
    return sqrt(dist);
}
/*****************************************
 * Function Name : add_face
 * Description   : The function saves the facial feature vector to a file
 *                 named after the person's name in a directory named "faces/".
 * Arguments     : floatarr: A vector<float> containing the facial feature vector to be saved.
 *                 name: A string containing the name of the person whose facial features are being saved.
 ******************************************/
void add_face(vector<float> floatarr, string name)
{
    std::string dir_path = "faces/";
    glob_t glob_result;
    std::string search_pattern = dir_path + "*.txt";
    int file_count = 0;
    if (glob(search_pattern.c_str(), 0, nullptr, &glob_result) == 0)
    {
        file_count = glob_result.gl_pathc;
    }
    globfree(&glob_result);
    std::string new_file_name = dir_path + name + ".txt";
    cout << "file saved at " << new_file_name << endl;
    std::ofstream outfile(new_file_name);
    for (size_t i = 0; i < floatarr.size(); i++)
    {
        outfile << floatarr[i] << " ";
    }
    outfile.close();
}
/*****************************************
 * Function Name : run_inference
 * Description   : This is a function that takes a cropped image as input, runs inference on it using a runtime object,
 *                 and returns a vector of float values as output.
 * Arguments     : croppedImg = Mat format.
 *
 * Return value  : The return value of the above function is a vector of float values.
 *                 These float values represent the output of a neural network inference model run on the input image.
 ******************************************/
vector<float> run_inference(Mat croppedImg)
{
    std::vector<Mat> bgr_channels;
    split(croppedImg, bgr_channels);
    Mat eq_b, eq_g, eq_r;
    equalizeHist(bgr_channels[0], eq_b);
    equalizeHist(bgr_channels[1], eq_g);
    equalizeHist(bgr_channels[2], eq_r);
    std::vector<Mat> eq_channels = {eq_b, eq_g, eq_r};
    Mat eq;
    merge(eq_channels, eq);
    croppedImg = eq;
    Mat patch1;
    vector<float> floatarr(2);
    cv::Mat rgb_img;
    cv::Mat resized_img;
    cv::Size size(160, 160);
    cv::resize(croppedImg, resized_img, size, INTER_LINEAR);
    cv::cvtColor(resized_img, rgb_img, cv::COLOR_BGR2RGB);
    cv::Mat inp_img;
    inp_img = hwc2chw(rgb_img);
    patch1 = inp_img;
    uint8_t ret = 0;
    Mat patch_con;
    if (!patch1.isContinuous())
        patch_con = patch1.clone();
    else
        patch_con = patch1;
    Mat patch_norm;
    cv::normalize(patch_con, patch_norm, 0, 1, cv::NORM_MINMAX, CV_32FC1);
    float *temp_input = new float[patch_norm.rows * patch_norm.cols * 3];
    memcpy(temp_input, patch_norm.ptr<float>(), patch_norm.total() * 3 * sizeof(float));
    runtime.SetInput(0, temp_input);
    runtime.Run();
    auto output_num = runtime.GetNumOutput();
    if (output_num != 1)
    {
        std::cerr << "[ERROR] Output size : not 1." << std::endl;
        vector<float> error = {0};
        return error;
    }
    auto output_buffer = runtime.GetOutput(0);
    int64_t out_size = std::get<2>(output_buffer);
    floatarr.resize(out_size);
    float *data_ptr = reinterpret_cast<float *>(std::get<1>(output_buffer));
    for (int n = 0; n < out_size; n++)
    {
        floatarr[n] = data_ptr[n];
    }
    return floatarr;
}
/*****************************************
 * Function Name : mouse_callback_button_click.
 * Description   : This is a mouse callback function that is triggered when a mouse button is clicked.
 * Arguments     : event: represents the mouse event (e.g., left button down, right button up)
 *                 x, y: the x and y coordinates of the mouse click.
 *                 flags: additional flags associated with the mouse event (e.g., control key pressed).
 *                 userdata: a pointer to user-defined data that can be used to pass additional information to the callback function.
 ******************************************/
void mouse_callback_button_click(int event, int x, int y, int flags, void *userdata)
{
    if (event == EVENT_LBUTTONDOWN)
    {
        if (415 < x && x < 565 && 523 < y && y < 573)
        {
            std::cout << "clicked add face \n";
            add_face_clicked = true;
        }
        else if (687 < x && x < 837 && 523 < y && y < 573)
        {
            std::cout << "cliked compare face \n";
            recognize_face_clicked = true;
        }
        else if (100 < x && x < 200 && 523 < y && y < 573)
        {
            add_face_from_dir_clicked = true;
        }
    }
}
/*****************************************
 * Function Name : capture_frame
 * Description   : This function captures a frame from a video source (in this case, a webcam) and displays it on the screen.
 * Return value  : returns the cropped image as a Mat object.
 ******************************************/
Mat capture_frame(void)
{
    cout << "capture frame\n";
    Mat patch1;
    Mat img1;
    cv::VideoCapture vid(0);
    cout << "starting \n";
    while (1)
    {
        vid >> img1;
        flip(img1, img, 1);
        cv::Point pt1(440, 160);
        cv::Point pt2(840, 560);
        /* Store vertices in vector */
        std::vector<cv::Point> vertices;
        vertices.push_back(pt1);
        vertices.push_back(cv::Point(pt2.x, pt1.y));
        vertices.push_back(pt2);
        vertices.push_back(cv::Point(pt1.x, pt2.y));
        cv::polylines(img, std::vector<std::vector<cv::Point>>{vertices}, true, cv::Scalar(255, 0, 0), 3);
        cv::putText(img, "Adjust face into the box!!", cv::Point(320, 100), cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar(255, 0, 0), 4, false);
        if (waitKey(30) == 27)
        {
            cv::destroyAllWindows();
            break;
        }
        cv::imshow("select face", img); // Wait for 'esc' key press to exit
    }
    cv::Rect roi(440, 160, 400, 400); // x,y,w,h
    cv::Mat croppedImg = img(roi);    // Crop the image
    return croppedImg;
}
/*****************************************
 * Function Name : compare_with_existing_faces
 * Description   : This function takes in a vector of floats floatarr representing the features of a face detected in an image,
 *                 and compares it with the features of previously stored faces in text files located in the directory "faces/".
 * Arguments     : floatarr = vector<float>
 * Return value  : The return value of the function compare_with_existing_faces is a string.
 *                 It can be either the string "none" if there is no match or the path to the text file that contains the 512-dimensional feature vector of the matching face.
 ******************************************/
string compare_with_existing_faces(vector<float> floatarr)
{
    float thresh = 0.23;
    string dir_path = "faces/";
    vector<float> current(512);
    for (int i; i < 512; i++)
    {
        current[i] = floatarr[i];
    }
    glob_t glob_result;
    string pattern = dir_path + "*.txt";
    int return_value = glob(pattern.c_str(), GLOB_TILDE, NULL, &glob_result);
    float max_value = 0.0;
    float min_value_eu = 10000000.0;
    float score = 0.0;
    float distance = 0.0;
    string match = "none";
    string match_eu = "none";
    if (return_value == 0)
    {
        for (size_t i = 0; i < glob_result.gl_pathc; i++)
        {
            ifstream infile(glob_result.gl_pathv[i]);
            vector<float> file_vector(512);
            for (int j = 0; j < 512; j++)
            {
                infile >> file_vector[j];
            }
            infile.close();
            score = cosine_similarity(file_vector, floatarr);
            distance = euclidean_distance(file_vector, floatarr, 512);
            if (score > max_value)
            {
                max_value = score;
                match = glob_result.gl_pathv[i];
            }
            if (distance < min_value_eu)
            {
                min_value_eu = distance;
                match_eu = glob_result.gl_pathv[i];
            }
            cout << glob_result.gl_pathv[i] << endl;
            cout << "cosine similarity : " << score << endl;
            cout << "euclidean_distance : " << distance << endl;
        }
        globfree(&glob_result);
        if ((min_value_eu < 10) && (max_value > thresh))
        {
            return match;
        }
        else
        {
            try_cnt++;
            return "none";
        }
    }
    return "none";
}
/*****************************************
 * Function Name : add_imgs_from_dir
 * Description   : This function appears to be part of a facial recognition system that is reading in a set of images from a directory,
 *                 computing face embeddings for each image using a neural network, and storing those embeddings for future use in identifying faces.
 ******************************************/
void add_imgs_from_dir(void)
{
    string dir_path = "dataset/";
    vector<float> current(512);
    glob_t glob_result;
    string pattern = dir_path + "*.jpg";
    int return_value = glob(pattern.c_str(), GLOB_TILDE, NULL, &glob_result);
    if (return_value == 0)
    {
        for (size_t i = 0; i < glob_result.gl_pathc; i++)
        {
            cout << glob_result.gl_pathv[i] << endl;
            Mat img1 = imread(string(glob_result.gl_pathv[i]));
            flip(img1, img1, 1);
            vector<float> floatarr = run_inference(img1);
            String s = string(glob_result.gl_pathv[i]).substr(7);
            s = s.substr(0, s.size() - 4);
            add_face(floatarr, s);
        }
    }
}
int main(int argc, char **argv)
{
    std::string app_name = "Face Recognition";
    int width = 900, height = 600;
    runtime.LoadModel(model_dir);
    cout << "loaded model:" << model_dir << endl;
    namedWindow(app_name, WINDOW_NORMAL);
    resizeWindow(app_name, 1200, 800);
    while (waitKey(1) != 'q')
    {
        Mat frame;
        frame = cv::imread("face_rec_bg.jpg");
        if (add_face_clicked)
        {
            rectangle(frame, Point(415, 523), Point(565, 573), Scalar(150, 150, 150), -1);
            putText(frame, "Add faces", Point(415 + (int)150 / 4, 553), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 1);
            add_face_clicked = false;
            destroyAllWindows();
            Mat croppedImg = capture_frame();
            vector<float> floatarr = run_inference(croppedImg);
            cv::Mat image(300, 600, CV_8UC3, cv::Scalar(255, 255, 255));
            std::string prompt = "Enter your name: ";
            cv::putText(image, prompt, cv::Point(50, 150), cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(0, 0, 0), 2);
            cv::imshow("Input", image);
            std::string name = "";
            char c;
            while ((c = cv::waitKey(0)) != 27)
            {
                if (c == '\n')
                    break;
                else if (c == 8 && !name.empty())
                    name.pop_back();
                else if (std::isprint(c))
                    name += c;
                cv::Mat updatedImage = image.clone();
                cv::putText(updatedImage, prompt + name, cv::Point(50, 150), cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(0, 0, 0), 2);
                cv::imshow("Input", updatedImage);
            }
            cv::destroyAllWindows();
            std::cout << "Name entered: " << name << std::endl;
            add_face(floatarr, name);
        }
        else
        {
            rectangle(frame, Point(415, 523), Point(565, 573), Scalar(150, 150, 150), -1);
            putText(frame, "Add faces", Point(415 + (int)150 / 4, 553), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 1);
        }
        if (recognize_face_clicked)
        {
            rectangle(frame, Point(687, 523), Point(837, 573), Scalar(150, 150, 150), -1);
            putText(frame, "Recognize", Point(687 + (int)150 / 4, 553), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 1);
            recognize_face_clicked = false;
            destroyAllWindows();
            Mat croppedImg = capture_frame();
            vector<float> floatarr = run_inference(croppedImg);
            string match = compare_with_existing_faces(floatarr);
            cout << "match:" << match << endl;
            cv::waitKey(10);
            if (match == "none")
            {
                cout << "[match]" << match << endl;
                if (try_cnt > 2)
                {
                    try_cnt = 0;
                    cv::putText(frame, "Person Not Found In The Dataset!!", cv::Point(50, 150), cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(0, 0, 255), 2);
                }
                else
                {
                    cv::putText(frame, "Match Not Found,Please try again!!", cv::Point(50, 150), cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(0, 0, 255), 2);
                }
                cv::imshow(app_name, frame);
                cv::waitKey(3000);
            }
            else
            {
                match.erase(match.length() - 4);
                match.erase(0, 6);
                cout << "[match]" << match << endl;
                cv::putText(frame, "Match Found : " + match, cv::Point(50, 150), cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(0, 255, 0), 2);
                cv::imshow(app_name, frame);
                cv::waitKey(3000);
                try_cnt = 0;
            }
        }
        else
        {
            rectangle(frame, Point(687, 523), Point(837, 573), Scalar(150, 150, 150), -1);
            putText(frame, "Recognize", Point(687 + (int)150 / 4, 553), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 1);
        }
        if (add_face_from_dir_clicked)
        {
            rectangle(frame, Point(100, 523), Point(300, 573), Scalar(150, 150, 150), -1);
            putText(frame, "Add Face From Dir", Point(100 + (int)150 / 4, 553), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 1);
            add_imgs_from_dir();
            add_face_from_dir_clicked = false;
            cv::putText(frame, "Added Faces from dataset folder", cv::Point(50, 150), cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(0, 255, 0), 2);
        }
        else
        {
            rectangle(frame, Point(100, 523), Point(300, 573), Scalar(150, 150, 150), -1);
            putText(frame, "Add Face From Dir", Point(120, 553), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 1);
        }
        setMouseCallback(app_name, mouse_callback_button_click);
        imshow(app_name, frame);
    }
    destroyAllWindows();
    return 0;
}
