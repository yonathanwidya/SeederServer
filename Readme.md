# Seeder Server
There are two separate executables: **SeederServer** and **NodeClient**. Building is straightforward using CMake:
* In terminal, go to the respective component directory (either **SeederServer** or **NodeClient**), until you can see the **CMakeLists.txt** and the source codes
* Run **cmake .**
* Run **make**
* The executables will be in **/build/bin** directory of the respective components.

Alternatively if running on MacOS, you can just open from the XCode project and run from there.

Note that this project is using C++11 and Boost 1.67.0
