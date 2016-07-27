/* 
 * File:   collision.hpp
 * Authors: Nick Koirala (original version), ahnonay (SFML2 compatibility)
 *
 * Collision Detection and handling class
 * For SFML2.

Notice from the original version:

(c) 2009 - LittleMonkey Ltd

This software is provided 'as-is', without any express or
implied warranty. In no event will the authors be held
liable for any damages arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute
it freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented;
   you must not claim that you wrote the original software.
   If you use this software in a product, an acknowledgment
   in the product documentation would be appreciated but
   is not required.

2. Altered source versions must be plainly marked as such,
   and must not be misrepresented as being the original software.

3. This notice may not be removed or altered from any
   source distribution.

 *
 * Created on 30 January 2009, 11:02
 */

/*
SFML
----

SFML - Copyright (C) 2007-2013 Laurent Gomila - laurent.gom@gmail.com

This software is provided 'as-is', without any express or
implied warranty. In no event will the authors be held
liable for any damages arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute
it freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented;
   you must not claim that you wrote the original software.
   If you use this software in a product, an acknowledgment
   in the product documentation would be appreciated but
   is not required.

2. Altered source versions must be plainly marked as such,
   and must not be misrepresented as being the original software.

3. This notice may not be removed or altered from any
   source distribution.



External libraries used by SFML
-------------------------------

* OpenAL-Soft is under the LGPL license
* libsndfile is under the LGPL license
* libjpeg is public domain
* stb_image and stb_image_write are public domain
* freetype is under the FreeType license or the GPL license
* GLEW is under the modified BSD License, the Mesa 3-D License (MIT License), and the Khronos License (MIT License)


SFML - Simple and Fast Multimedia Library
=========================================

SFML is a simple, fast, cross-platform and object-oriented multimedia API. It provides access to windowing, graphics,
audio and network.
It is written in C++, and has bindings for various languages such as C, .Net, Ruby, Python.

Authors
-------

Laurent Gomila - main developer (laurent.gom@gmail.com)
Marco Antognini - OS X developer (antognini.marco@gmail.com)

Download
--------

You can get the latest official release on SFML website (http://www.sfml-dev.org/download.php).
You can also get the current development version from the git repository (https://github.com/LaurentGomila/SFML).

Install
-------

Follow the instructions of the tutorials (http://www.sfml-dev.org/tutorials.php), there is one for each platform/compiler that SFML supports.

Learn
-----

There are several places to learn SFML:
* The official tutorials (http://www.sfml-dev.org/resources.php#tutorials)
* The online API documentation (http://www.sfml-dev.org/resources.php#documentation)
* The community wiki (https://github.com/LaurentGomila/SFML/wiki/)
* The community forum (http://en.sfml-dev.org/forums/) (or http://fr.sfml-dev.org/forums/ for french people)

Contribute
----------

SFML is an open-source project, and it needs your help to go on growing and improving.
Don't hesitate to post suggestions or bug reports on the forum (http://en.sfml-dev.org/forums/),
submit patches by e-mail, or post new bugs/features requests on the task tracker (https://github.com/LaurentGomila/SFML/issues/).
You can even fork the project on github, maintain your own version and send us pull requests periodically to merge your work.

*/


#include <SFML\Graphics.hpp>

#ifndef COLLISION_H
#define COLLISION_H

namespace Collision {
    //////
    /// Test for a collision between two sprites by comparing the alpha values of overlapping pixels
    /// Supports scaling and rotation
    /// AlphaLimit: The threshold at which a pixel becomes "solid". If AlphaLimit is 127, a pixel with
    /// alpha value 128 will cause a collision and a pixel with alpha value 126 will not.
    /// 
    /// This functions creates bitmasks of the textures of the two sprites by
    /// downloading the textures from the graphics card to memory -> SLOW!
    /// You can avoid this by using the "CreateTextureAndBitmask" function
    //////
    bool PixelPerfectTest(const sf::Sprite& Object1 ,const sf::Sprite& Object2, sf::Uint8 AlphaLimit = 0);

    //////
    /// Replaces Texture::loadFromFile
    /// Load an imagefile into the given texture and create a bitmask for it
    /// This is much faster than creating the bitmask for a texture on the first run of "PixelPerfectTest"
    /// 
    /// The function returns false if the file could not be opened for some reason
    //////
    bool CreateTextureAndBitmask(sf::Texture &LoadInto, const std::string& Filename);

    //////
    /// Test for collision using circle collision dection
    /// Radius is averaged from the dimensions of the sprite so
    /// roughly circular objects will be much more accurate
    //////
    bool CircleTest(const sf::Sprite& Object1, const sf::Sprite& Object2);

    //////
    /// Test for bounding box collision using the Seperating Axis Theorem
    /// Supports scaling and rotation
    //////
    bool BoundingBoxTest(const sf::Sprite& Object1, const sf::Sprite& Object2);
}

#endif  /* COLLISION_H */