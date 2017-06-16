kernel-x86
======

overview
-----------
*kernel-x86* --- an Intel x86-arch kernel  
~~Personally I develop under Windows, then build with a virtual machine w/ shared folders~~  
WSL(Bash on Windows) simplifies the process, now I develop and build under Windows  

how-to
-----------
  * Run *./wsl_setup* under WSL to setup the build environment required  
  * Run *./compile* under WSL or launch *compile.bat* under Windows  
  * Run *run_bochs.bat* under Windows (tested under Windows 10 with bochs 2.6.9; modify version number as needed)  

VSCode Prep
-----------
  * (CTRL+P) ext install cpptools  
  * (CTRL+P) ext install language-x86-64-assembly  
  
WSL
-----------
  * Linux:    build-essential, nasm, *cmake-3.x*, gcc, g++, grub2, xorriso  
  * Windows:  bochs 2.6.9 (modify version # if needed)  

Run *CompileWithWSL.bat* or *RebuildWithWSL.bat* to compile  
Run *run_bochs.bat* with correct path to bochs to emulate/debug  
