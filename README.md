# elemag_sim
Simple implementation of the Yee algorithm for 2D waves in C++. Creates heatmap images for visualization using the [png++][png++] API.

## Future Developments

* Refactor the code and use proper linkage
* Script for checking and installing requirements (currently libpng, will probably use other libs in the future)
* Minimize memory usage (execute one step of the algorithm at a time)
* Create videos with FFMPEG
* Optimize performance
* Other simulations (1D, 3D, other CEM algorithms and visualizations)

## How to Execute

Make sure you have libpng installed. Simply execute make in your command line in the main directory, the results of all the tests implemented should be in the build directory if everything goes well.

[png++]: https://www.nongnu.org/pngpp/
