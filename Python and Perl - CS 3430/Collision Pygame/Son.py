# Jonathan Petersen
# A01236750
# Collision Pygame Assignment
# Son Class

import pygame;
import random;

class Son:

	currentSprite = None;
	fp_walkLeft = ["SonLeft.png", "SonLeft.png", "SonLeft.png"];
	fp_walkRight = ["SonRight.png", "SonRight.png", "SonRight.png"];

	sonX = 100;
	sonY = 100;
	sonV = -1;

	def __init__(self, xIni = 0, yIni = 0, vIni = 0):
		
		xIni = random.randint(10, 630);
		yIni = random.randint(1, 7) * 50;
		vIni = random.randint(1, 3);

		self.sonX = xIni;
		self.sonY = yIni;
		self.sonV = vIni;
		self.move();


	def move(self, minWidth = 0, maxWidth = 640):

		if (self.sonV < 0):
			self.currentSprite = pygame.image.load(self.fp_walkLeft[1]).convert_alpha();
		if (self.sonV > 0):
			self.currentSprite = pygame.image.load(self.fp_walkRight[1]).convert_alpha();

		self.sonX += self.sonV;

		if (self.sonX < minWidth):
			self.sonV *= -1;
			Son = self.fp_walkRight[1];
		if (self.sonX + self.currentSprite.get_width() > maxWidth):
			self.sonV *= -1;
			Son = self.fp_walkLeft[1];

		
