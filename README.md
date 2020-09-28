# SDL2_2D_RayCaster

FLAWLESS RAYCASTING! BY THE POWER OF MATH!

![Demo](demo_assets/raycastingBest1.gif)

![Demo](demo_assets/raycastingDark1.gif)

![Demo](demo_assets/raycastingDark2.gif)

If you want to try this for yourself, download the latest release and run the executable.
Then just use your mouse or trackpad to move the raycaster object around on the screen. The walls are randomly generated at runtime. You can press P to regenerate them (although the blue square may get stuck inside one)

Here you can see the exact line-intersect geometry code that the raycaster now uses. It took me a while to set this up and I still don't fully understand it really. I borrowed this from here https://stackoverflow.com/a/1968345

The function takes four points (a, b, c, d) as inputs. ab and cd are the two lines.

ab will always be the ray line. cd will always be one of the four sides of a rectangle. this is repeated for every side of every rectangle in the scene, and then there is a bit of code that picks the closest point of intersection to the start of the ray (for each ray casted per frame).

![Demo](demo_assets/geometrycode.PNG)

Below are some gifs recorded at various stages of development. You can see the different techniques that I used throughout. Only the above gifs demonstrate the use of actual line-intersect geometry.

![Demo](demo_assets/raycasting1.gif)

Raycasting but with a larger gap between point checks. Results in some rays penetrating the solid walls and in some cases even ignoring the walls altogether. It is way faster though and results in more rays being casted (not sure why) I think it produces a cool effect though.

![Demo](demo_assets/raycasting2fast.gif)

And raycasting with a smaller gap between point checks.

![Demo](demo_assets/raycasting3.gif)

Build: include SDL2 and SDL2_ttf header files, link to SDL2.lib, SDL2main.lib, SDL2_ttf.lib (also provide SDL2.dll, SDL2_ttf.dll, zlib1.dll, and libfreetype-6.dll with the executable)
