-- Library for setting up a classes
require 'classlib'

-------------- Global simulation constants go here (Don't change them) --------------------
-- Time per move (1 second)
DELTA_TIME = 1.0

-- Starting values for the lander
LANDER_INIT_ALTITUDE = 50.0
LANDER_INIT_VELOCITY = 0.0
LANDER_INIT_FUEL_PLUTO = 10.0
LANDER_INIT_FUEL_MARS = 20.0

-- Lander thruster strength
LANDER_THRUSTER_STRENGTH = 1.0

-- Lander explodes if it reaches the surface going faster than this
MAX_LANDING_VELOCITY = -1.5

-- Planet constants
PLUTO_GRAVITY = 0.5
PLUTO_HEIGHT = 10.0
MARS_GRAVITY = 0.9
MARS_HEIGHT = 1.0
-----------------------------------------------------------------

 --[[--
classLib Usage Notes:
 To construct a new instance:
    myPlanet = Planet("MyPlanet", 0.4, 16)
 To access class members:
    myPlanet.gravity
 To call class methods:
    myPlanet:toString()
 To access members and methods internally:
    self.landingSiteElevation
    self:toString()
--]]--

-- Declare the Planet class which models a Planet, which has a gravity and a landing site elevation height
Planet = class('Planet')

-- Planet class constructor
function Planet:__init(name, gravity, elevation)
  self.name = name
  self.gravity = gravity
  self.landingSiteElevation = elevation
end

-- Returns a string representing the planet
function Planet:toString()
  return self.name .. 
  		 ", gravity: " .. self.gravity .. 
  		 ", landing site elevation: " .. self.landingSiteElevation
end


-- Todo Add all of the required code here
Lander = class('Lander')

-- Lander Class Constructor
function Lander:__init(velocity, altitude, fuelReserve, thrusterStrength)

	-- Default Construct members
	self.velocity = -9.8
	self.altitude = 0.0
	self.fuelReserve = 0.0
	self.thrusterStrength = 0.0

	-- Parameter Construction
	self.velocity = velocity
	self.altitude = altitude
	self.fuelReserve = fuelReserve
	self.thrusterStrength = thrusterStrength
end

-- Returns a string representing the lander
function Lander:toString()
	return "Altitude: " .. self.altitude .. 
		   ", Velocity: " .. self.velocity .. 
		   ", Fuel: " .. self.fuelReserve
end


Simulation = class('Simulation')

-- Simulation Class Constructor
function Simulation:__init(lander, planet, strategy)
	
	-- Default Constructor
	self.lander = nil
	self.planet = nil
	self.strategy = nil

	-- Parameter Constructor
	self.lander = lander
	self.planet = planet
	self.strategy = strategy

end


function Simulation:updateLander(burnRate)

	-- Checks to make sure that the desired burn rate does not exceed the amount of fuel remaining, 
	-- if so, limit the burn rate.
	if (burnRate > self.lander.fuelReserve) then
		burnRate = self.lander.fuelReserve
	end

	-- Updates the altitude and velocity of the lander in the simulation
	self.lander.altitude = self.lander.altitude + (self.lander.velocity * DELTA_TIME)
	self.lander.velocity = self.lander.velocity + (((self.lander.thrusterStrength * burnRate) -
						   self.planet.gravity) * DELTA_TIME)

	-- Update fuel remaining by subtracting the burn rate.
	self.lander.fuelReserve = self.lander.fuelReserve - burnRate

end

-- Checks if the lander has reached the planet’s surface at the landing site elevation
function Simulation:reachedSurface()

	if (self.lander.altitude <= self.planet.landingSiteElevation) then
		return true
	else
		return false
	end

	return false
end

-- Checks if the lander has reached the surface and did so at a safe landing velocity
function Simulation:landed()

	-- print(self.lander.velocity)
	-- print(MAX_LANDING_VELOCITY)

	if (self:reachedSurface() and self.lander.velocity >= MAX_LANDING_VELOCITY) then
		return true
	else
		return false
	end

end


-- Returns a string representation of the relative position of the lander to the planetary
-- surface landing site with | representing planet surface (which might not be at height
-- zero!) and * being the lander. For example: “ | *”
function Simulation:positionString()

	local DISTANCE_PER_CHARACTER = 2

	local elevationPos = 0
	local landerPos = 0

	elevationPos = self.planet.landingSiteElevation / DISTANCE_PER_CHARACTER
	landerPos = self.lander.altitude / DISTANCE_PER_CHARACTER

	for i = 1, elevationPos do
		io.write(" ")
	end
	io.write("|")
	for i = 1, landerPos - elevationPos do
		io.write(" ")
	end
	io.write("*\n")

end


function Simulation:run()

	local burnRate = 0.0

	while (self:reachedSurface() == false) do
		
		-- print(self.lander.altitudeg)
		-- print(self.planet.landingSiteElevation)

		self:positionString()
		status, burnRate = coroutine.resume(self.strategy, self.lander, self.planet)
		-- print(burnRate)
		self:updateLander(burnRate)

		if (self:landed()) then
			print("You landed on the surface! Congratulations!\n")
			return 0
		end
	end
	
	print("Oh no! Your lander crashed in a firey ball of destruction!\n")
	return 1

end


function randomStrategy()

	while true do
		coroutine.yield(4) -- Guaranteed random by fair dice roll
	end

end


function plutoStrategy(lander, planet)

	while (true) do
		burnRate = 0
		if (lander.altitude <= (planet.landingSiteElevation + 20.0)) then
			-- burnRate = (planet.gravity / lander.thrusterStrength)
			-- burnRate = burnRate * burnRate * burnRate
			burnRate = 1.2
		end
		-- print(burnRate)
		coroutine.yield(burnRate)
	end

end


function marsStrategy(lander, planet)

	while (true) do
		burnRate = 0

		if (lander.altitude <= planet.landingSiteElevation * 20) then
			-- burnRate = (planet.gravity / lander.thrusterStrength)
			-- burnRate = burnRate * burnRate * burnRate
			burnRate = 3.5
		end

		coroutine.yield(burnRate)
	end

end

strategy = coroutine.create(plutoStrategy)


-- Uncomment below once you have your code in place to run your simulation
local pluto = Planet("Pluto", PLUTO_GRAVITY, PLUTO_HEIGHT)
local plutoLander = Lander(LANDER_INIT_VELOCITY, LANDER_INIT_ALTITUDE, LANDER_INIT_FUEL_PLUTO, LANDER_THRUSTER_STRENGTH)
local plutoSimulation = Simulation(plutoLander, pluto, strategy)
plutoSimulation:run()

strategy = coroutine.create(marsStrategy)

-- Uncomment below if you want to try for the Mars landing extra credit
local mars = Planet("Mars", MARS_GRAVITY, MARS_HEIGHT)
local marsLander = Lander(LANDER_INIT_VELOCITY, LANDER_INIT_ALTITUDE, LANDER_INIT_FUEL_MARS, LANDER_THRUSTER_STRENGTH)
marsSimulation = Simulation(marsLander, mars, strategy)
marsSimulation:run()
