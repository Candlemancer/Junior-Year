# Jonathan Petersen
# A01236750
# Collision Pygame Assignment
# Mom Class

import pygame;
import random;

class Mom:

	currentSprite = None;
	fp_walkLeft = ["MomLeft.png", "MomLeft.png", "MomLeft.png"];
	fp_walkRight = ["MomRight.png", "MomRight.png", "MomRight.png"];

	momX = 100;
	momY = 100;
	momV = -1;

	def __init__(self, xIni = 0, yIni = 0, vIni = 0):	
		xIni = random.randint(10, 630);
		yIni = random.randint(1, 7) * 50;
		vIni = random.randint(1, 3);
		
		# for frame in self.fp_walkLeft:
		# 	frame = pygame.image.load(frame).convert_alpha();
		# for frame in self.fp_walkRight:
		# 	frame = pygame.image.load(frame).convert_alpha();

		self.momX = xIni;
		self.momY = yIni;
		self.momV = vIni;
		self.move();


	def move(self, minWidth = 0, maxWidth = 640):
		if (self.momV < 0):
			self.currentSprite = pygame.image.load(self.fp_walkLeft[1]).convert_alpha();
		if (self.momV > 0):
			self.currentSprite = pygame.image.load(self.fp_walkRight[1]).convert_alpha();

		self.momX += self.momV;

		if (self.momX < minWidth):
			self.momV *= -1;
			self.momX = minWidth + 1;
			mom = self.fp_walkRight[1];
		if (self.momX + self.currentSprite.get_width() > maxWidth):
			self.momV *= -1;
			self.momX = maxWidth - self.currentSprite.get_width() - 1;
			mom = self.fp_walkLeft[1];

	def getCollisionBox(self):
		return [[self.momX, self.momY],
				[self.currentSprite.get_width(), self.currentSprite.get_height() / 3]];		


	def reverseDirection(self):
		self.momV *= -1;

		return;
