# snake-ai
qt c++实现的贪吃蛇ai吃满屏幕  

教程已经放到csdn上了：[qt c++实现的ai贪吃蛇吃满屏幕，超详细！(一)基本组件](https://blog.csdn.net/livingsu/article/details/104455053)  

[qt c++实现的ai贪吃蛇吃满屏幕，超详细！(二)ai的具体实现](https://blog.csdn.net/livingsu/article/details/104456075)  

大概讲一下各个类的作用：widget是欢迎界面，chooseWidget是选择界面，可以选择单双人或者ai模式，还有基本或随机地形。gameWidget处理游戏加分和特殊食物倒计时，gameWidget中有一个drawWidget类的成员myDrawWidget用来实现游戏绘制和更新。游戏的主要功能都在drawWidget类中实现。component类是游戏基本组件类，实现了地图、蛇和食物类。要看核心代码就直接看drawWidget。  

由于个人是小白，写的代码也不是很好看，希望大家见谅。


