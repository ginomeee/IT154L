# IT154-8L
***
Under the class of Dr. William Rey

### Prerequisites for Windows:
- Install the [g++ compiler](https://www.scaler.com/topics/c/c-compiler-for-windows/) or any compiler that can compile C++
- Any editor / IDE. I personally use [Atom](https://atom.io/).
- Your Windows PATH / environment variables set to the install location of your compiler (For GCC/G++). Here's a [helpful guide](https://www.scaler.com/topics/c/c-compiler-for-windows/)

### G++ Compile Instructions for Windows:
- Run the G++ compile command with the following syntax `g++ file_to_compile.cpp -o output_exe` 
- Example: `g++ MP02_Araullo_EEA.cpp -o MP02_Araullo_EEA`
or you can make your own "Compile" batch file as I did and add the following lines of code inside a .bat file
`
@ECHO ON
g++ MP02_Araullo_EEA.cpp -o MP02_Araullo_EEA
MP02_Araullo_EEA
cmd /k
`

