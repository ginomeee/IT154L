# IT154-8L - Operating Systems Laboratory
***
Under the class of Dr. William Rey. 
This includes all instructions in each individual README file. The only Machine Problem that isn't perfect / is wrong is MP03.

### *Updated* Prerequisite for Windows:
- Dev-C++

Yes all you need is Dev-C++ to run this.

**Note:** Sir is very particular with his instructions and I'm not sure how or why some got different results even with the same output. My hypothesis is that others "Appended" the output and didn't rewrite the TXT output file completely, removing the previous output. From my understanding, sir Rey wants to remove the previous output after every run and overwrite the TXT file. Your activity and instructions can and possibly will vary, so goodluck.

- **Module 1:** MP01-MP04
- **Module 2:** MP05-MP08

***
## The section below is deprecated. It has a tendency not to work on Windows installs without the proper DLL.
### Prerequisites for Windows:
- Install the [g++ compiler](https://sourceforge.net/projects/mingw/) or any compiler that can compile C++
- Any editor / IDE. I personally use [Atom](https://atom.io/).
- Your Windows PATH / environment variables set to the install location of your compiler (For GCC/G++). Here's a [helpful guide](https://www.scaler.com/topics/c/c-compiler-for-windows/)

### G++ Compile Instructions for Windows:
- Run the G++ compile command with the following syntax `g++ file_to_compile.cpp -o output_exe`
- Example: `g++ MP02_Araullo_EEA.cpp -o MP02_Araullo_EEA`<br/>
Or you can make your own "Compile" batch file `compile.bat` as I did and add the following lines of code inside the .bat file, with the filename as your preferred filename.
```
@ECHO ON
set filename=MP01_Araullo_EEA
g++ %filename%.cpp -o %filename%
%filename%.exe
cmd /k
```
