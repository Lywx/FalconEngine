Falcon Engine
===
A cross-platform 3D Graphics Engine for study and academic use, (Windows: DirectX 11 / OpenGL 4.3, Unix: OpenGL 4.3).

Building
===
1. Manually build 3rd-party dependency for static or shared libraries of your choice.
2. Manually copy their include and lib into root/include and root/lib respectively.
3. Run cmake for make system of your choice on project root directory.
4. Build.

Dependency
===
1. assimp 3.3.1.
2. boost 1.6.1 for boost-filesystem, boost-regex, boost-system.
3. [cereal](https://github.com/USCiLab/cereal) 1.2.2.
4. glew 2.0.0.
5. glfw 3.2.1.
6. stb_image.

Showcase
===
![Bedroom](case/Showcase.jpg)

Reference
===
1. David Eberly. *Wild Magic* and *Geometry Tool* Source Code.
2. David Eberly. *3D Game Engine Design: A Practical Approach to Real-Time Computer Graphics*, 2nd, 2006.
3. Patrick Cozzi, Kevin Ring. *3D Engine Design for Virtual Globes*, 2011.

Disclaimer
===
You would find some similiarity in code, compared to the David Eberly's [Geometry Tool](https://www.geometrictools.com/)
Project. 

In fact, this project started as my first attempt to build a rendering engine.
As I learned more and more about David Eberly's work, I decided to prune code from 
Geometry Tool into my own renderer. By doing so I actually learned faster, given 
the necessary framework and logics in Geometry Tool.

So I don't claim originality for entirety of this project. But the current code base
has been greatly diverged from the original framework in Geometry Tool.
