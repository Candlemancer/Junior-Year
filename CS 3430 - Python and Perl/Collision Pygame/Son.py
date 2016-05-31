# Jonathan Petersen
# A01236750
# Collision Pygame Assignment
# Son Class

import pygame;
import random;

class Son:

	currentSprite = None;
	fp_walkUp = ["SonUp.png", "SonUp.png", "SonUp.png"];
	fp_walkDown = ["SonDown.png", "SonDown.png", "SonDown.png"];
	fp_walkRight = ["SonRight.png", "SonRight.png", "SonRight.png"];
	fp_walkLeft = ["SonLeft.png", "SonLeft.png", "SonLeft.png"];

	sonX = 100;
	sonY = 100;

	def __init__(self, xIni = (640 / 2 - 32 / 2), yIni = 430):
		self.sonX = xIni;
		self.sonY = yIni;
		self.currentSprite = pygame.image.load(self.fp_walkDown[1]).convert_alpha();

		return;

	def getCollisionBox(self):
		return [[self.sonX, self.sonY],
				[self.currentSprite.get_width(), self.currentSprite.get_height() / 3]];


	def moveUp(self):
		self.sonY -= 3;
		self.currentSprite = pygame.image.load(self.fp_walkUp[1]).convert_alpha();

		return;


	def moveDown(self):
		self.sonY += 3;
		self.currentSprite = pygame.image.load(self.fp_walkDown[1]).convert_alpha();

		return;


	def moveRight(self):
		self.sonX += 3;
		self.currentSprite = pygame.image.load(self.fp_walkRight[1]).convert_alpha();

		return;


	def moveLeft(self):
		self.sonX -= 3;
		self.currentSprite = pygame.image.load(self.fp_walkLeft[1]).convert_alpha();

		return;


