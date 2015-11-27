# IMT2531 Graphics Programming - Exam 2015 #

## Per-Morten Straume ##

Before the Exam we already had a framework ready, with a rotating Cube with full Phong lighting and textures. This framework was just so we could have the most basic stuff ready and get stuff on the screen from the get go. However we were quite lucky with the assignment, as our framework supplied us with almost all the building blocks we needed.
The first part of the process was the to integrate our framework into the exam. Following that we started reading in the positions we needed from file and started working with our "beautiful" 3d vector of SceneObjects. The performance were terrible, seeing as we were sending of identical uniforms to our graphics card around 1016 times pr frame etc. We used some time setting up different tricks to optimize the performance. After the worst performance issues were dealt with we started adding the correct textures to our cubes. First in a hardcoded fashion with the texture offsets, I however moved over to an index based solution later, as I found that more readable.
After the textures we fixed the directional lights, and mapped it to user input, through the inputhandler we were given.
After this were in place we started implementing a camera that reacted to the mouse, first this was done in a more static way, that did not follows where the camera was actually looking, but just so you could move around and rotate the camera with the mouse. This was later updated to the current version where the camera moves in the direction you are moving, and strafing.
After that we tackled scale, where the explanation can be found further down in this document.
After Scale we started adding extra functionality, I started trying to clean up my main a bit as it was getting quite hacky and messy at this point. I also used this time to try and optimize my drawcalls.
After this came functionality for adding and deleting blocks
I did start working on my own version of the diamond square algorithm, but tossed it aside after trying to work with it, deciding to rather use my time on other features. 
I also implemented a SkyBox, which in an increadibly haxy way, basically I just draw a huge cube, and flip the cullfacing so that the cube is facing inwards. I also apply a texture on this cube, depending on wether it is "day" or "night". It switched abrubtly, but atleast looks ok'ish.
I also added functionality for rain and snow, where I just create a bunch of cubes and texture them snow or watery. 
After Talking with Simon I fixed my sun moving direction, where I kinda cheated the sun angle. 
Then the last part of the time were used for cleaning up the code.

Buttons mapped to features:

* 9 Raise Scale
* 8 Lower Scale
* 0 Reset Scale
* 1 Earlier Sun
* 2 Later Sun

Extra Features:

* p toggle camera movement on and off
* w Move camera in the direction you are facing
* s Move camera backwards from the direction you are facing
* a Strafe camera Left
* d Strafe Camera Right
* x Move camera down
* c Move camera Up
* k create block below you (/continue building on the stack you are standing "in")
* i destroy block below you (/destroy the block on top of the stack you are standing "in")
* m NextTexture, scrolls through the different texture sets.
* n toggle Rain (turns on a cloud and starts pouring down rain)
* t toggle Snow (turns on a cloud and turns the world into a snowy landscape with icy water and powdery snow)



## Questions to Answer ##

### Resources used ###
Websites and other resources used.  With large sites provide more details of which page, for example which stack overflow question.
For doing the texture atlas:
https://www.youtube.com/watch?v=6T182r4F6J8

For doing camera movement:
https://www.youtube.com/watch?v=HhXzKOMkA1k for Horizontal
https://www.youtube.com/watch?v=7oNLw9Bct1k for Vertical
https://www.youtube.com/watch?v=v6RZRPo0O3k for Keyboard

For MipMapping Explenation
https://developer.valvesoftware.com/wiki/MIP_Mapping
Lecture6 Slides

Also worked together on a lot of the task with Claus, Fredrik and Sebastian.

### Most difficult part of code ###
The part that caused the most problems was scaling in the vertexShader, Many different hacks were tried until I actually understood what I was trying to achieve.

Fixing the performance was also quite hard, the framework we had available when we started was quite good, but not made to do 1016 drawing calls per frame. However after several performance enhancing algorithms and tricks the performance in Debug is now actually quite ok.

Keeping the code "Tidy" was quite hard, especially in main, I had done a couple to many hacks and at one point I decided it was time to Refactor the code.

Finding extra stuff to implement: for some reason my creativity was dead until the last day.

Lighting is not my strongest side, so although we had it ready in the framework, I can say that it is still something I find challenging.

### Explanation of texture lookup and height scaling ###
For texture lookup I decided to index the texture file based on how many different "textures" that were in there.
example dirt = 0, grass = 1, snow = 2, etc etc.
I also in my Texture class added a variable for holding the number of rows that the texture atlas represented. In this assignment that was 4.
My SceneObject now also started to hold on its textureIndex, which were passed of to the renderer and calculated there.
Now, that index is only one Uint so more calculations had to me done to find the actual texture offset in the textureFile.
to calculate that I took my "index % number of rows" in the texture to find out how much I had to travel in xDirection in the file.
to caluclate how much I had to travel in y direction I took "index / number of rows". I then divided these results on the number of rows, to clamp into 0-1 values.
then I sent the texture offset into the vertex shader. In my vertex shader I first took the original textureCoordinates from the mesh, and scaled them down so they would fit into the "scale" of the texture file. Did this by dividing them with the number of rows of the texture, which I sent it by uniform. For example, if numberOfRows = 4, and textureCoordinates is in 0-1 values, then the new textureCoordinates will now be in range 0-0.25. Then I added on the offset that I calculated earlier based on my index. 

Doing Scaling in the vertex shader was done by sending in a uniform scale matrix that I applied to all the vertexPositions.
I already sent in a modelmatrix representing the normal model in worldspace, and but now we also added the worldScale.
Since order is important in matrixMultiplication I decided to send to rather calculate all the matrices needed in the vertex shader, so I calculate the whole MVP down there + the scaling.
Another solution could be to just make a scale matrix inside the vertex shader, and only send in a float as a uniform. But we then still need to calculate the MVP in there, however we would not need to send the whole 4x4 worldscale matrix that we do now. 

### Describe the problem in this task which Mip-mapping would be solve ###
Mipmapping is a "texturing" technique done mainly to avoid artifacts like for examples moiré patterns.
The technique involves taking a high resolution picture, scaling it down and filter it into several resolutions.
In my case mipmapping would solve the aliasing I am struggling with when I look at my textures at the "right/wrong angle",
leading to artifacts in my textures. This is especially noticable in my program if you have a larger map, and press m enough time to get the "1" texture on the ground, you will see that in the distance the black colors from the "1" texture blends into each other, if you for instance stand in one particular angle, the vertical number 1, can turn into a horizontal black line. 
The artifacts is a result of sampling from a high resolution image when drawing stuff far away, which leads to the colors blending into each other in an unintended fashion.  


## Exam Details ##

### Exam Q&A ###
Any question asked by students during the exam will *only* be answered here not directly.

### Exam Details ###

Due 27th November 2015 at 12:00.  This 3 day, take home exam, together with the oral, will be worth 60% of the grade for the course. Each student will select a 10-12 minute slot on the 30th of November for an oral discussion of their project. You will have received and email to participate on the 23rd at about 12:15.

### Process ###
You will fork the repository https://bitbucket.org/simonmccallum/imt2531-exam-2015. You will give Johannes  and Simon  read access to the forked repository. You will commit your code every 1 hour of development time.  Thus I expect about 20+ commits. There is no limit on more commits, but you should have at least 10.  You will be marked on both the final state of the exam and also the process. Commits will be meaningful. You will also push the repository to Bitbucket every couple of hours so we can see your progress.
You will document your development by writing comments and answering the questions in the readme of your exam repository.  24 hour into the exam (Wednesday at 12:00) we will run a test of the code to see if we can compile your partial solutions. This gives you a chance to see that you have a generally functional framework.

### Task: Create a Block world ###
This will be achieved by:

* test
* Loading a model from a command line parameter. The command line will be exam2015.exe terrain.pnm.  This is a pnm image which is a height map.  This type of terrain information is called a Digital Elevation Model (DEM).  This is a simplified version of the ArcASCII format of DEM files. We will test with a different file to make sure that the code is reading the file and loading the blocks accordingly.
    * The file header contains “P2 width height max [data]”.  The amount of data is width * height integers.
    * Load the file into an array. This is the height in number of blocks at each location on the map.
* Display the map on screen by creating cubes stacked on top of each other to the height specified. Each cube should be placed on top of a cube below.
The cubes should be textured with different textures according to height
    * h 0   , 1 =  water ( texture[3] in texture.png )
    * h 2   =   dirt ( texture [0] in texture.png )
    * h 3  - 17 = grass ( texture[1] in texture.png )
    * h 18 -20 = snow. ( texture[2] in texture.png )
* You should position the camera to see the terrain from an isometric position.
* You will implement a sun, which provides directional lighting. Start with the sun at about 20 degrees.  
* Pressing “2” will advance the sun. The sun will move from one side of the model to the other.  You do not need to implement shadows, but the light direction will determine the amount of light falling on the cubes. “1” will move in the opposite direction.
* You will implement height scaling in the vertex shader. This will be done by passing a scaling factor as a uniform to the shader. When the user presses “0” it will reset the scaling factor to 1. Pressing “9” will increase the height of every block and therefore the location of every block. Pressing “8” will decrease the height of every block. 

Extra Credit 

* First Person mode walking around on the landscape
* Destroying the block in front of you pressing space “ “.
* Creating a block immediately under the player by pressing “b”
* Adding Shadows
* Adding cliffs by calculating when there is a vertical difference of more than 1 block and using dirt (texture[0]) on the sides of the blocks exposed.
Having the sky dome change colour at “sunrise” and “sunset”.

Notes

* OpenGL 3.x or 4.x is required.
* You can use the shaders and file loaders from assignments.
* The program should compile and run in Visual Studio 2013 or 2015, SDL2.0.x and C/C++

### Questions from Students ###
  If you have any questions email them to both Simon and Johannes with the subject “IMT2531 Exam Question”. Questions and answers will be added to the exam FAQ on the Bitbucket repository and emailed to the class.  Do not wait until Friday if you have a question.