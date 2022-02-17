#include "colors.inc"  

background { color White }

sphere {  <10, 2, 0>, 2
    pigment { Blue } }

cylinder { <10, 2, 0>,  <0, 2, 10>, 0.7         
    pigment { color Red } } 

sphere {  <0, 2, 10>, 4
    pigment { Green transmit 0.4} }

cylinder { <0, 2, 10>,  <-10, 2, 0>, 0.7         
    pigment { Red } } 

sphere {  <-10, 2, 0>, 2
    pigment { Blue } }

plane { <0, 1, 0>, -5
    pigment { checker color White, color Black}}

light_source { <10, 30, -3> color White} 

camera {location <0, 8, -20>
    look_at  <0, 2,  10>
    aperture 0.4}
