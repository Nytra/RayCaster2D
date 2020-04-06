# SDL2_2D_RayCaster

FLAWLESS RAYCASTING! BY THE POWER OF MATH!

![Demo](https://github.com/Nytra/SDL2_2D_RayCaster/blob/master/raycastingBest1.gif)

If you want to try this for yourself, download the repo and run "MenuFramework.exe" (i forgot to change the name)
Then just use your mouse or trackpad to move the raycaster object around on the screen. The walls are randomly generated at runtime.

Here you can see the exact line-intersect geometry code that the raycaster now uses. It took me a while to set this up and I still don't fully understand it really. I borrowed this from here https://stackoverflow.com/a/1968345

The function takes four points (a, b, c, d) as inputs. ab and cd are the two lines.

ab will always be the ray line. cd will always be one of the four sides of a rectangle. this is repeated for every rectangle in the scene, and then there is a bit of code that picks the closest point of intersection to the start of the ray (for each ray casted).

![Demo](https://github.com/Nytra/SDL2_2D_RayCaster/blob/master/geometrycode.PNG)

Below are some gifs recorded at various stages of development. You can see the different techniques that I used throughout. Only the above gif demonstrates the use of actual line-intersect geometry.

![Demo](https://github.com/Nytra/SDL2_2D_RayCaster/blob/master/raycasting1.gif)

Raycasting but with a larger gap between point checks. Results in some rays penetrating the solid walls and in some cases even ignoring the walls altogether. It is way faster though and results in more rays being casted (not sure why) I think it produces a cool effect though.

![Demo](https://github.com/Nytra/SDL2_2D_RayCaster/blob/master/raycasting2fast.gif)

And raycasting with a smaller gap between point checks.

![Demo](https://github.com/Nytra/SDL2_2D_RayCaster/blob/master/raycasting3.gif)
