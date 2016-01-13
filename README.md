# SF-SpaceG
A game (prototype) about dodging objects in the space

This is my first attempt to create a complete game using SFML, actually it's only a prototype on which i implement what i've learned about SFML

WIN32 BINARY:
- https://github.com/ludiaros/SF-SpaceG/releases

CONTROLS:
- Up, W = Thrust up, *make direction equal to sprite angle (not implemented yet)*
- Down, S = Thrust down
- Left, A = Turn left, *keep direction (not implemented yet)*
- Right, D = Turn right, *keep direction (not implemented yet)*
- Ctrl+Left, Ctrl+A = Small turn to left, *change sprite angle but keep direction (not implemented yet)* 
- Ctrl+Right, Ctrl+D = Small turn to right, *change sprite angle but keep direction (not implemented yet)*
- Space = Shoot laser
- Enter = Pause / resume the game
- Esc = Exit to main menu
- NumPad+, MouseWheelUp   = Zoom in
- NumPad-, MouseWheelDown = Zoom out
- NumPad0 = Zoom reset
- Alt+F4 = Close game
- F11 = Full screen / Windowed
- F = Show / Hide FPS
- I = Show / Hide ship information
- R = Align rotation to ship angle
- Y = Reset game after win or game over
- N = Close game after win or game over

CREDITS:
- Font Unique - https://fontlibrary.org/en/font/unique
- Deja Vu Font - http://dejavu-fonts.org/wiki/Main_Page
- Asteroids - http://opengameart.org/content/asteroid-generator-and-a-set-of-generated-asteroids
- Collision detection - https://github.com/SFML/SFML/wiki/Source:-Simple-Collision-Detection-for-SFML-2

TOOLS:
- SFML 2.3
- Inkscape
- Gimp
- Geany
- Code::Blocks

REFERENCES:
- SFML Forums, tutorials and official documentation
- Stackoverflow
- And so many search in Google

TODO:
- 000% - Add sounds
- 000% - Add a level manager
- 000% - Add save / load options
- 000% - Make a configuration interface (key bindings, screen resolution...)
- 010% - Implement a score system
- 020% - More abstraction in some classes for reuse in other projects (it's not necessarily a game engine)
- 040% - Build menus and GUI
- 100% - Make it consistent with framerate changes
- 100% - Implement a State machine for game states (Run, Pause, Initial Screen...)
