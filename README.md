# COSC363-Assignment 1
## Andrew Holden
### Alien Invasion

###1.0 – Description
####1.1 – Setting the scene
        Aliens have invaded Earth! They have taken over an old fortress in the middle of
        nowhere. The aliens have landed in their space ship in the centre of the fortress and
        built a small wooden hangar around it. The hangar opens from the top, so they can
        leave at short notice whenever they feel it necessary. The fortress is still in pretty
        good shape, with a working cannon outside a fully functional draw bridge and no
        visible damage. It also has a marble tile floor which the aliens have polished so that it
        reflects everything above it. The aliens have deployed an invisible light source that
        constantly revolves around the sky casting shadows in different directions. The aliens
        have set up 8 robots to patrol the area, so they can leave in a hurry when a threat
        has been spotted. 2 robots are circling the fortress clockwise and another 2 are
        circling anti-clockwise. The other 4 robots have been placed one on top of each wall
        with a spotlight attached to their head, so they can better see the approach of any
        threats, they patrol along the wall at regular intervals. The aliens can at any time take
        off in their ship to get a better view of the fortress from above.

####1.2 – Technical Description
        This Scene was built inside of a skybox, however because the floor is quite large it
        slowed the scene down too much, so I had to make much larger quads for the
        outlying area that was not used. I then built a fortress with towers, each made from
        2 custom made triangle strip extrusions, one for the roof and one for the body of the
        tower. The walls were made using quads, both for the wall itself, the battlements
        and the gate each with a texture applied. The gate can be raised and lowered using
        the ‘l’ and ‘o’ keys. Inside the fortress the floor is slightly transparent and has a
        marble tile texture to reflect the objects above it. The hangar in the middle of the
        fortress is made from gates which were transformed to be big enough to encompass
        the space ship and its orbiting orbs, it opens from the top when the space ship is
        launched using the ‘s’ key and closes automatically when the space ship lands again.
        The space ship is made from a rotating triangle strip with a parabolic hull, triangles
        make up the fins and cylinders represent the engines. It changes colours constantly
        and has several orbiting orbs, which are always the opposite colour to the ship. The
        robots are made of glut solid objects, including cylinders, a sphere, cubes, and torus.
        The cannon is the same as the one from the labs, it fires a cannon ball with the ‘c’
        key which bounces a few times getting less altitude with each bounce. The main light
        source rotates around the scene constantly to show off the fact that literally
        everything has a shadow. The robots on the walls even have 2 shadows, one on the
        wall and one on the ground as with their reflections. The camera can be moved left
        and right with the left and right keys, it can also be moved up and down with the
        page up and page down keys, so the camera can move in any direction. It cannot go
        through the fortress or the hangar in the middle, however if the gate is completely
        lowered it can go through the front gate. The camera is also limited to a certain area
        so it cannot get too close to the skybox.

###2.0 – Deployment Instructions
    - Download and install CMake and Make from
        https://cmake.org/download/
        https://www.gnu.org/software/make/
    - Clone the repository
    - Open the terminal in the root folder of the cloned repository
    - run the commands:
        cmake CMakeLists.txt
        make
        ./MainScene.out
    - enjoy the scene.

###3.0 – Extra Features
####3.1 – Planar Shadows
        I have cast planar shadows from every object in the scene. The
        fortress, robots (both on the walls and ground), space ship, cannon and hangar all
        have shadows on the ground surface with the robots on the walls also casting a
        shadow on top of the wall as well, I have also made the light source revolve around
        the scene to show this feature off better.
        One difficulty I had with this was that I had nested a few functions to make the code
        more readable as it was growing at an exponential rate. In the end I decided to pass
        in a Boolean to each function in which colours and or textures were used so that the
        appropriate changes could be made if the object was intended to be a shadow.

####3.2 – Spot Lights
        I have placed 4 spotlights in the scene, one on the head of each of the robots
        manning the walls. They move and rotate at regular intervals along with the robots
        which can be clearly seen on both the ground and the fortress walls/towers.
        This I found very difficult to implement at first as when I added a second light source
        it played havoc with my first light source. At first, I managed to fix this by placing the
        light source at the origin first and then moving it to the required location. I have no
        idea why this fixed it and stumbled on the solution by accident. I found a more
        permanent solution however when I started adding animations. It seems that the
        light is only different in the initial render of the scene and after the first
        glutPostRedisplay it fixes itself. So as soon as I added animations that were present
        from the start the error went away.

####3.3 – Additional Animated System Inside the Fortress
        I added a draw bridge to the front of the fortress that can be controlled using the ‘l’
        and ‘o’ keys complete with shadows etc. It sits above the ground when down so as to
        be realistic.

        I also added a hangar as an additional animated system, with doors that open before
        the spaceship takes off and close when it lands.

        I also added Reflections to the floor inside the fortress, these
        include the hangar, fortress, robots, spaceship and the top of the skybox.

####3.4 – Two camera modes
        I implemented an extra camera mode, which
        just swaps over using a Boolean trigger when rendering the scene, that way the
        position of the original camera is not affected and can be returned to. The altitude of
        the space ship is used as the altitude of the camera too which means it goes up and
        down as the ship does.

####3.5 – Physics Models
        The physics model I have used was for the trajectory of the cannonball which
        bounces with a dampener so that it behaves similar to in real life.

####3.6 – Custom Built Sweep Surfaces
        I have 3 of these in my scene, the tower has 2 of these in the body and the roof of
        the tower, and the space ship’s body is also a custom-built sweep surface. All of
        these were extrusions made with triangle strips which I found to look the best for
        the objects I was making.
        The only problem I had with these was that they would grow over time because they
        were not reset after each time they were rendered. This was easily fixed.

####3.7 – Collision Detection
        I used collision detection quite heavily with my camera movement. I made it so the
        camera cannot move too far away from the centre of the scene and it also cannot go
        through the fortress walls, towers, or the hanger. I made it possible however to
        move through the gate portal only if the gate was fully lowered.

####3.8 – Sky Box
        The skybox I used took its texture from one of the textures provided in the labs. The
        walls and the ceiling all use GL_REPLACE whilst the floor uses GL_MODULATE so the
        spotlights etc work properly. I shrank the height of the skybox to make it look better,
        however it’s still pretty obvious where the sides meet the floor.
        This I found incredibly easy to implement at first however incredibly difficult to make
        it look good. I had to play with it a lot in order to get it to the standard I have at the
        moment.

###4.0 – Controls
    Key         |   Function
    -------------------------------
    Up          |   Move the camera forwards
    Down        |   Move the camera backwards
    Left        |   Turn the camera left
    Right       |   Turn the camera right
    Page Up     |   Turn the camera upward
    Page Down   |   Turn the camera downward
    C           |   Fire the cannon
    S           |   Launch the space ship
    O           |   Raise the drawbridge 1 degree
    L           |   Lower the drawbridge 1 degree

###Appendix – References
####Textures:
        https://www.123rf.com/photo_46098525_old-gray-stone-wall-seamless-background-photo-texture.html
        https://www.sketchuptextureclub.com/textures/architecture/roofings/clay-roofs
        https://www.tryfoto.com/photo/3673/wooden-texture
        https://www.sketchuptextureclub.com/textures/architecture/tiles-interior/marble-tiles/white/rhino-marble-floor-tile-texture-
            seamless-14849
####Image conversion to TGA:
        https://image.online-convert.com/convert-to-tga
