%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% game.pl  
%
% Use this as the starting point for your game.  This starter code includes
% the following:
%  - Some example areas
%  - An example of how you might connect those areas 
%  - Handling of the actions 'go _______.', 'help.', and 'quit.'
%  - Basic game loop
%  - Input processing which strips case and punctuation and puts the words into a list 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Facts %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Dynamic fact used to store the player's current location
:- dynamic currentArea/1.	

% Assert this dynamic fact to stop the game once the player has won (or lost!) 
:- dynamic gameOver/0.

% Mood levels for the main characters. These are pretty important.
:- dynamic wifeMood/1.
:- dynamic husbandMood/1.

% Various scenario switches.
:- dynamic canTalk/1.
:- dynamic husbandShower/0.
:- dynamic wifeShower/0.
:- dynamic cleanClothes/0.
:- dynamic cleanRoom/0.

% Dynamic fact used to store whether or not a player has an item.
:- dynamic have/1.
% Dynamic fact to store where an item is.
:- dynamic inside/2.

% Dynamic switches for certain items.
:- dynamic canActivate/1.
:- dynamic active/1.
:- dynamic canEat/1.
:- dynamic eatenRecently/0.
:- dynamic canUse/1.

% Here is one way you might create your areas
%% area(startArea, 'Start Area', 'You find yourself in a large empty area').
%% area(forest, 'Forest', 'You enter a dense forest, there is path heading east').
%% area(treasureRoom, 'Treasure Room', 'You look around and find yourself in a an area full of gold!').

area(tutorial, 'Master Bedroom', 'You\'re in the room you share with your husband. It\'s kind of a mess.').

area(morningBedroom, 'Master Bedroom', 'The room you share with your husband. It\'s kind of a mess.').
area(morningBedroomHusband, 'Master Bedroom', 'The room you share with your husband. He\'s sitting on the bed.').
area(morningEntryway, 'Entryway', 'Nothing much here, just the front door and a hallway leading into the house.').
area(morningKitchen, 'Kitchen', 'Your cosy kitchen. Both of you like to cook, so it\'s quite well stocked.').
area(morningLounge, 'Living Room', 'There\'s a sofa and recliner by the fireplace, and a dining table where you host guests.').
area(morningBathroom, 'Bathroom', 'The master bathroom. It\'s still humid from your husband\'s shower.').

area(work, 'OfficeCo, Inc.', 'The familiar pile of paperwork greets you. It\'ll take a while to get through this.').

area(eveningBedroom, 'Master Bedroom', 'The room you share with your husband. It\'s kind of a mess').
area(eveningBedroomClean, 'Master Bedroom', 'The room you share with your husband. It looks a lot cleaner.').
area(eveningEntryway, 'Entryway', 'You get home late, and the house is quiet.').
area(eveningKitchen, 'Kitchen', 'Your cosy kitchen. Both of you like to cook, so it\'s quite well stocked.').
area(eveningLounge, 'Living Room', 'Your husband\'s on the recliner by the fireplace.').


% You might connect your areas like this:
%% connected(north, startArea, forest).
%% connected(south, forest, startArea).
%% connected(east, forest, treasureRoom).
%% connected(west, treasureRoom, forest).

connected(bathroom, morningBedroom, morningBathroom).
connected(bedroom, morningBathroom, morningBedroom).

connected(hallway, morningBedroom, morningEntryway).
connected(bedroom, morningEntryway, morningBedroom).

connected(bathroom, morningBedroomHusband, morningBathroom).
connected(bedroom, morningBathroom, morningBedroomHusband).

connected(hallway, morningBedroomHusband, morningEntryway).
connected(bedroom, morningEntryway, morningBedroomHusband).

connected(kitchen, morningEntryway, morningKitchen).
connected(hallway, morningKitchen, morningEntryway).

connected(lounge, morningKitchen, morningLounge).
connected(kitchen, morningLounge, morningKitchen).

connected(work, morningEntryway, work).
connected(home, work, eveningEntryway).

connected(bathroom, eveningBedroom, eveningBathroom).
connected(bedroom, eveningBathroom, eveningBedroom).

connected(hallway, eveningBedroom, eveningEntryway).
connected(bedroom, eveningEntryway, eveningBedroom).

connected(bathroom, eveningBedroomClean, eveningBathroom).
connected(bedroom, eveningBathroom, eveningBedroomClean).

connected(hallway, eveningBedroomClean, eveningEntryway).
connected(bedroom, eveningEntryway, eveningBedroomClean).

connected(kitchen, eveningEntryway, eveningKitchen).
connected(hallway, eveningKitchen, eveningEntryway).

connected(lounge, eveningKitchen, eveningLounge).
connected(kitchen, eveningLounge, eveningKitchen).


%% % Objects, defined as follows

%% isContainer(bag).

%% inHallway(keys).

%% inHallway(documents).

%% inWork().



%%%%%%%%%%%%%%%%%%%%%%%%%%%% Input Processing %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Handling of the action 'go _______.', and a good example of how you might implement others
processInput([go, 'bathroom']) :-
    % Preconditions
    currentArea(Current),
    connected('bathroom', Current, _),
    husbandShower,

    % Effects
    print('The door is locked. You can hear your husband taking a shower.'), nl, nl.

processInput([go, 'bedroom']) :-
    % Preconditions
    \+ husbandShower,
    currentArea(Current),
    connected('bedroom', Current, morningBedroom),

    % Effects
    assert(canTalk(husband)),
    changeArea('morningBedroomHusband').

processInput([go, Direction]) :-
    % Preconditions
    currentArea('morningBedroomHusband'),
    connected(Direction, 'morningBedroomHusband', NewRoom),

    % Effects
    retract(canTalk(husband)),
    changeArea(NewRoom).

processInput([go, 'lounge']) :-
    % Preconditions
    currentArea(Current),
    connected('lounge', Current, eveningLounge),

    % Effects
    assert(canTalk(husband)),
    changeArea('eveningLounge').

processInput([go, Direction]) :-
    % Preconditions
    currentArea('eveningLounge'),
    connected(Direction, 'eveningLounge', NewRoom),

    % Effects
    retract(canTalk(husband)),
    changeArea(NewRoom).

processInput([go, 'bedroom']) :-
    % Preconditions
    cleanRoom,
    currentArea(Current),
    connected('bedroom', Current, eveningBedroomClean),

    % Effects
    changeArea('eveningBedroomClean').

processInput([go, 'work']) :-
    % Preconditions
    currentArea('morningEntryway'),
    \+ have(bag),
    \+ have(documents),
    \+ have(laptop),
    \+ have(keys),

    % Effects
    print('You need your bag, keys, documents, and laptop before you can leave.'), nl, nl.

processInput([go, 'work']) :-
    retractall(eatenRecently),
    assert(canTalk('coworker')),
    husbandImprove(2),
    currentArea(Current),
    connected('work', Current, NewRoom),
    changeArea(NewRoom).

processInput([go, 'home']) :-
    retractall(eatenRecently),
    retract(canTalk('coworker')),
    wifeImprove(1),
    husbandImprove(1),
    currentArea(Current),
    connected('home', Current, NewRoom),
    changeArea(NewRoom).

processInput([go, Direction]) :-
    currentArea(Current),
    connected(Direction, Current, NewRoom),
    changeArea(NewRoom).

processInput([go, _]) :-
    print('You can\'t go that way'), nl, nl.


% Grab an item from the current room.
processInput([grab, 'food']) :-
    % Preconditions
    currentArea(Current),
    inside('food', Current),         

    % Effects
    assert(have('food')),
    print('You pick up some food.'), nl, nl.

processInput([grab, Item]) :-
    % Preconditions
    \+ have(Item),
    currentArea(Current),
    inside(Item, Current),         

    % Effects
    assert(have(Item)),
    retract(inside(Item, Current)),
    print('You pick it up.'), nl, nl.

processInput([grab, _]) :-
    print('You can\'t pick that up.'), nl, nl.


% Drop an item into the current room.
processInput([drop, Item]) :-
    % Preconditions
    have(Item),

    % Effects
    currentArea(Current),
    assert(inside(Item, Current)),
    retract(have(Item)),

    print('You drop the item.'), nl, nl.

processInput([drop, _]) :-
    print('You can\'t drop that there!'), nl, nl.

% Turn items on or off.
processInput([use, 'clothes']) :-
    % Preconditions
    have('clothes'),
    currentArea('morningBathroom'),

    % Effects
    retract(have(clothes)),
    wifeMood(X),
    FX is X + 1,
    retractall(wifeMood(_)),
    assert(wifeMood(FX)),
    print('You quickly change into the clean clothes.'), nl, nl.

processInput([use, 'clothes']) :-
    % Preconditions
    have('clothes'),
    currentArea('morningBedroom'),

    % Effects
    retract(have(clothes)),
    wifeMood(X),
    FX is X + 1,
    retractall(wifeMood(_)),
    assert(wifeMood(FX)),
    print('You quickly change into the clean clothes.'), nl, nl.

processInput([use, 'clothes']) :-
    % Preconditions
    have('clothes'),
    currentArea('morningBedroomHusband'),

    % Effects
    retract(have(clothes)),
    wifeImprove(1),
    print('You quickly change into the clean clothes.'), nl, nl.

processInput([use, 'food']) :-
    % Preconditions
    have('food'),
    \+ eatenRecently,
    husbandShower,

    % Effects
    retract(have('food')),
    assert(eatenRecently),
    retract(husbandShower),
    checkBag,
    checkClothes,
    wifeImprove(1),
    print('You eat the food. It tastes pretty good, and you feel a little better.'), nl, nl.

processInput([use, 'food']) :-
    % Preconditions
    have('food'),
    \+ husbandShower,
    \+ eatenRecently,

    % Effects
    retract(have('food')),
    assert(eatenRecently),
    wifeImprove(1),
    print('You eat the food. It tastes pretty good, and you feel a little better.'), nl, nl.

processInput([use, Item]) :-
    % Preconditions
    currentArea('tutorial'),
    have(Item),
    canActivate(Item),
    active(Item),

    % Effects
    changeArea(morningBedroom),
    printIntro2.

processInput([use, Item]) :-
    % Preconditions
    have(Item),
    canActivate(Item),
    active(Item),

    % Effects
    retract(active(Item)),
    print('You turn off the device.'), nl, nl.

processInput([use, Item]) :-
    % Preconditions
    have(Item),
    canActivate(Item),
    \+ active(Item),

    % Effects
    assert(active(Item)),
    print('You turn on the device.'), nl, nl.

processInput([use, _]) :-
    print('You can\'t use that.'), nl, nl.

% Print out a list of the items you currently have.
processInput([inventory]) :-
    findall(X, have(X), ListStuff),
    print(ListStuff), nl, nl.

processInput([inventory]) :-
    print('You don\'t have anything on you.'), nl, nl.


% Print a list of all the exits from the current room.
processInput([exits]) :-
    % Effects
    currentArea(Current),
    findall(X, connected(X, Current, _), ListExits),
    print(ListExits), nl, nl.

processInput([items]) :-
    % Effects
    currentArea(Current),
    findall(X, inside(X, Current), ListStuff),
    print(ListStuff), nl, nl.

% Give a rough estimate of how the wife is feeling.
processInput([feelings]) :-
    % Preconditions
    wifeMood(X),
    X < 4,

    % Effects
    print('You feel miserable and angry. Life sucks.'), nl, nl.

processInput([feelings]) :-
    % Preconditions
    wifeMood(X),
    X < 7,

    % Effects
    print('You feel grumpy, and you wish someone cared. But they don\'t.'), nl, nl.

processInput([feelings]) :-
    % Preconditions
    wifeMood(X),
    X < 10,

    % Effects
    print('You feel fine. Emphasis on the \".\".'), nl, nl.

processInput([feelings]) :-
    % Preconditions
    wifeMood(X),
    X >= 10,

    % Effects
    print('Things aren\'t that bad, actually. You feel pretty good.'), nl, nl.


% Talk to someone, probably your husband.
processInput([talk, 'husband']) :-
    % Preconditions
    \+ canTalk('husband'),

    % Effects
    print('He can\'t hear you.'), nl, nl.

processInput([talk, 'husband']) :-
    % Preconditions
    wifeMood(X),
    husbandMood(Y),
    X < 3,
    Y < 3,

    % Effects
    FX is X - 1,
    FY is Y - 1,
    retractall(wifeMood(_)),
    retractall(husbandMood(_)),
    assert(wifeMood(FX)),
    assert(husbandMood(FY)),
    print('You talk to your idiot husband. It does not go well. He can die in a hole.'), nl, nl.

processInput([talk, 'husband']) :-
    % Preconditions
    wifeMood(X),
    husbandMood(Y),
    X < 4,
    Y < 4,

    % Effects
    FX is X - 1,
    FY is Y - 1,
    retractall(wifeMood(_)),
    retractall(husbandMood(_)),
    assert(wifeMood(FX)),
    assert(husbandMood(FY)),
    print('You talk to your idiot husband. It does not go well.'), nl, nl.

processInput([talk, 'husband']) :-
    % Preconditions
    wifeMood(X),
    husbandMood(Y),
    X < 7,
    Y < 4,

    % Effects
    FY is Y - 1,
    retractall(husbandMood(_)),
    assert(husbandMood(FY)),
    print('You try to talk to your husband, but he just ignores you. He\'s pretty surly.'), nl, nl.

processInput([talk, 'husband']) :-
    % Preconditions
    wifeMood(X),
    husbandMood(Y),
    X < 4,
    Y < 7,

    % Effects
    FX is X - 1,
    retractall(wifeMood(_)),
    assert(wifeMood(FX)),
    print('You talk to your husband. Doesn\'t he know how to shut up and listen to you?'), nl, nl.

processInput([talk, 'husband']) :-
    % Preconditions
    wifeMood(X),
    husbandMood(Y),
    X < 7,
    Y < 7,

    % Effects
    print('You talk to your husband, but he doesn\'t really listen.'), nl, nl.

processInput([talk, 'husband']) :-
    % Preconditions
    wifeMood(X),
    husbandMood(Y),
    X < 10,
    Y < 4,

    % Effects
    FX is Y,
    FY is Y + 1,
    retractall(wifeMood(_)),
    retractall(husbandMood(_)),
    assert(wifeMood(FX)),
    assert(husbandMood(FY)),
    print('You talk to your husband. Things get ugly. He calls you a fat shapeless pig.'), nl, nl.

processInput([talk, 'husband']) :-
    % Preconditions
    wifeMood(X),
    husbandMood(Y),
    X < 4,
    Y < 10,

    % Effects
    FY is X,
    FX is X + 1,
    retractall(wifeMood(_)),
    retractall(husbandMood(_)),
    assert(wifeMood(FX)),
    assert(husbandMood(FY)),
    print('Your husband tries to talk to you, but you remind him that he\'s a worthless slob. It feels good.'), nl, nl.

processInput([talk, 'husband']) :-
    % Preconditions
    wifeMood(X),
    husbandMood(Y),
    X < 10,
    Y < 7,

    % Effects
    FX is X - 1,
    FY is Y + 1,
    retractall(wifeMood(_)),
    retractall(husbandMood(_)),
    assert(wifeMood(FX)),
    assert(husbandMood(FY)),
    print('You and your husband say a few words to each other, but don\'t really say anything important.'), nl, nl.

processInput([talk, 'husband']) :-
    % Preconditions
    wifeMood(X),
    husbandMood(Y),
    X < 7,
    Y < 10,

    % Effects
    FX is X + 1,
    FY is Y - 1,
    retractall(wifeMood(_)),
    retractall(husbandMood(_)),
    assert(wifeMood(FX)),
    assert(husbandMood(FY)),
    print('You and your husband say a few words to each other, but don\'t really say anything important.'), nl, nl.

processInput([talk, 'husband']) :-
    % Preconditions
    wifeMood(X),
    husbandMood(Y),
    X < 10,
    Y < 10,

    % Effects
    FX is X,
    FY is Y,
    retractall(wifeMood(_)),
    retractall(husbandMood(_)),
    assert(wifeMood(FX)),
    assert(husbandMood(FY)),
    print('The two of you talk for a little while.'), nl, nl.

processInput([talk, 'husband']) :-
    % Preconditions
    wifeMood(X),
    husbandMood(Y),
    X >= 10,
    Y < 4,

    % Effects
    FX is X - 3,
    FY is Y + 1,
    retractall(wifeMood(_)),
    retractall(husbandMood(_)),
    assert(wifeMood(FX)),
    assert(husbandMood(FY)),
    print('You apologize to your husband, but he just tells you to shut up and storms off.'), nl, nl.

processInput([talk, 'husband']) :-
    % Preconditions
    wifeMood(X),
    husbandMood(Y),
    X >= 10,
    Y < 7,

    % Effects
    FX is X - 1,
    FY is Y + 1,
    retractall(wifeMood(_)),
    retractall(husbandMood(_)),
    assert(wifeMood(FX)),
    assert(husbandMood(FY)),
    print('You apologize to your husband, but he just grunts in response.'), nl, nl.

processInput([talk, 'husband']) :-
    % Preconditions
    wifeMood(X),
    husbandMood(Y),
    X >= 10,
    Y < 10,

    % Effects
    FX is X,
    FY is Y + 1,
    retractall(wifeMood(_)),
    retractall(husbandMood(_)),
    assert(wifeMood(FX)),
    assert(husbandMood(FY)),
    print('You apologize to your husband. He takes it well, but still seems frustrated.'), nl, nl.

processInput([talk, 'husband']) :-
    % Preconditions
    wifeMood(X),
    husbandMood(Y),
    X < 4,
    Y >= 10,

    % Effects
    FX is X + 1,
    FY is Y - 3,
    retractall(wifeMood(_)),
    retractall(husbandMood(_)),
    assert(wifeMood(FX)),
    assert(husbandMood(FY)),
    print('Your husband apologizes, like the grovelling sow he is. You tell him to get lost.'), nl, nl.

processInput([talk, 'husband']) :-
    % Preconditions
    wifeMood(X),
    husbandMood(Y),
    X < 7,
    Y >= 10,

    % Effects
    FX is X + 1,
    FY is Y - 1,
    retractall(wifeMood(_)),
    retractall(husbandMood(_)),
    assert(wifeMood(FX)),
    assert(husbandMood(FY)),
    print('Your husband says something, but you weren\'t paying attention.'), nl, nl.

processInput([talk, 'husband']) :-
    % Preconditions
    wifeMood(X),
    husbandMood(Y),
    X < 10,
    Y >= 10,

    % Effects
    FX is X + 1,
    FY is Y,
    retractall(wifeMood(_)),
    retractall(husbandMood(_)),
    assert(wifeMood(FX)),
    assert(husbandMood(FY)),
    print('Your husband apologizes. It\'s almost enough to make you forgive him.'), nl, nl.

processInput([talk, 'husband']) :-
    % Preconditions
    wifeMood(X),
    husbandMood(Y),
    X >= 10,
    Y >= 10,

    % Effects
    FX is 10,
    FY is 10,
    retractall(wifeMood(_)),
    retractall(husbandMood(_)),
    assert(wifeMood(FX)),
    assert(husbandMood(FY)),
    print('The two of you talk for a while, and you both feel better afterward.'), nl, nl.

processInput([talk, 'husband']) :-
    % Preconditions
    wifeMood(X),
    husbandMood(Y),

    % Effects
    FX is Y,
    FY is X,
    retractall(wifeMood(_)),
    retractall(husbandMood(_)),
    assert(wifeMood(FX)),
    assert(husbandMood(FY)),
    print('You talk to your husband. It\'s hard to say how it went.'), nl, nl.

processInput([talk, 'coworker']) :-
    % Preconditions
    \+ canTalk('coworker'),

    % Effects
    print('He can\'t hear you.'), nl, nl.

processInput([talk, 'coworker']) :-
    % Preconditions
    wifeMood(X),
    X > 5,

    % Effects
    wifeImprove(-1),
    print('You talk to a coworker about your problems. He tries to hit on you.'), nl, nl.

processInput([talk, 'coworker']) :-
    % Preconditions
    wifeMood(X),
    X > 1,

    % Effects
    wifeImprove(2),
    print('You talk to a coworker about your problems. He makes you laugh.'), nl, nl.

processInput([talk, 'coworker']) :-
    print('You try to talk to your coworkers, but can\'t muster the effort.'), nl, nl.

processInput([talk, _]) :-
    print('Talk all you want, it doesn\'t respond.'), nl, nl.

% Various hidden commands.
processInput([shower]) :-
    % Preconditions
    currentArea('morningBathroom'),
    \+ wifeShower,
    \+ have(clothes),

    % Effects
    wifeMood(X),
    FX is X + 1,
    retractall(wifeMood(_)),
    assert(wifeMood(FX)),
    assert(wifeShower),
    print('You take a quick shower, then put on the clothes you were wearing. It\'s not like anyone will notice.'), nl, nl.

processInput([shower]) :-
    % Preconditions
    currentArea('morningBathroom'),
    \+ wifeShower,

    % Effects
    wifeMood(X),
    FX is X + 2,
    retractall(wifeMood(_)),
    assert(wifeMood(FX)),
    assert(wifeShower),
    retract(have(clothes)),
    print('You take a nice shower, then put on the clean clothes.'), nl, nl.

processInput([clean]) :-
    % Preconditions
    currentArea('morningBedroom'),

    % Effects
    print('You don\'t have time to clean, you have to go to work.'), nl, nl.

processInput([clean]) :-
    % Preconditions
    currentArea('morningBedroomHusband'),

    % Effects
    print('You don\'t have time to clean, you have to go to work.'), nl, nl.

processInput([clean]) :-
    % Preconditions
    currentArea('eveningBedroom'),

    % Effects
    wifeImprove(1),
    husbandImprove(2),
    changeArea(eveningBedroomClean),
    print('You clean up the bedroom.'), nl, nl.

% Go to bed at night and end the game.
processInput([sleep]) :-
    % Preconditions
    currentArea('eveningBedroom'),

    % Effects
    finalSequence,
    assert(gameOver).
    %% getInput([quit]).

processInput([sleep]) :-
    % Preconditions
    currentArea('eveningBedroomClean'),

    % Effects
    finalSequence,
    assert(gameOver).
    %% getInput([quit]).

processInput([sleep]) :-
    % Preconditions
    currentArea('eveningBedroom'),
    print('Thanks for playing!'),
    assert(gameOver).

% Add some help output here to explain how to play your game
processInput([help]) :- 
    print('go _ : Go to the specified place. See exits.'), nl,
    print('grab _ : Pick up the specified item.'), nl,
    print('drop _ : Drops the specified item in the current room.'), nl,
    print('use _ : Use the specified item.'), nl,
    print('inventory : Show a list of all the items you are carrying.'), nl,
    print('exits : Show a list of all the exits to the current place.'), nl,
    print('items : Show a list of all the items in the current place.'), nl,
    print('feelings : Think about how you feel at the moment.'), nl,
    print('talk _ : Talk to someone. This can help, if you feel up to it.'), nl,
    print('sleep : After a long day at work, you can sleep in the bedroom. This will end the game.'), nl,
    print('help : Show this list.'), nl,
    print('quit : Quit the game.'), nl, nl.


% Catch-all for unknown inputs - make sure all of your processInput rules are above this one!
processInput(_) :-
    print('I don\'t know how to do that...try something else'), nl, nl.

%%%%%%%%%%%%%%%%%%%%%%%%%%%% Basic Gameplay %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% This rule starts everything off
play :-
    retractall(gameOver),
	retractall(currentArea(_)),
    assertz(currentArea(tutorial)),
    setupObjects,
    printIntro,
	dispPrompt,
    getInput.
	
% Setup Object Locations
setupObjects :-

    % Setup the character moods.
    retractall(wifeMood(_)),
    retractall(husbandMood(_)),
    assert(wifeMood(3)),
    assert(husbandMood(4)),

    assert(husbandShower),
    retractall(cleanClothes),
    retractall(cleanRoom),

    retractall(canTalk('husband')),
    retractall(canTalk('coworker')),

    % Remove any leftover items.
    retractall(inside(bag, _)),
    retractall(inside(alarm, _)),
    retractall(inside(clothes, _)),
    retractall(inside(food, _)),    
    retractall(inside(laptop, _)),
    retractall(inside(keys, _)),
    retractall(inside(documents, _)),

    retractall(have(bag)),
    retractall(have(alarm)),
    retractall(have(clothes)),
    retractall(have(food)),    
    retractall(have(laptop)),
    retractall(have(keys)),
    retractall(have(documents)),

    % Assign items to their proper locations.
    assert(inside(bag, morningBedroom)),
    assert(inside(alarm, tutorial)),
    assert(inside(clothes, morningBedroom)),
    assert(inside(food, morningKitchen)),    
    assert(inside(food, eveningKitchen)),    
    assert(inside(laptop, morningLounge)),
    assert(inside(keys, morningEntryway)),
    assert(inside(documents, morningEntryway)),

    % Setup the item properties.
    retractall(eatenRecently),
    assert(canEat(food)),

    assert(canActivate(alarm)),
    assert(active(alarm)).

checkBag :-
    % Preconditions
    inside(bag, morningBedroom),

    % Effects
    assert(inside(bag, morningBedroomHusband)).

checkBag.

checkClothes :-
    inside(clothes, morningBedroom),
    assert(inside(clothes, morningBedroomHusband)).

checkClothes.

% Improve moods by V.
husbandImprove(V) :-
    husbandMood(X),
    FX is X + V,
    retractall(husbandMood(_)),
    assert(husbandMood(FX)).

wifeImprove(V) :-
    wifeMood(X),
    FX is X + V,
    retractall(wifeMood(_)),
    assert(wifeMood(FX)).

% Print out the introduction to the game
printIntro :-
    print('~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~'), nl,
    print('Your alarm goes off. Your head hurts. Were you drinking last night? Probably.'), nl,
    print('It\'s your husband\'s fault anyway, always nagging you about your health.'), nl,
    print('Whatever. First you need to turn off that stupid alarm.'), nl,
    nl,
    print('[You get out of bed. To turn off the alarm you\'ll need to pick it up with \'grab alarm\' and then'), nl,
    print(' turn it off with \'use alarm\'.]'), nl.

% Print out the next intro block
printIntro2 :-
    print('Stupid alarm. You\'ll probably be late for work anyway. Speaking of which, you need to get ready.'), nl,
    print('You\'ll need to gather your bag, documents, laptop, and keys before you leave. You may also want'), nl,
    print('to pack a lunch and shower before you go. Maybe it will make you feel better.'), nl,
    nl,
    print('[Feel free to move about the house. You can use \'help\' to show a list of commands.]'), nl.

finalSequence :-
    % Preconditions
    wifeMood(X),
    husbandMood(Y),
    X < 5,
    Y < 5,

    % Effects
    print('You crumple into bed and cry yourself to sleep. Again.'), nl, nl,
    print('~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~'), nl,
    print('Thanks for playing! It looks like you didn\'t do so well this time, but that\'s okay. Try eating'), nl,
    print('three square meals a day next time!'), nl, nl.

finalSequence :-
    % Preconditions
    wifeMood(X),
    husbandMood(Y),
    X < 10,
    Y < 5,

    % Effects
    print('You sit in bed for a while, wondering what went wrong in your life. At least today is over.'), nl, nl,
    print('~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~'), nl,
    print('Thanks for playing! You made a good effort, but things could still have gone better. A good shower'), nl,
    print('and clean clothes in the morning do wonders for your mood.'), nl, nl.

finalSequence :-
    % Preconditions
    wifeMood(X),
    husbandMood(Y),
    X < 5,
    Y < 10,

    % Effects
    print('Sleep comes immediately after such an exhausting day.'), nl, nl,
    print('~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~'), nl,
    print('Thanks for playing! You made a good effort, but things could still have gone better. Cleaning the'), nl, 
    print('house can be a good way to improve relations between the two of you. It feels good too.'), nl, nl.

finalSequence :-
    % Preconditions
    wifeMood(X),
    husbandMood(Y),
    X >= 10,
    Y >= 10,

    print('You and your husband go to bed early, happy to have one another\'s company once more.'), nl,
    print('~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~'), nl,
    print('Thanks for playing! It looks like you did quite well for yourself, and got the best ending. Congrats!'), nl, nl.


% Prints out the players current location description
printLocation :-
    currentArea(Current),
    area(Current, _, Description), write(Description), nl, nl. 

% Changes the players current location, validity of change is checked in processInput
changeArea(NewArea) :-
    currentArea(Current),
    retract(currentArea(Current)),
    assertz(currentArea(NewArea)).

%%%%%%%%%%%%%%%%%%%%%%%%%%%% Input Handling %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%	
:- use_module(library(readln)).

% Displays the player prompt so they can enter actions
dispPrompt :- prompt(_, '> ').

% Get input from the user
getInput :- readSentence(Input), getInput(Input).
getInput([quit]).
getInput(Input) :-
    processInput(Input), 
	printLocation,
    readSentence(Input1), 
	getInput(Input1).
	
% Reads a sentence from the prompt (unless game has ended)
readSentence(_) :-
	gameOver.	
readSentence(Input) :-
    readln(Input1, _, ".!?", "_0123456789", lowercase),
    stripPunctuation(Input1, Input).

% Strips punctuation out of the user input
stripPunctuation([], []).
stripPunctuation([Word|Tail], [Word|Result]) :-
    \+(member(Word, ['.', ',', '?', '!'])),
    stripPunctuation(Tail, Result).
stripPunctuation([_|Tail], Result) :-
    stripPunctuation(Tail, Result).
