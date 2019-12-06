创建一个新的custom功能的步骤：
1. 创建／克隆 新的.cc与.h文件， 并添加到CMAKELIST中
2. 若新添加的源码是克隆得来的，则在其中所有类名前添加“Custom”、在#ifndef中添加“CUSTOM”。所有新建的类都在colmap命名空间中。
3. 在main_window.h中添加新的.h，并用新添加的源码中的类定义一个对象，对象名以"_"结尾。
4. 在main_window.cc中的“CreateWidgets”类中添加 对新建对象内存的创建及相关代码。
5. 在main_window.cc中就可以使用新的类了！！！
