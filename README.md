---------------------------------------------------
Traveling Thief Problem 
---------------------------------------------------



---------------------------------------------------
Build
---------------------------------------------------


cd travelling-thief-problem
mkdir build && cd build
cmake ..
make


---------------------------------------------------
Project Structure
---------------------------------------------------


travelling-thief-problem
|
|-- bin 
|        make install will copy the binary files and library to this folder
|
|-- build
|        just a temporary folder for using cmake
|
|-- data
|        location for the test data .ttp
|
|-- doc
|        doxygen documentation of this project
|
|-- executables
|        source code for the executables .cpp
|
|-- lib
|        source code of the library ttp
|
|-- test
|        all the gtest cases
|
|-- vendor
         all vendor libraries that are used


