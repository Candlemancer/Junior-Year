# Jonathan Petersen
# A01236750
# Diagonal Pygame Assignment

import pygame;
import random;
from pygame.locals import *;
from sys import exit;


# Set image paths
fp_backgroundImage = "mountain.jpg";
fp_spriteImage = "SnowSprite.png";

screenWidth = 640;
screenHeight = 480;
screenFlags = 0
# | pygame.FULLSCREEN
# | pygame.DOUBLEBUF
# | pygame.HWSURFACE
# | pygame.OPENGL
# | pygame.NOFRAME
bitDepth = 32;


# Start the game
pygame.init();

# Setup the Screen
screen = pygame.display.set_mode([screenWidth, screenHeight], screenFlags, bitDepth);
pygame.display.set_caption("Snow Scene");

# Load the Art assets
fp_backgroundImage = pygame.image.load(fp_backgroundImage).convert();
fp_spriteImage = pygame.image.load(fp_spriteImage).convert_alpha();
fp_backgroundImage = pygame.transform.scale(fp_backgroundImage, (640, 480));

x = 0;
y = 0;
A = [];

# for i in range(1, 100) :
# 	A.append((
# 		random.randint(0, screenWidth), 
# 		random.randint(0, screenHeight),
# 		random.randint(1, 4)
# 	));

# Start the game loop
shouldExit = False;
while (shouldExit != True) :

	# Handle events
	for event in pygame.event.get() :
		if event.type == QUIT :
			del fp_backgroundImage;
			del fp_spriteImage;
			shouldExit = True;
			exit(0);

	# Refresh the background image
	screen.blit(fp_backgroundImage, (0, 0));

	# Update the Sprite
	x += 1;
	y += 1;

	# screen.blit(fp_spriteImage, (x, y));
	for location in A :
		screen.blit(fp_spriteImage, (
			(location[0] + x * location[2]) % screenWidth, 
			(location[1] + y * location[2]) % screenHeight)
		);

	A.append((
		random.randint(0, screenWidth), 
		random.randint(0, screenHeight),
		random.randint(1, 4),
	));

	pygame.display.update();
	
# Terminate the game	
pygame.quit();
exit(0);
