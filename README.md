DevIL for Marmalade
===================

Image loading library for Marmalade C++. The animated (gif) and mipmaps formats supported.

Based on DevIL 1.7.8 - http://openil.sourceforge.net/about.php

Few format have been disabled because of the dependencies. They could be added later.

Supported formats
-----------------

Format|Loading|Saving
------|-------|------
Windows Bitmap - .bmp|y|y
Dr. Halo - .cut|y|n
Multi-PCX - .dcx|y|n
Dicom - .dicom, .dcm|y|n
DirectDraw Surface - .dds|y|y
OpenEXR - .exr|o|o
Flexible Image Transport System - .fits, .fit|y|n
Heavy Metal: FAKK 2 - .ftx|y|n
C-style Header - .h|n|y
Radiance High Dynamic - .hdr|y|n
Macintosh icon - .icns|y|n
Windows icon/cursor - .ico, .cur|y|n
Interchange File Format - .iff|y|n
Infinity Ward Image - .iwi|y|n
Graphics Interchange Format - .gif|y|n
Jpeg - .jpg, .jpe, .jpeg|y|y
Jpeg 2000 - .jp2|o|o
Interlaced Bitmap - .lbm|y|n
Homeworld texture - .lif|y|n
Half-Life Model - .mdl|y|n
MPEG-1 Audio Layer 3 - .mp3|y|n
Palette - .pal|y|y
Kodak PhotoCD - .pcd|y|n
ZSoft PCX - .pcx|y|y
Softimage PIC - .pic|y|n
Portable Network Graphics - .png|y|y
Portable Anymap - .pbm, .pgm, .pnm, .pnm|y|y
Alias , Wavefront - .pix|y|y
Adobe PhotoShop - .psd|y|y
PaintShop Pro - .psp|y|n
Pixar - .pxr|y|n
Raw data - .raw|y|y
Homeworld 2 Texture - .rot|y|n
Silicon Graphics - .sgi, .bw, .rgb, .rgba|y|y
Creative Assembly Texture - .texture|y|n
Truevision Targa - .tga|y|y
Tagged Image File Format - .tif|o|o
Gamecube Texture - .tpl|y|n
Unreal Texture - .utx|y|n
Quake 2 Texture - .wal|y|n
Valve Texture Format - .vtf|y|y
HD Photo - .wdp, .hdp|y|n
X Pixel Map - .xpm|y|n
Doom graphics|y|n

y = supported
o = not supported, the library could be added
n = not supported

Library Features
----------------
~~(striked texts not valid for this Marmalade extension)~~
* Portable, supports Windows, Mac OS X and *nix.
* OpenGL-style syntax.
* Use of image names instead of pointers.
* Full Unicode support for filenames.
* 64-bit compatibility.
* Loading from files, file streams or memory "lumps".
* Direct access to data through ilGetData() and ilSetData().
* Support for luminance, rgb(a), bgr(a) and colour-indexed images.
* Support for 3 different numbers of bits per channel.
* Conversion between all formats and datatypes (including palettes).
* User-defined automatic conversions if desired when loading images.
* Automatic conversion when saving images if needed.
* Automatic conversion of colour-indexed images to truecolour images if desired.
* Controllable compression when saving.
* Maintains a state stack that can be pushed and popped.
* Full support for 3d texture volumes (3d images).
* Validation of images.
* Support for layers.
* Support for mipmaps.
* Support for animations.
* Support for cubemaps.
* User-specified clear colour.
* Can load a default image if loading fails.
* User-specified hints.
* Use of key colours.
* Support for overlaying an image on top of another.
* Allows the user to specify their own loading and saving callbacks, even overriding the default ones.
* Support for user-specified read and write functions.
* ~~Delphi support.~~
* ~~Visual Basic support.~~
* ~~Linux support.~~
* ~~Can pick and choose which features will be used to create smaller dlls.~~
* ~~Choose whether to use the Intel Jpeg Library or libjpeg.~~
* A whole host of effects and filters to apply to images, such as embossing and edge detection.
* Images can be resized or even be put on a larger background (enlarged canvas).
* ~~OpenGL, Allegro, Windows GDI and DirectX API support.~~
