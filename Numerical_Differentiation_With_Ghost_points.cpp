#include<iostream>
#include<vector>
#include<fstream>
#include<math.h>
#include<string>

using namespace std;

typedef double real;

// Function for the stencil
double central_diff_2nd_order_derivative_4th_order_accurate(vector<double> u,double dx, int i)
{
    return (-u[i-2] + (16*u[i-1]) -(30*u[i]) + (16*u[i+1]) - u[i+2])/(12*pow(dx,2));
}

// Function to save a vector<double> to a file of given name
void vector_double_to_file(vector<double> u, string str)
{
    ofstream file;
    // Open the file
    file.open(str);

    // If the file is NOT opened
    if( !file )
    {
        // Error Message if the file couldn't be opened
        cerr << "Error: file could not be opened" << endl;
        exit(1);
    }

    // Writing the vector values to the file in scientific notation
    for(int i=0;i<u.size();i++)
    {
        file<<u[i]<<scientific<<endl;
    }

    // Closing the file
    file.close();
}

vector<real> input_parameters(string file_name, int num_parameters)
{

    vector<real> input(num_parameters);
    string item_name;
    int i = 0;

    // Open the file
    ifstream file;
    file.open(file_name);

    cout<<"Input file is opened."<<endl;

    // If the file is NOT opened
    if( !file )
    {
        // Error Message if the file couldn't be opened
        cerr << "Error: Input file could not be opened" << endl;
        exit(1);
    }

    while (file >> item_name)
    {
        // Classifying a string as double if the first character is a numeric
        if(isdigit(item_name[0]))
        {
            // converting the string to double
            input[i] = stod(item_name);
            i++;
        }
    }
    // Closing the input file
    file.close();

    cout<<"Input file is closed."<<endl;

    return input;

}

int main()
{
    // Using the double as a real number
    typedef double real;

    int num_grid_points,num_stencil_points,nst;

    vector<real> input;
    input = input_parameters("Input.txt",3);

    //num_grid_points = 20;
    num_grid_points = input[0];
    num_stencil_points = 5;

    // Number of grid points on each side of the point which is at the middle of the stencil
    nst = (num_stencil_points-1)/2;

    // Location of the grid points
    vector<real> x(num_grid_points+(2*nst));

    // The original function
    vector<real> u(num_grid_points+(2*nst));

    // The second derivative of the function in the interval [a,b]
    vector<real> d2udx2(num_grid_points+(2*nst));

    real a,b,L,dx,pi;

    pi = acos(-1);
    //a = 0;
    //b = 2*pi;

    a = input[1];
    b = input[2];

    // Length of the interval
    L = b-a;

    // Distance between 2 consecutive grid points
    dx = L/(num_grid_points-1);

    // Calculating the location of the grid points even the ghost points
    for(int k = 0 ; k<= num_grid_points + (2*nst) ; k++)
    {
        x[k] = a+((k-nst)*dx);
    }

    // Calculating the value of the function at the grid points even the ghost points
    // Here the function need to be periodic and the the interval b-a = L (L > 0) should the period of the function
    for(int k = 0 ; k< num_grid_points-1 ; k++)
    {
        u[k+ nst] = sin(k*dx);
    }

    // Populating the value of the ghost points
    for(int k = 0 ; k<= nst ; k++)
    {
        u[nst - k ] = u[ (nst) +num_grid_points - 1 - k];
        u[num_grid_points - 1+ k + nst] = u[nst + k];
    }

    // Printing the value of the original function
    /*for(int k = 0 ; k< num_grid_points+(2*nst) ; k++)
    {
        cout<<"u["<<k<<"] = "<<u[k]<<endl;
    }*/

    // Calculating and printing the second derivative of the original function
    for(int i = nst; i<num_grid_points +nst;i++)
    {
        //cout<<"Calulating at the grid point: "<<i<<endl;

        // Calculating
        //d2udx2[i] = (-u[i-2] + (16*u[i-1]) -(30*u[i]) + (16*u[i+1]) - u[i+2])/(12*pow(dx,2));
        d2udx2[i] = central_diff_2nd_order_derivative_4th_order_accurate(u,dx,i);
        //cout<<"d2u/dx2: "<<d2udx2[i]<<endl;
    };

    // Writing the value of the original function in the file "Original_Function_File.txt"
    vector_double_to_file(u,"Original_Function_File.txt");

    // Writing the value of the second derivative of the original function in the file "Output_File.txt"
    vector_double_to_file(d2udx2,"Output_File.txt");

    // Writing the location of the gird points in the file "Grid_Location.txt"
    vector_double_to_file(x,"Grid_Location.txt");

    return 0;
}
