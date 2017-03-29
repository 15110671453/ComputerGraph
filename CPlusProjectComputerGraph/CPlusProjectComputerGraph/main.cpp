//
//  main.cpp
//  CPlusProjectComputerGraph
//
//  Created by admindyn on 2017/3/28.
//  Copyright © 2017年 admindyn. All rights reserved.
//


/*
 在看计算机系的同学的代码时，我还不知道GLSL这种东西。我还以为OpenGL绘制就是使用glBegin和glEnd。我还深深地纳闷：OpenGL这货画东西完全不给力，是怎么做到跟DirectX相比的？然后我看到了代码里的glUseProgram，看到了程序里完全没有出现glBegin这种语句。后来我才知道，手里的OpenGL红宝书已经是过去时，NeHe的OpenGL教程也已经是过去时，我离地球太远了。
 
 所以glsl才是所谓的Advanced OpenGL吧，然而在百度上搜索OpenGL相关信息，依然有许多文章在用glBegin和glEnd来画东西。但是看到的助于Open.gl这种网站里的教程，都已经彻底弃用这些老式代码，而将绘制工作完全交由显卡完成。现在学OpenGL不学glsl我看是说不过去了。即便是glsl，也经历了许多版本，有很多代码也开始过时了。
 */
/*第三方 对opengl的封装*/

#import <glew.h>
#import <GLFW/glfw3.h>
#import <GLFW/glfw3native.h>
/*opengl库 xcode 自带的GL库 与其他平台自带代码都一样 */
/*
 Do not include the OpenGL header yourself, as GLFW does this for you in a platform-independent way
 Do not include windows.h or other platform-specific headers unless you plan on using those APIs yourself
 If you do need to include such headers, include them before the GLFW header and it will detect this
 */
//#import <OpenGL/OpenGL.h>
//#import <OpenGL/glu.h>
#import <OpenGL/OpenGL.h>
#import <OpenGL/glu.h>
#import <GLUT/GLUT.h>
/*C++自己的苦*/
#include <fstream>
#include <vector>
#include <iostream>
using namespace std;
class Vector3
{
    float x, y, z;
public:
    Vector3():x(0), y(0), z(0){}
    Vector3(float x1, float y1, float z1):x(x1), y(y1), z(z1){}
    Vector3(const Vector3 &v);
    ~Vector3();
    void operator=(const Vector3 &v);
    Vector3 operator+(const Vector3 &v);
    Vector3 operator-(const Vector3 &v);
    Vector3 operator/(const Vector3 &v);
    Vector3 operator*(const Vector3 &v);
    Vector3 operator+(float f);
    Vector3 operator-(float f);
    Vector3 operator/(float f);
    Vector3 operator*(float f);
    float dot(const Vector3 &v);
    float length();
    void normalize();
    Vector3 crossProduct(const Vector3 &v);
    void printVec3();
};
class  MapPoint
{
public:
    double longitude;
    double latitude;
};

class Polygon{
    public :
    //多边形顶点序列
    vector<MapPoint> points;
};

//多边形集合
vector<Polygon*> polys;

vector<Vector3*> vertices;
vector<Polygon*> ReadMapData(char* filename)
{
    int PointCount;
    vector<Polygon*> polygons;
    ifstream fs(filename);
    
    while(fs.eof()!=true){
        Polygon* poly = new Polygon;
        fs>>PointCount;
        cout<<PointCount<<endl;
        for (int i=0; i<PointCount; i++) {
            MapPoint p;
            fs>>p.longitude>>p.latitude;
            poly->points.push_back(p);
        }
        
        polygons.push_back(poly);
    }
    return polygons;
}
/*
 在老式的固定功能管线里，你只能在每次glBegin(target)和glEnd()间的渲染调用里传递你的顶点（指老版本的OpenGL的机理），但是现代的方法却是把它们放在顶点缓冲对象VBO（Vertext Buffer Object）里。
 VBO用来储存所有你GPU里的顶点数据。
 */
void display(GLFWwindow* window){

   /*
    //设置背景颜色
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glClear(GL_COLOR_BUFFER_BIT );
    
    //用蓝色绘制各省边界
    
    glColor3f(0.0, 1.0, 1.0);
    
    //设置正面为填充模式
    
    glPolygonMode(GL_BACK, GL_LINE);
    
    for (int i=0; i<polys.size(); i++) {
    vector<MapPoint> points = polys[i]->points;
    
    glBegin(GL_LINE_LOOP);
    for (int j=0; j<points.size(); j++) {
    glVertex3f(points[j].longitude, points[j].latitude, 0.0);
    
    }
    glEnd();
    
    
    
    }
    glFlush();
    */
 
    // 旋转角度
    
    static  float  fSpin = 0.0f ;
    
    fSpin += 2.0f ;
    
    if (fSpin > 360.0f ) {
        fSpin -= 360.0f ;
    }
    
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    
    // 旋转矩形的主要函数
    glRotatef(fSpin, 0.0f , 0.0f , 1.0f );
    glRectf(-25.0 , -25.0 , 25.0 , 25.0 );
    glPopMatrix();
    
    // 交换缓冲区 
    glfwSwapBuffers(window);
    
    
}
void displayAdvancedGL(void)
{
    Vector3* v= new Vector3();
    
    vertices.push_back(v) ;
    GLuint VBO;
}
void error_callback(int error, const char* description)
{
    fprintf(stderr, "GLF 调用Error: %s\n", description);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        
    {
        fprintf(stderr, "GLF 调用关闭窗口 ");glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}
void init(void){
   
    //设置背景颜色
    glClearColor(1.0,1.0,1.0,0.0);
    glColor3f(1.0f , 1.0f , 1.0f );
    //初始化观察值
    glShadeModel(GL_FLAT);
    //将矩阵模式设为投影模式
    glMatrixMode(GL_PROJECTION);
    //对矩阵进行单位化
    glLoadIdentity();
    
    //构造平行投影矩阵 注意坐标的设置
   glOrtho(70.0, 140.0, 0.0, 60.0, -1.0, 1.0);
    
    
    
}

void printInfo(void)
{
    cout << "Hello, World8888!\n";
    
    cout << "OpenGL Vendor:" << glGetString(GL_VENDOR) << endl;
    cout << "OpenGL Renderer: " << glGetString(GL_RENDERER) << endl;
    cout << "OpenGL Version: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL Version:" << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;

}
int glfwWindow(void){
    GLFWwindow* window;
    if (!glfwInit()) {
        return -1;
    }
    
    
    /*
     GLFW_CONTEXT_VERSION_MAJOR和GLFW_CONTEXT_VERSION_MINOR顾名思义，就是要告诉GLFW创建的是3.2版本的上下文。
     在GLFW_OPENGL_PROFILE，我们指定要使用核心功能。如果你想用低于3.2版本的OpenGL，你需要指定的是GLFW_OPENGL_ANY_PROFILE，默认其实就是这个值。
     GLFW_OPENGL_FORWARD_COMPAT这个hint指定OpenGL的上下文是否应该向前兼容，如果设定成TRUE，它会停用所有的废弃功能。如果是用OpenGL3.0版本以下，请无视这个hint。
     
     
     
     这几句代码实际上限制死了程序使用OpenGL 3.2版本。但实际上MAC的显卡已经支持到OpenGL 4.1，有一些新特性在3.2下反而无法使用。最后注释了这几句，发现反而没有了限制，也没有出现其他问题。
     */
    
    
    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    /*
     以上描述决定要使用的opengl版本 版本不能超出操作系统平台提供的
     如果你是Apple OS X系统的话那么这4行不要注释掉。简单来说就是它会让我们得到Apple上最新的OpenGL版本，在Mavericks上可能是4. 1或者3.3，在更前的系统上可能是3.2。在其他系统上可能更倾向于选择3.2而不是最新的版本。为了提升对于更新版本的OpenGL的支持，我们可以在启动GLEW之前写上标志glewExperimental = GL_TRUE;
     还需要安装glew库！！！
     */
    glfwSetErrorCallback(error_callback);
    
    
    window= glfwCreateWindow(320,480 , "Hello Title", NULL, NULL);
    //glfw 创建glwindow前先设置调用错误回调
    
    
    if (!window) {
        glfwTerminate();
        return -1;
    }
    
    
    
    glfwMakeContextCurrent(window);
    
    init();
    printInfo();
    
    
    
    glfwSetKeyCallback(window, key_callback);
    /*获取渲染视图上下文后 载入画面*/
    
    while (!glfwWindowShouldClose(window)) {
        
        display(window);
        /*Opengl调用完，需要交换颜色缓冲区，因为GLFW使用的是双缓冲机制。调用glfwSwapBuffers(window)做这件事。
         另一件事是处理执行事件，比如键盘事件，用glfwPollEvents()来做。你也可以用glfwWaitEvents()，如果你的程序在你收到新的输入指令之前只做更新的话。*/
        glfwSwapBuffers(window);
        
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;

}
int main(int argc, const char * argv[]) {
    // insert code here...
    cout << "Hello, World!\n";
    
    
    char* filename ="/Users/admindyn/Downloads/HenanCounty.txt";
    polys=ReadMapData(filename);
   // glutInit(&argc,argv);
    
    

    
    
    
    
    
    
    
    return 0;
}

/*
 The OpenGL Extension Wrangler (GLEW)是用来访问OpenGL 3.2 API函数的。不幸的是你不能简单的使用#include <GL/gl.h>来访问OpenGL接口，除非你想用旧版本的OpenGL。在现代OpenGL中，API函数是在运行时（run time）确定的，而非编译期（compile time）。GLEW可以在运行时加载OpenGL API。
 
 GLFW允许我们跨平台创建窗口，接受鼠标键盘消息。OpenGL不处理这些窗口创建和输入，所以就需要我们自己动手。我选择GLFW是因为它很小，并且容易理解。
 
 OpenGL Mathematics (GLM)是一个数学库，用来处理矢量和矩阵等几乎其它所有东西。旧版本OpenGL提供了类似glRotate, glTranslate和glScale等函数，在现代OpenGL中，这些函数已经不存在了，我们需要自己处理所有的数学运算。GLM能在后续教程里提供很多矢量和矩阵运算上帮助。
 
 在这系列的所有教程中，我们还编写了一个小型库tdogl用来重用C++代码。这篇教程会包含tdogl::Shader和tdogl::Program用来加载，编译和链接shaders。
 */


/*
 什么是Shaders？
 Shaders在现代OpenGL中是个很重要的概念。应用程序离不开它，除非你理解了，否则这些代码也没有任何意义。
 
 Shaders是一段GLSL小程序，运行在GPU上而非CPU。它们使用OpenGL Shading Language (GLSL)语言编写，看上去像C或C++，但却是另外一种不同的语言。使用shader就像你写个普通程序一样：写代码，编译，最后链接在一起才生成最终的程序。
 
 Shaders并不是个很好的名字，因为它不仅仅只做着色。只要记得它们是个用不同的语言写的，运行在显卡上的小程序就行。
 
 在旧版本的OpenGL中，shaders是可选的。在现代OpenGL中，为了能在屏幕上显示出物体，shaders是必须的。
 
 为可能近距离了解shaders和图形渲染管线，
 */

/*
 // get version info
 const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
 const GLubyte* version = glGetString(GL_VERSION); // version as a string
 printf("Renderer: %s\n", renderer);
 printf("OpenGL version supported %s\n", version);
 
 // tell GL to only draw onto a pixel if the shape is closer to the viewer
 glEnable(GL_DEPTH_TEST); // enable depth-testing
 glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"
 */
