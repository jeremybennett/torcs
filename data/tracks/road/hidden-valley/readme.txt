Hidden Valley Track
-------------------

Methods used to generate:-

raceline: ~/torcs_bin/bin/trackgen -c road -n hidden-valley -r
This file was then manually edited to show areas on the track which had been swept "clean" versus corners & braking areas with tyre marks.

shading: I saved the 3D model file as hidden-valley-shad.ac, then manually changed the textures & UV mapping.  Everything with 
"grass-underlay.png" was set to "shadow-terrain.png" and remapped from the top.  All road, trackside grass, curb and sand textures 
were set to shadow.png, remapped from the top and the UV aligned to match.  All other objects were set to "no texture" as if I set
them to shadow.png they end up with ugly smears on vertical surfaces.

acc file: ~/torcs_bin/bin/accc -g hidden-valley.acc -l0 hidden-valley.ac -l1 hidden-valley-shad.ac -l2 hidden-valley-trk-raceline.ac -d3 1000 -d2 500 -d1 300 -S 300 -es

I don't suggest using trackgen to re-create any of the .ac files, as they've all had significant manual work done to them, which would be lost.

If the .acc file needs to be rebuilt, please ensure the material (at the top of the generated file) reads:-

MATERIAL "" rgb 0.70 0.70 0.70 amb 0.80 0.80 0.80 emis 0.40 0.40 0.40 spec 0.10 0.10 0.10 shi  50 trans 0 

.. as this removes unsightly "glare" issues.

-------------------
Copyright © 2017 Andrew Sumner
Some textures borrowed from other tracks in TORCS and may have been created by
other authors.

Copyleft: this work of art is free, you can redistribute
it and/or modify it according to terms of the Free Art license.
You will find a specimen of this license on the site
Copyleft Attitude http://artlibre.org as well as on other sites.
