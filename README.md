# IMT2531 Graphics Programming - Exam 2015 #

## Per-Morten Straume ##

You will replace this text with the documentation of your progress and your solution
Buttons mapped to features:
** 9 Raise Scale

** 8 Lower Scale

** 0 Reset Scale

** 1 Earlier Sun

** 2 Later Sun

Extra Features:
** p toggle camera movement on and off
** w Move camera in the direction you are facing
** s Move camera backwards from the direction you are facing
** a Strafe camera Left
** d Strafe Camera Right
** x Move camera down
** c Move camera Up
** k create block below you (/continue building on the stack you are standing "in")
** i destroy block below you (/destroy the block on top of the stack you are standing "in")
** m NextTexture, scrolls through the different texture sets.
** n toggle Rain (turns on a cloud and starts pouring down rain)
** t toggle Snow (turns on a cloud and turns the world into a snowy landscape with icy water and powdery snow)



## Questions to Answer ##

### Resources used ###
Websites and other resources used.  With large sites provide more details of which page, for example which stack overflow question.
For doing the texture atlas:
https://www.youtube.com/watch?v=6T182r4F6J8

For doing camera movement:
https://www.youtube.com/watch?v=HhXzKOMkA1k for Horizontal
https://www.youtube.com/watch?v=7oNLw9Bct1k for Vertical
https://www.youtube.com/watch?v=v6RZRPo0O3k for Keyboard

Also worked togheter on a lot of the task with Claus, Fredrik and Sebastian.

### Most difficult part of code ###
What part of the code caused the most problems.

### Explanation of texture lookup and height scaling ###
Here you must explain how you dealt with texture lookup and scaling of the vertex height.

### Describe the problem in this task which Mip-mapping would be solve ###
You need to describe the problem related to textures in this block world which mip-mapping of the texture would solve.

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