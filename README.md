# C++ Standard Parallel for_each for Apple Clang

Apple Clang, not referring to Google Clang, does not implement C++17 parallel for_each and it leads to porting problems when compiling parallel for_each code on Apple platforms. This C++11 header-only library is to close the gap. The namespace is `loop` as not to confuse with `std` in case Apple decide to implement it in the future. **Note**: This library also works on other C++ compilers such as Visual C++, G++ and Google Clang++, not just Apple Clang++.

```Cpp
#include "std_parallel_for_each.h"

int arr[5000];

loop::for_each(loop::execution::par, std::begin(arr), std::end(arr), 
    [](int& n) { 
        n = 3; 
    }
);
```
