
! ---------------------------------------------------------------------------- !
!       CAPTAINS QUARTERS. 11/02/21
!
  Room    captainsQuarters "Captain's Quarters - Deck A"
   with   description [;
              if (self.roomCount) {
                  self.roomCount = false;
                  iRoom++;
              }
              if (self.firstTime) {
                  self.firstTime = false;
              } else {
                  player.advanceGravity = false;
              }
              player.inCorridor = false;
              if (self.alienWrecked) {
                  "With the hatch ripped off, smoke has filled a room that's been reserved
                  for the ship's commander. But the bed's overturned, along with the desk that's
                  been smashed in half. All of it is now covered in acid.^^The only way out of
                  this room is through the mangled hatch to port.";
              }
              "With the hatch ripped off, smoke has filled a room that's been reserved for
              the ship's commander. There's a bed along the aft bulkhead with a few pictures on the
              wall. A desk sits across from it, missing a chair.^^The only way out of this room
              is through the mangled hatch to port.";
          ],
          w_to [;
              if (alien in self) return PXF();
              self.firstTime = true;
              return galley;
          ],
          cant_go [;
              if (alien in self) return PXF();
              "You can exit port.";
          ],
          before [;
              Exit:
                  if (alien in self) return PXF();
                  self.firstTime = true;
                  PlayerTo(galley, 2);
                  rtrue;
              Listen:

              SitRoom:
                  <<Enter captainsQuartersBed>>;
          ],
          alienWrecked false,
          destroyedYet false,
          takenRedCard false,
          takenKaBar false,
          roomCount true,
          firstTime true;

! 11/02/21

  RoomObj -> captainsQuartersObj "quarters"
    with  name 'quarters' 'area' 'place' 'room' 'section',
          description [;
              <<Look captainsQuarters>>;
          ],
          before [;
              Take, Remove, Turn, PushDir, Push, Pull:
                  "You can't do that to the quarters.";
          ];

! 11/02/21

  StObj   -> captainsQuartersBulkhead "bulkhead"
    with  name 'bulkhead' 'wall' 'picture' 'pictures',
          before [;
              Examine:
                  player.advanceGravity = false;
                  "The bulkhead has a few pictures on it, mostly of naked women.";
              Go:
                  "You are already here.";
          ];

! 11/02/21

  StObj   -> captainsQuartersPictures "women"
    with  name 'naked' 'women',
          before [;
              Attack:
                  "You could tear them off the wall, but you're here to loot the ship.";
              Examine:
                  player.advanceGravity = false;
                  "You take a closer look. Yep. They're naked.";
              Go:
                  "You are already here.";
              Take:
                  "They're old, brittle, and not worth anything.";
          ],
     has  pluralname;

! 11/15/21

  NoHelp  -> captainsQuartersDesk "desk"
    with  name 'bench' 'desk' 'lock' 'drawer',
          before [;
              Attack:
                  if (captainsQuarters.alienWrecked) "The alien beat you to it.";
                  if (self.isLocked == false) "You've already forced open the desk.";
                  if (sledgehammer in player) "With the sledgehammer? That would destroy it and everything inside.";
                  "The desk is sturdier than that.";
              Examine:
                  player.advanceGravity = false;
                  if (captainsQuarters.alienWrecked)
                      "The desk has been broken in half. It looks like a large anvil slammed into the middle,
                      breaking it in two. Then topped the whole thing with a layer of acid that burns its way
                      through the wood.";
                  if (self.isLocked)
                      "A work desk sits against the bulkhead. Looking it over closer, you see it has only one drawer.";
                  "A work desk sits against the bulkhead, but you broke open the drawer that now lies on the floor.";
              Go:
                  "You are already here.";
              Kick:
                  if (captainsQuarters.alienWrecked) "You don't need to do more damage to it.";
                  if (self.isLocked) "That's not enough force to break it open.";
              Open:
                  if (captainsQuarters.alienWrecked) "There's nothing to open. It's been broken in half, and it's covered in acid.";
                  if (self.isLocked) "It's locked using an old fashion key. You're going to have to find a way around it.";
                  "You already forced it open.";
              Push, PushDir, Turn:
                  if (captainsQuarters.alienWrecked) "The desk is covered in acid, and you'd burn yourself.";
                  "You don't need to push the desk around. That's not going to help.";
              Pull:
                  if (captainsQuarters.alienWrecked) "The desk is covered in acid, and you'd burn yourself.";
                  "You can pull as hard as you like, but it's not going to open.";
              Unlock:
                  if (captainsQuarters.alienWrecked) "It's been broken in half. There's nothing to unlock, and it's covered in acid.";
                  if (self.isLocked == false) "You've already forced open the desk.";
                  if (second == kabar) {
                      if (kabar in vortexBag)
                          "The ka-bar is a relic, and you wouldn't want to damage it. It will be worth much more unblemished.";
                      move kabar to vortexBag;
                      print "The ka-bar is a relic, and you wouldn't want to damage it. So you put it in the vortex bag.^";
                      return ItemFirstTaken();
                  }
                  if (second == crowbar) {
                      if (crowbar in vortexBag) {
                          print "(first taking the crowbar)^";
                          move crowbar to player;
                      }
                      self.isLocked = false;
                      iMonsterDestination = CAPTQRTRS;
                      move redFlashcard to captainsQuarters;
                      "You cram the crowbar as deep as you can into the lip of the drawer. It pops off with a thud
                      that rings throughout the ship. An orange flashcard bounces out.";
                  }
                  if (second == nothing) "You need to pry the desk with something.";
                  "That's not going to fit the lock. You need to find another way to open it.";
              Take:
                  if (captainsQuarters.alienWrecked) "The desk is covered in acid, and you'd burn yourself.";
                  "Even though it's big and bulky and would fit into your bag, it's worthless.";
              Attack, Burn, Climb, Close, Cut, Dig, Drink, Eat, Empty, Enter, Exit, GetOff, Go, GoIn, JumpOver, Kick, Listen, LookUnder, Open:
                  if (captainsQuarters.alienWrecked) "The desk is covered in acid, and you'd burn yourself.";
                  "You need to loot the ship, not mess with ", (the) self, ".";
              Push, PushDir, Pull, Remove, Rub, Search, Set, SetTo, Smell, Squeeze, Swing, SwitchOn, SwitchOff, Take, Talk, Taste, Tie, Touch, Transfer, Turn, Unlock, Wave:
                  if (captainsQuarters.alienWrecked) "The desk is covered in acid, and you'd burn yourself.";
                  "You need to loot the ship, not mess with ", (the) self, ".";
          ],
          isLocked true,
     has  supporter;

! 01/10/22

  Object  -> captainsQuartersBed "bed"
    with  name 'bed' 'rack',
          before [;
              Examine:
                  player.advanceGravity = false;
                  if (captainsQuarters.alienWrecked)
                      "The overturned rack has a mattress pinned under the metal. But the pile
                      slowly melts away since it's covered with acid.";
                  "This room is small, and the rack is only big enough for one person. You'd
                  expect it to be neatly made, but it's in shambles.";
              Go:
                  "You are already here.";
              Take:
                  if (captainsQuarters.alienWrecked) "Covered in acid, you'd burn yourself if you tried.";
                  "The bed is bulky and not worth anything.";
              Blow:
                  "You can't blow through your suit. The polymer seals in your environment.";
              LookUnder:
                  if (alien in captainsQuarters) "But a large alien towers over the bed, his mouth open, with rows of teeth that form a smile.";
                  if (captainsQuarters.alienWrecked) "You can't look under the rack. It's overturned and covered in acid.";
                  "You look under the rack, but the captain didn't stash anything here.";
              Enter:
                  if (alien in captainsQuarters) "This is no time to relax. You are about to be eaten.";
                  if (captainsQuarters.alienWrecked) "Covered in acid, you'd burn yourself if you tried.";
                  "This is no time to relax. You are plunging into the sun.";
              Attack, Burn, Climb, Close, Cut, Dig, Drink, Eat, Empty, Enter, Exit, GetOff, Go, GoIn, JumpOver, Kick, Listen, LookUnder, Open:
                  if (captainsQuarters.alienWrecked) "Covered in acid, you'd burn yourself if you tried.";
                  "You need to loot the ship, not mess with ", (the) self, ".";
              Push, PushDir, Pull, Remove, Rub, Search, Set, SetTo, Smell, Squeeze, Swing, SwitchOn, SwitchOff, Take, Talk, Taste, Tie, Touch, Transfer, Turn, Unlock, Wave:
                  if (captainsQuarters.alienWrecked) "Covered in acid, you'd burn yourself if you tried.";
                  "You need to loot the ship, not mess with ", (the) self, ".";
          ],
     has  concealed static;

! 01/10/22

  StObj   -> captainsQuartersHatch "hatch"
    with  name 'hatch' 'door' 'hinge' 'metal' 'mangled' 'hinges',
          before [;
              Examine:
                  player.advanceGravity = false;
                  "Something broke open the hatch, tearing it off metal hinges. Now smoke freely enters the room.";
              Enter:
                  if (alien in captainsQuarters) return PXF();
                  captainsQuarters.firstTime = true;
                  PlayerTo(galley, 2);
                  rtrue;
              Go:
                  "You are already here.";
              Take:
                  "The hatch has been ripped apart. There's not much to take, and it's worthless.";
          ];

! 01/05/22

  AcidObj captainsQuartersAcid "acid"
    with  name 'acid' 'pool' 'secretion' 'secretions' 'yellow',
          before [;
              Examine, Search:
                  player.advanceGravity = false;
                  "The acid burns everything it touches, trying to melt all the way through the floor.";
              Go:
                  "You are already here.";
          ];

! 01/05/22

  StObj   captainsQuartersWood "wood pieces"
    with  name 'wood' 'pieces',
          before [;
              Examine, Search:
                  player.advanceGravity = false;
                  "Since the desk has been broken in half, wood pieces are scattered throughout the room.";
              Go:
                  "You are already here.";
              Rub, Push, PushDir, Take, Pull, Remove, Turn:
                  "They're worthless.";
          ],
     has  static concealed pluralname;
