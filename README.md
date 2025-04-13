# FdF - Wireframe Model Renderer

![Alt text](https://github.com/ipuig-pa/02_FdF/blob/master/images/mars.png)

This project was developed individually by:

- @ipuig-pa

## Project Overview

---

This project consists on a wireframe renderer that creates a graphic representation of a relief landscape by surfaces outlined in line segments. It introduces the basics of graphic programming, focusing on placing points in space and viewing the scene from different perspectives.

### Resources

- miniLibX: this project uses miniLibX graphical library, from 42 School.
- test_maps: test maps files were provided from 42 School.
- Custom libft and ft_printf library

## Rendering

---

### Compilation

- Use `make` to compile the project.

### Running

- Run the program with the map file name as an argument: `./fdf [map_file.fdf]` .

### Map files

Map files use the `.fdf` extension and contain a grid of integers representing the height of each point in the landscape. Each number represents:

- Horizontal position (separated by spaces): X coordinate
- Vertical position (separated by new lines): Y coordinate
- Value: Z coordinate (altitude)

Right after the Z coordinate, and separated by a coma, a hexadecimal value representing the color in RGB can optionally be given. 

- Hexadecimal value: Color

In the absence of the color field, color representation will be taken from the altitude (max altitude = RED; min altitude = WHITE) 

**Example of map (.fdf) file**

```
#42.fdf

0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0 10 10  0  0 10 10  0  0  0 10 10 10 10 10  0  0  0
0  0 10 10  0  0 10 10  0  0  0  0  0  0  0 10 10  0  0
0  0 10 10  0  0 10 10  0  0  0  0  0  0  0 10 10  0  0
0  0 10 10 10 10 10 10  0  0  0  0 10 10 10 10  0  0  0
0  0  0 10 10 10 10 10  0  0  0 10 10  0  0  0  0  0  0
0  0  0  0  0  0 10 10  0  0  0 10 10  0  0  0  0  0  0
0  0  0  0  0  0 10 10  0  0  0 10 10 10 10 10 10  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
```

**Example of map (.fdf) file with colors**

```
#elem-col.fdf

0  0  0          0           0  0           0           0           0   0
0 10 10          10          10 10          10          10          10  0
0 10 20,0xFF0000 15,0xFF0000 12 15,0xFF0000 17,0xFF0000 20,0xFF0000 10  0
0 10 15,0xFF0000 10          12 15,0xFF0000 15,0xFF0000 15,0xFF0000 10  0
0  5 15,0xFF0000 10          12 15,0xFF0000 15,0xFF0000 13          10  0
0  5 10          5           7  12          12          12          10  0
0  5  7          1           2  7           5           5           7   0
0  3  0          0           1  2           2           2           5   0
0  1  0          0           0  0           0           0           3   0
0  0  0          0           0  0           0           0           0   0
```

### Features / implementation details

- Isometric projection of 3D landscapes → Line drawing algorithm
- Automatic scaling to optimal fit the predefined window dimensions (set in the header file)
- Basic window and event management (minimize, close, Esc)
- Color gradient based on altitude or taken from map → color interpolation

## Examples of output

---
![Alt text](https://github.com/ipuig-pa/02_FdF/blob/master/images/42.png)
Simple test example of a non-color coded map, with color gradient derived from altitude



![Alt text](https://github.com/ipuig-pa/02_FdF/blob/master/images/mars.png)
Big non-color coded map, with color gradient derived from altitude, symbolizing Mars surface



![Alt text](https://github.com/ipuig-pa/02_FdF/blob/master/images/custom.png)
Custom map with color-coded points



![Alt text](https://github.com/ipuig-pa/02_FdF/blob/master/images/t2.png)
Big color-coded surface, symbolizing Earth surface

## License

---

This project was developed as part of the curriculum at 42 School. Use of this code must comply with the school's academic integrity policies.
