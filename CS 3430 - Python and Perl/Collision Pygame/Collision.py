# Jonathan Petersen
# A01236750
# Collision Pygame Assignment
# Collision Game Class

import pygame;
from pygame.locals import *;
from sys import exit;

import Mom;
import Son;

class Collision:

	# Initialize the game
	def __init__(self):
		pygame.init();
		pygame.display.set_caption("Collision Pygame");
		pygame.font.init();
		self.textFont = pygame.font.Font(None, 24);

		self.displaySetup();
		self.player = Son.Son();
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

		return;

	def gameLoop(self):
		while (True):
			self.checkEvents();
			self.checkCollisions();
			self.updateScreen();

		return;


	def checkEvents(self):
		currentKey = pygame.key.get_pressed();
		if currentKey[K_UP]:
			self.player.moveUp();
		if currentKey[K_DOWN]:
			self.player.moveDown();
		if currentKey[K_LEFT]:
			self.player.moveLeft();
		if currentKey[K_RIGHT]:
			self.player.moveRight();
		for event in pygame.event.get():
			if (event.type == QUIT):
				exit(0);


		return;


	def checkCollisions(self):
		for mom in self.moms: 
			if (
				pygame.Rect(self.player.getCollisionBox())
				.colliderect(pygame.Rect(mom.getCollisionBox())) and
				self.hitCooldown == 0
			):
				self.hits += 1;
				self.hitCooldown = 45;
				mom.reverseDirection();

		if (self.hitCooldown > 0):
			self.hitCooldown -= 1;

		return;


	def updateScreen(self):
		self.screen.blit(self.fp_backgroundImage, (0, 0));

		self.updateEnemy();
		self.updatePlayer();
		self.updateCounter();

		pygame.display.update();
		return;


	def updateCounter(self):
		text = self.textFont.render("Hits: " + str(self.hits), 1, (10, 10, 10));
		self.screen.blit(text, (self.SCREEN_WIDTH / 2 - text.get_width() / 2, 0));

		print "~~~~~~~~~"
		return;


	def updatePlayer(self):
		self.screen.blit(self.player.currentSprite, (self.player.sonX, self.player.sonY));

		return;


	def updateEnemy(self):
		for mom in self.moms:
			self.screen.blit(mom.currentSprite, (mom.momX, mom.momY));
			mom.move();

		return


	fp_backgroundImage = "field.jpg";

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

	textFont = None;

	moms = [];
	player = None;

	hits = 0;
	hitCooldown = 45;


