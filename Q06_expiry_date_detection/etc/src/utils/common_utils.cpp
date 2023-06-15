#include "common_utils.h"

/*****************************************
 * Function Name     : float16_to_float32
 * Description       : Function by Edgecortex. Cast uint16_t a into float value.
 * Arguments         : a = uint16_t number
 * Return value      : float = float32 number
 ******************************************/
float float16_to_float32(uint16_t a)
{
    return __extendXfYf2__<uint16_t, uint16_t, 10, float, uint32_t, 23>(a);
}

/*****************************************
 * Function Name     : load_label_file
 * Description       : Load label list text file and return the label list that contains the label.
 * Arguments         : label_file_name = filename of label list. must be in txt format
 * Return value      : vector<string> list = list contains labels
 *                     empty if error occurred
 ******************************************/
vector<string> load_label_file(string label_file_name)
{
    vector<string> list = {};
    vector<string> empty = {};
    ifstream infile(label_file_name);

    if (!infile.is_open())
    {
        return list;
    }

    string line = "";
    while (getline(infile, line))
    {
        list.push_back(line);
        if (infile.fail())
        {
            return empty;
        }
    }

    return list;
}

/*****************************************
 * Function Name : sigmoid
 * Description   : Helper function for YOLO Post Processing
 * Arguments     : x = input argument for the calculation
 * Return value  : sigmoid result of input x
 ******************************************/
double sigmoid(double x)
{
    return 1.0 / (1.0 + exp(-x));
}

/*****************************************
* Function Name : yolo_index
* Description   : Get the index of the bounding box attributes based on the input offset
* Arguments     : n = output layer number
                  offs = offset to access the bounding box attributes
*                 channel = channel to access each bounding box attribute.
* Return value  : index to access the bounding box attribute.
******************************************/
int32_t yolo_index(uint8_t n, int32_t offs, int32_t channel)
{
    uint8_t num_grid = num_grids[n];
    return offs + channel * num_grid * num_grid;
}

/*****************************************
* Function Name : yolo_offset
* Description   : Get the offset number to access the bounding box attributes
*                 To get the actual value of bounding box attributes, use yolo_index() after this function.
* Arguments     : n = output layer number [0~2].
                  b = Number to indicate which bounding box in the region [0~4]
*                 y = Number to indicate which region [0~13]
*                 x = Number to indicate which region [0~13]
* Return value  : offset to access the bounding box attributes.
******************************************/
int32_t yolo_offset(uint8_t n, int32_t b, int32_t y, int32_t x)
{

    uint8_t num = num_grids[n];
    uint32_t prev_layer_num = 0;
    int32_t i = 0;

    for (i = 0; i < n; i++)
    {
        prev_layer_num += NUM_BB * (NUM_CLASS + 5) * num_grids[i] * num_grids[i];
    }
    return prev_layer_num + b * (NUM_CLASS + 5) * num * num + y * num + x;
}