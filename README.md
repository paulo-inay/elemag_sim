# elemag_sim
Simple implementation of the Yee algorithm for 2D waves in C++. Creates heatmap images for visualization using the [png++][png++] API.

## Future Developments

* Refactor the code and use proper linkage;
* Script for checking and installing requirements (currently libpng, will probably use other libs in the future);
* Minimize memory usage (execute one step of the algorithm at a time);
* Create videos with FFmpeg;
* Implement more boundary conditions (currently the boundaries reflect the electromagnetic wave);
* Optimize performance;
* Other simulations:
  * 1D waves;
  * 3D waves;
  * Cases with more than one medium;
  * Other CEM algorithms and visualizations.

## How to Execute

Make sure you have libpng installed. Simply execute make in your command line in the main directory, the results of all the tests implemented should be in the build directory if everything goes well.

## Example
Interference pattern caused by the reflection of an electromagnetic wave propagating from a single source.

![EX_IMG1](https://github.com/paulo-inay/elemag_sim/blob/master/eximage.png)

Waves propagating from two distinct sources.

![EX_IMG2](https://github.com/paulo-inay/elemag_sim/blob/master/eximage2.png)

## Algorithm Explanation

TBD

[png++]: https://www.nongnu.org/pngpp/
