Aline for the Commander X16
===========================

Aline is a work in progress library for doing vector based graphics.
The main target a the moment is the Commander X16 computer which uses
a 65C02 and there is no graphics hardware accelaration for line
drawing, so everything needs to be done by the CPU.

Aline is written in C with some time critical routines in assembly
language.

The general plan is to have a virtual machine (DSL or EDSL) which
executes instructions that directs the drawing of shapes made up from
a set of lines.

Affine transformations are available, which makes it possible to
scale, flip, rotate (with 2.5 degree resolution) and shear
shapes. Thus, a shape representing a space ship is able to rotate
around its axis, enemies may wiggle after being hit or they could
turn, rotate and dive. They could also tilt towards the direction they
intend to go, perhaps start the tilt a moment before actually starting
a sideways move.

Graphics are intended to be drawn into a screen bitmap. In reality you will
need to plan to make use of sprites for many shapes to keep
computation time within reason for the 6502. Aline can be used to
create such sprites up front. Some important player shapes may be
scaled, rotated and drawn using on the fly calculations, allowing for
much richer animation than if you use sprites. Also, drawn shapes can
easily be larger than a sprite. In the end, generated sprites and
drawn shapes will appear the same way to the player, both being made
up from lines.
