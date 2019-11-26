#ifndef DATAUTILS_H
#define DATAUTILS_H

#include <vector>
#include <iostream>
#include <fstream>

#ifndef PI
#define PI	3.1415926535897932384626433832795
#endif
#define NUMBER_OF_CYCLES_FOR_QUAULITY_CHECK		2000
#define SIZE_OF_TRANSFER_STRING					32
#define MIN_STIFFNESS 0.01

namespace eitools {
namespace DataUtils {

/*
class DataUtils
{
public:

private:
    DataUtils();
};
*/

template<typename T, typename U>
void insertArrayIntoVector(T arr[], size_t size, std::vector<U> &vec) {
    vec.insert(vec.begin(), &arr[0], &arr[size]);
}

void shiftMotionPosition(std::vector<std::vector<float> > &cart_motion, float x, float y, float z) {
    // change reference of cart_motion to shift whole trajectory in position
    for(int r=0; r < cart_motion.size(); ++r) {
        cart_motion[r][3] += x;
        cart_motion[r][7] += y;
        cart_motion[r][11] += z;
    }
}

void reserveVectorMatrix(std::vector< std::vector<float> > &mat, unsigned int n_rows, unsigned int n_cols) {
    // Memory allocated here is lost after leaving scope of this function
    mat.clear();
    for(int k = 0; k < n_rows; k++){
        //std::vector <float> *tmp_vec = new std::vector <float>(); // store on heap to persist
        mat.push_back( std::vector <float>() );
        //mat.push_back( *tmp_vec );
        for(int j=0; j < n_cols; j++){
            mat[k].push_back(0.0);
        }
    }
    std::cout << "Reserved vector matrix with dimensions: " << n_rows << " x " << n_cols << std::endl;
}

int loadVectorMatrixFromFile (std::string fileName, int cols, std::vector<std::vector<float> > &outMat)
{
    std::ifstream in(fileName.data());
    if (!in)
    {
        std::cout << "No file found: " << fileName << std::endl;
        return -1;
    }
    int counter = 0;
    while (!in.eof())
    {
        outMat.push_back( std::vector <float>() );
        for (int j = 0; j < cols; ++j)
        {
            double readf;
            in >> readf;
            outMat[counter].push_back(readf);
        }
        counter++;
    }
    outMat.pop_back();
    in.close();
    return 0;
}


void saveVectorMatrixToFile (std::string fileName, const std::vector<std::vector<float> > &outMat)
{
    std::ofstream out(fileName.data());
    if (!out)
    {
        std::cout << "No file found: " << fileName << std::endl;
        return;
    }
    int rows = (int)outMat.size();
    int cols = (int)outMat[0].size();
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            out << outMat[i][j] << "\t";
        }
        out << std::endl;
    }
    out.close();
    return;
}


float getSquaredDistance(float a[3], float b[3]){
    return (a[0]-b[0])*(a[0]-b[0]) +
           (a[1]-b[1])*(a[1]-b[1]) +
           (a[2]-b[2])*(a[2]-b[2]) ;
}

void float2doubleArr(float* in_arr, double* out_arr, unsigned int size)
{
    for (int i=0; i<(int)size; i++) {
        out_arr[i] = (double)in_arr[i];
    }
}

void double2floatArr(double* in_arr, float* out_arr, unsigned int size)
{
    for (int i=0; i<(int)size; i++) {
        out_arr[i] = (float)in_arr[i];
    }
}

template <typename T1, typename T2>
void arrayTypeConversion(T1* in_arr, T2* out_arr, size_t size) {
    for (int i=0; i<size; i++) {
        out_arr[i] = (T2)in_arr[i];
    }
}

/*
void rotateVecArr(float* src, float* dest, float* trafo, bool invert=false)
{
    Eigen::Map<Eigen::Vector3f> src_vec(src); // 3 vector
    //Eigen::Map<Eigen::Matrix3f> rot_mat(rotation); // 3x3 matrix

    Eigen::Map<Eigen::Matrix<float,3,4, Eigen::RowMajor> > trafo_eigen(trafo); // 3x4 affine trafo
    Eigen::Matrix3f rot_mat = trafo_eigen.block<3,3>(0,0); // 3x3 rotation matrix

    Eigen::Vector3f dest_vec;
    if (invert)
         dest_vec = rot_mat.transpose() * src_vec;
    else
        dest_vec = rot_mat * src_vec;

    memcpy(dest, dest_vec.data(), sizeof(float)*3);
}
*/


} } // end namespace

#endif // DATAUTILS_H
