//
//  glfwDetails.h
//  CPlusProjectComputerGraph
//
//  Created by admindyn on 2017/3/29.
//  Copyright © 2017年 admindyn. All rights reserved.
//

#ifndef glfwDetails_h
#define glfwDetails_h
/*
 图形的显示
 这才是最终的目的。
 真正的位图的显示，在OpenGL中都不是那么容易的，需要掌握一堆的东西。见《Win32 OpenGL编程(15) 位图显示 》《Win32 OpenGL编程(16) 纹理贴图 》，那是因为OpenGL中实际完全对图形的显示没有直接的支持。听起来有些奇怪。。。实际的意思就是，OpenGL的API完全不理解位图，png图的含义。（虽然在上述15中提到一些bmp的操作接口，但是很遗憾的，实际的使用中都是使用纹理贴图，即16中提到的东西） 在GLFW中呢？我看到GLFW有对图形操作的接口。可是遗憾的是仅支持TGA，连BMP都不支持，不知道这种取舍是为啥，一般而言，我感觉，支持bmp的话，是最基础的。
 这里还是用《SDL 简单入门学习 》中的那个龙图。
 其中，图形文件操作的接口分两种，这里只看OpenGL常用的使用纹理贴图的方式。用到的API名字叫glfwLoadTexture2D。先显示个tga试一下。
 代码的主要部分还是OpenGL，所以可以参考《Win32 OpenGL编程(16) 纹理贴图 》中的代码，仅仅借用了glfw的glfwLoadTexture2D函数而已。
 */
/*
 感觉相对于图像显示来说，glfw并没有如SDL那般省事，因为毕竟还是全程使用OpenGL，对比原来OpenGL中显示位图的代码来说，仅仅是没有调用Windows API了而已，仅仅是多了跨平台的特性而已，并没有简化工作，而且，glfw同样的，也没有内置png图形的支持。虽然说tga在3D中用的非常多，主要是因为无损压缩，但是2D中，我还是喜欢使用png,因为小的多。当然，一旦使用png，无可避免的会需要使用libpng/zlib，所以GLFW为了保持自身的简单，没有做这样的工作吧，相对来说tga的解压就要简单太多了。
 另外，GLFW还有glfwReadImage函数可以将tga图直接读入内存，然后获取到图形的相关信息的办法（上面就没有办法获取到图形的宽高）
 */

#endif /* glfwDetails_h */
