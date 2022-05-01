# c_cpp_data_structures
Data Structures written in C/C++. This is an adaptation of [William Fiset's Data Structures Repository](https://github.com/williamfiset/DEPRECATED-data-structures) in C/C++.

You can find his [Video](https://youtu.be/RBSGKlAvoiM) describing these structures.

# Building the Projects
1. Create a build folder under each algorithm's root directory
   `mkdir build`
2. Open a bash shell at the root directory and run
    `cmake -S . -B build`
3. This is generating a MSVS project for me. You can instead change the generator to minGW (assuming you already donwloaded it)
   `cmake -G "MinGW Makefiles" -S . -B build`
   1. You can use the 'clean' option to clear out the cmake files in a project
      `cmake --build build --target clean`
4. cd to the build directory and then run make to build the target executable.
   `cd build; make`