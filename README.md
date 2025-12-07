# Cub3D

This is an introductory project to 3D graphics. The main challenge in this project is to impelement the Digital Differential Analyser (DDA) algorithm. 

DDA sounds scary but all it does is finds distance between two points. In the case of Cub3D we were finding the distance between the player and the wall. Finding this distance allows us determine how large the wall should be rendered. A large distance indicates a small wall should be rendered and likewise a small distance means that the wall should show up as large. They are inversely related. 

We start off with a 2D map with the player in it. The player has a position vector and direction vector. The player also has a field of view. As part of the DDA algorithm we shoot rays that travel until they meet a wall. The algorithm works it's magic and gives us this length of the ray's journey and it is used to draw a vertical strip of pixels on the player's screen. We do this for small angles so it enables us to render a wall. 


It was a great project!
