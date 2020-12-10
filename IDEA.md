# Dungeon Crawler

## Meta

Group                  4
Jan Zoppe              1433409
Robert Andreas Fritsch 1431348
Date                   2020-12-09

## Abstract

A simple 3D dungeon crawler, where you control a character inside a dungeon.
The character has to solve a simple riddle. (select and place objects)

## Aspects

### Camera Movement

The "bird view" camera is fixed to the player.

### Geometric Modelling

Low Poly objects mostly generated. (like barrels and walls)

### Texturing and Skybox

All object textures use image files or procedual generation.

### Lighting

The Player has its own light source.
Further Light sources like torches may be added later.
Reflections and Shadows!

HOW:
- write shader with multiple light sources

### Animation

Player get simple Skeletal animation.

HOW:
- implement skeletal animation

### Level loding

Using ASCII-Files or BMP-Files for visual editing.

```
 #########
##    BBC#
#   T  B #
#      B #
#        #
#  P   ###
########  
```

where:
 P - Player spawn
\# - Wall
 T - Table
 B - Barrel
 C - Chest

### Collision

Only 2D collisions which can be significantly simplified,
as we only have circles (Player and Barrels) and axis aligned rectangles (Walls, Tabels and Chests) to check.

## Timeline

2020-12-10 - Current State
2021-01-07 - Loading level with all objects and character (all static)
           - Character can move around
           - Character collides with objects
           - Camera following character
           - (search for free assets)
2021-01-21 - Add Character animation
           - Lighting
           - Shadows
2021-02-04 - Add game logic (interaction / little riddle)
           - Reflection
2021-02-11 - Final Testing
           - Final Presentation
