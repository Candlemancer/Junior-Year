# Jonathan Petersen
# A01236750
# Collision Pygame Assignment
# Collision Game Class

import pygame;

class Collision:

	# Initialize the game
	def __init__(self):
		pygame.init();
		pygame.display.set_caption("Collision Pygame");

	def displaySetup(self):
		screen = pygame.display.set_mode([SCREEN_WIDTH, SCREEN_HEIGHT], SCREEN_FLAGS, BIT_DEPTH);




	fp_backgroundImage = "";
	fp_playerSprite = "";
	fp_enemySprite = "";

	SCREEN_WIDTH = 640;
	SCREEN_HEIGHT = 480;
	SCREEN_FLAGS = 0
	# | pygame.FULLSCREEN
	# | pygame.DOUBLEBUF
	# | pygame.HWSURFACE
	# | pygame.OPENGL
	# | pygame.NOFRAME
	BIT_DEPTH = 32;
