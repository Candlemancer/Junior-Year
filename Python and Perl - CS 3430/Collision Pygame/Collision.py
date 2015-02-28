# Jonathan Petersen
# A01236750
# Collision Pygame Assignment
# Collision Game Class

import pygame;
from pygame.locals import *;
from sys import exit;

import Mom;

class Collision:

	# Initialize the game
	def __init__(self):
		pygame.init();
		pygame.display.set_caption("Collision Pygame");

		self.displaySetup();
		self.moms = [ Mom.Mom() for i in xrange(3) ];

		self.gameLoop();


		return;

	def displaySetup(self):
		self.screen = pygame.display.set_mode(
			[self.SCREEN_WIDTH, self.SCREEN_HEIGHT], 
			self.SCREEN_FLAGS, 
			self.BIT_DEPTH);
		
		self.fp_backgroundImage = pygame.image.load(self.fp_backgroundImage).convert();
		self.fp_backgroundImage = pygame.transform.scale(
			self.fp_backgroundImage, 
			(self.SCREEN_WIDTH, self.SCREEN_HEIGHT)
		);

		self.fp_playerSprite = pygame.image.load(self.fp_playerSprite).convert_alpha();

		return;

	def gameLoop(self):
		while (True):
			self.checkEvents();
			self.updateScreen();

		return;


	def checkEvents(self):
		for event in pygame.event.get():
			if (event.type == QUIT):
				exit(0);

		return;


	def updateScreen(self):
		self.screen.blit(self.fp_backgroundImage, (0, 0));

		self.updatePlayer();
		self.updateEnemy();

		pygame.display.update();
		return;


	def updatePlayer(self):
		self.screen.blit(self.fp_playerSprite, (self.playerX, self.playerY));

		return;


	def updateEnemy(self):
		for mom in self.moms:
			self.screen.blit(mom.currentSprite, (mom.momX, mom.momY));
			mom.move();

		return


	fp_backgroundImage = "field.jpg";
	fp_playerSprite = "ChildForward.png";

	SCREEN_WIDTH = 640;
	SCREEN_HEIGHT = 480;
	SCREEN_FLAGS = 0
	# | pygame.FULLSCREEN
	# | pygame.DOUBLEBUF
	# | pygame.HWSURFACE
	# | pygame.OPENGL
	# | pygame.NOFRAME
	BIT_DEPTH = 32;
	screen = 0;

	playerX = 0;
	playerY = 0;

	moms = [];

