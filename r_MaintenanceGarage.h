
! ---------------------------------------------------------------------------- !
!       MAINTENANCE GARAGE. 10/29/21
!
  Room    maintenanceGarage "Maintenance Garage - Deck C"
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
                  print "The thick haze churns as it flows out the open garage door, whipped up by
                  something that went crazy in the room. Through the gloom, ";
                  if (maintenanceGarageDoor.isDoorOpen) print "the set of tall doors to the aft are open";
                  else print "you see a set of tall doors to the aft";
                  ".^^A land crawler sits next to an industrial pallet, but its hull is covered in a layer
                  of acid that boils through anodized gold. The rest of the equipment fares no better. Everything
                  is melting in here.";
              }
              print "If the bridge is the brains of the ship, then the garage is its heart. Maintenance worked
              hard down here to keep things running, and it shows with a layer of grease covering everything.
              The room is full of smoke, and it flows out the open garage door. Through the gloom, ";
              if (maintenanceGarageDoor.isDoorOpen) print "the set of tall doors to the aft are open";
              else print "you see a set of tall doors to the aft";
              ".^^Over by an industrial pallet is a land crawler made of gold. Every significant piece of
              equipment has been anodized with the stuff, giving all of it a longer life span in the harsh
              space environment.";
          ],
          n_to [;
              if (alien in self) return PXF();
              self.firstTime = true;
              return forwardCompanionwayDeckC;
          ],
          s_to [;
              if (alien in self) return PXF();
              <<Enter maintenanceGarageDoor>>;
          ],
          cant_go [;
              if (alien in self) return PXF();
              if (maintenanceGarageDoor.isDoorOpen) "You can go forward or aft.";
              "You can go forward.";
          ],
          before [;
              Exit:
                  if (alien in self) return PXF();
                  self.firstTime = true;
                  PlayerTo(forwardCompanionwayDeckC, 2);
                  rtrue;
              GoIn:
                  if (alien in self) return PXF();
                  if (maintenanceGarageDoor.isDoorOpen) {
                      self.firstTime = true;
                      PlayerTo(clawChamber, 2);
                      rtrue;
                  }
              Listen:
                  if (forwardStarboardJunctionDeckC.pipesBlown) "Forward, the sound of gas venting into the air cries through the ship.";
          ],
          alienWrecked false,
          destroyedYet false,
          takenHammer false,
          roomCount true,
          firstTime true;


! 10/29/21
  RoomObj -> maintenanceGarageObj "garage"
    with  name 'garage' 'area' 'place' 'room',
          description [;
              <<Look maintenanceGarage>>;
          ],
          before [;
              Take, Remove, Turn, PushDir, Push, Pull:
                  "You can't do that to the garage.";
          ];

! 10/29/21

  Object  -> maintenanceGarageBench "bench"
    with  name 'bench' 'desk' 'work' 'surface' 'metal' 'workbench' 'lock' 'drawer',
          describe [;
              if (maintenanceGarage.alienWrecked) {
                  print "^On the fore bulkhead, there's an open door. Next to it, the bench is broken in half and covered in acid";
                  if (maintenanceGarage.takenHammer == false) print ". On the deck is a sledgehammer";
                  ".";
              }
              print "^On the fore bulkhead, there's an open door. Next to it is a ";
              if (self.isLocked) print "locked bench";
              else print "broken bench";
              if (maintenanceGarage.takenHammer == false) print ". Leaning against the door is a sledgehammer";
              ".";
          ],
          before [ iTempLoc;
              Attack:
                  if (maintenanceGarage.alienWrecked) "The alien beat you to it.";
                  if (self.isLocked == false) "You've already forced open the bench.";
                  if (sledgehammer in player)
                      "You could lay into it, that would be an excellent way to get your frustration out,
                      but you'd only dent it. You wouldn't open it.";
                  "This bench has been beaten daily. It's taken a lot more damage than you would dish out.";
              Examine:
                  player.advanceGravity = false;
                  if (maintenanceGarage.alienWrecked)
                      "The bench has been laid into - the metal snapped in half. The drawer is torn off,
                      and the whole thing is covered in acid.";
                  if (self.isLocked)
                      "Dented and bruised, the metal workbench has been beaten daily by overzealous mechanics.
                      There's a drawer here that's locked using an old fashion key. Maybe there's another way
                      to open it.";
                  "Dented and bruised, the metal workbench has been beaten daily by overzealous mechanics.
                  And you forced opened the drawer.";
              Enter:
                  if (maintenanceGarage.alienWrecked) "It's been broken in half, and you can't sit on it.";
                  "This is no time to relax. You are plunging into the sun.";
              Go:
                  "You are already here.";
              Kick:
                  if (maintenanceGarage.alienWrecked) "It's covered in acid, and you'd burn yourself if you tried that.";
                  if (self.isLocked) "That's not enough force to break it open.";
              Open:
                  if (maintenanceGarage.alienWrecked) "It's been broken in half. You could say it already open.";
                  if (self.isLocked) "It's locked. You're going to have to find a way around it.";
                  "You've already forced open the bench.";
              Push, PushDir, Turn:
                  if (maintenanceGarage.alienWrecked) "It's covered in acid, and you'd burn yourself if you tried that.";
                  "The workbench is made of metal, and it's too heavy to push around.";
              Pull:
                  if (maintenanceGarage.alienWrecked) "It's covered in acid, and you'd burn yourself if you tried that.";
                  "You can pull as hard as you like, but that's not going to open it.";
              Unlock:
                  if (maintenanceGarage.alienWrecked) "It's been broken in half. There's nothing to unlock.";
                  if (self.isLocked == false) "You've already forced open the bench.";
                  if (second == kabar)
                      "The ka-bar is a relic, and you wouldn't want to damage it. It will be worth much more unblemished.";
                  if (second == crowbar) {
                      if (crowbar in vortexBag) {
                          print "(first taking the crowbar)^";
                          move crowbar to player;
                      }
                      self.isLocked = false;
                      iMonsterDestination = MAINTNNCGRGE;
                      iTempLoc = iMonsterLoc;
                      iTempLoc++;
                      if (iTempLoc > MONSTERTOTAL) iTempLoc = 0;
                      monster_loc-->iTempLoc = MAINTNNCGRGE;
                      alien.resetLocInGarage = true;
                      move yellowFlashcard to maintenanceGarage;
                      move maintenanceGarageBench to maintenanceGarage;
                      "Putting the crowbar between the lip of the drawer, you work it back and forth, forcing
                      the tool deeper into the bench. Then when it's halfway, you push down with everything you
                      got. Immediately the drawer blows out, hitting the deck with a loud crash as a yellow flashcard
                      falls out with it. You almost drop the crowbar but manage to keep that in hand.";
                  }
                  if (second == nothing) "You need to pry the bench with something.";
                  "That's not going to fit the lock. You need to find another way to open it.";
              Blow:
                  "You can't blow through your suit. The polymer seals in your environment.";
              Attack, Burn, Climb, Close, Cut, Dig, Drink, Eat, Empty, Enter, Exit, GetOff, Go, GoIn, JumpOver, Kick, Listen, LookUnder, Open:
                  if (maintenanceGarage.alienWrecked) "It's covered in acid, and you'd burn yourself if you tried that.";
                  "That's not going to help.";
              Push, PushDir, Pull, Remove, Rub, Search, Set, SetTo, Smell, Squeeze, Swing, SwitchOn, SwitchOff, Take, Talk, Taste, Tie, Touch, Transfer, Turn, Unlock, Wave:
                  if (maintenanceGarage.alienWrecked) "It's covered in acid, and you'd burn yourself if you tried that.";
                  "That's not going to help.";
          ],
          isLocked true,
     has  supporter static;

! 12/18/21

  Object  -> maintenanceGaragePanel "panel"
    with  name 'panel' 'square' 'space',
          before [;
              Examine:
                  player.advanceGravity = false;
                  if (battery in self) "The panel is recessed into the bulkhead. Pushing on it, you see the D-Cell battery you inserted.";
                  self.firstSeen = true;
                  "The panel is recessed into the bulkhead. Pushing on it, you see a square space behind it that should hold a D-Cell battery.";
              Set, SetTo, SwitchOn:
                  if (maintenanceGarageDoor.isDoorOpen) "The door is already open.";
                  if (self.firstSeen) "It doesn't work like that. It looks like it needs a battery.";
                  "It doesn't work like that.";
              Unlock:
                  if (maintenanceGarageDoor.isDoorOpen) "The door is already open.";
                  "That's not what is locked. The door is.";
              Open:
                  if (battery in self) "The panel is already open. Pushing on it, you see the D-Cell battery you inserted.";
                  self.firstSeen = true;
                  "The panel is already open. Inside is a square space that will hold a D-Cell battery.";
              Push:
                  if (battery in self) "You push the panel and see the D-Cell battery you inserted.";
                  self.firstSeen = true;
                  "You push the panel, looking inside. It has room to hold a D-Cell battery.";
              Blow:
                  "You can't blow through your suit. The polymer seals in your environment.";
              Attack, Burn, Climb, Close, Cut, Dig, Drink, Eat, Empty, Enter, Exit, GetOff, Go, GoIn, JumpOver, Kick, Listen, LookUnder, Open:
                  "That's not going to help.";
              Push, PushDir, Pull, Remove, Rub, Set, SetTo, Smell, Squeeze, Swing, SwitchOn, SwitchOff, Take, Talk, Taste, Tie, Touch, Transfer, Turn, Unlock, Wave:
                  "That's not going to help.";
          ],
          firstSeen false,
     has  container open concealed static;

! 12/18/21

  NoHelp  -> maintenanceGarageDoor "doors"
    with  name 'doors' 'tall',
          before [;
              Attack:
                  if (self.isDoorOpen) "The doors are already open as smoke pours out of the aft chamber. You don't need to do that.";
                  if (second == sledgehammer)
                      "You could swing the hammer with all your might, attracting the alien, or you could
                      take a look at the panel next to the doors and figure out how to properly open them.";
                  "You don't need to break them open. The doors are mechanical, and you should get
                  them working. Maybe you could take a closer look at the panel next to the doors.";
              Examine:
                  player.advanceGravity = false;
                  if (self.isDoorOpen) "The doors are open as smoke pours out of the aft chamber.";
                  "The doors on the aft bulkhead look down at you, tall things that span the height of the room. Next to them, a panel is recessed into the wall.";
              Enter:
                  if (alien in maintenanceGarage) return PXF();
                  if (self.isDoorOpen) {
                      maintenanceGarage.firstTime = true;
                      PlayerTo(clawChamber, 2);
                      rtrue;
                  }
                  "The doors are closed. You need a way to power them open. Maybe you should take a closer look at the panel next to the doors.";
              Open, Pull:
                  if (self.isDoorOpen) "The doors are already open as smoke pours out of the aft chamber.";
                  "You can't pull them open. Maybe you should take a closer look at the panel next to the doors.";
              Push:
                  if (self.isDoorOpen) "The doors are already open as smoke pours out of the aft chamber.";
                  "The doors are closed and won't push open. Maybe you should take a closer look at the panel next to them.";
              Close:
                  if (self.isDoorOpen) "But you worked so hard to open them.";
                  "They're already closed.";
              Lock:
                  if (self.isDoorOpen) "The doors don't lock.";
                  "The doors don't lock. You need a way to power them open.";
              Unlock:
                  if (self.isDoorOpen) "The doors are already open as smoke pours out of the aft chamber.";
                  "That's not going to work. Maybe you should take a closer look at the panel next to the doors.";
          ],
          isDoorOpen false,
     has  pluralname;

! 01/20/22

  StObj   -> maintenanceGarageGarageDoor "door"
    with  name 'door' 'large',
          before [;
              Examine, Search:
                  player.advanceGravity = false;
                  "At the forward end of this garage sits a large door - open. But smoke fills the companionway behind it. You can't see through it.";
              Open:
                  "That's already open.";
              Enter, Go:
                  if (alien in maintenanceGarage) return PXF();
                  maintenanceGarage.firstTime = true;
                  PlayerTo(forwardCompanionwayDeckC, 2);
                  rtrue;
          ];

! 01/20/22

  StObj   -> maintenanceGaragePallet "pallet"
    with  name 'industrial' 'pallet' 'survey' 'equipment',
          before [;
              Examine, Search:
                  player.advanceGravity = false;
                  if (maintenanceGarage.alienWrecked)
                      "The pallet and the survey equipment are covered in the alien's secretions. Even though the equipment is made from anodized gold, the acid cuts straight through.";
                  "On the pallet, there's a lot of survey equipment that's been left behind. It's old. None of it's needed on a tug.";
              Take:
                  if (maintenanceGarage.alienWrecked) "It's covered in acid, and you'd burn yourself if you tried that.";
                  "None of it has any value. It's too old and not even anodized with gold.";
              Attack, Burn, Climb, Close, Cut, Dig, Drink, Eat, Empty, Enter, Exit, GetOff, Go, GoIn, JumpOver, Kick, Listen, LookUnder, Open:
                  if (maintenanceGarage.alienWrecked) "It's covered in acid, and you'd burn yourself if you tried that.";
                  return PNL();
              Push, PushDir, Pull, Remove, Rub, Search, Set, SetTo, Smell, Squeeze, Swing, SwitchOn, SwitchOff, Take, Talk, Taste, Tie, Touch, Transfer, Turn, Unlock, Wave:
                  if (maintenanceGarage.alienWrecked) "It's covered in acid, and you'd burn yourself if you tried that.";
                  return PNL();
          ];

! 01/20/22

  StObj   -> maintenanceGarageCrawler "crawler"
    with  name 'land' 'crawler' 'vehicle' 'gold' 'plating' 'anodized',
          before [;
              Examine, Search:
                  player.advanceGravity = false;
                  if (maintenanceGarage.alienWrecked)
                      "The land crawler was slammed into, then spit upon - the acid burning through the gold plating that once protected it.";
                  "The land crawler is an exploratory vehicle made from anodized gold that sits in the
                  corner of the room by the industrial pallet. It can cover several kilometers in good
                  conditions before depleting the batteries, carrying two passengers.";
              Take:
                  if (maintenanceGarage.alienWrecked) "It's covered in acid, and you'd burn yourself if you tried that.";
                  "It's too big to take. It's not going anywhere.";
              Attack, Burn, Climb, Close, Cut, Dig, Drink, Eat, Empty, Enter, Exit, GetOff, Go, GoIn, JumpOver, Kick, Listen, LookUnder, Open:
                  if (maintenanceGarage.alienWrecked) "It's covered in acid, and you'd burn yourself if you tried that.";
                  return PNL();
              Push, PushDir, Pull, Remove, Rub, Search, Set, SetTo, Smell, Squeeze, Swing, SwitchOn, SwitchOff, Take, Talk, Taste, Tie, Touch, Transfer, Turn, Unlock, Wave:
                  if (maintenanceGarage.alienWrecked) "It's covered in acid, and you'd burn yourself if you tried that.";
                  return PNL();
          ];

! 03/28/22

  StObj   -> maintenanceGarageGrease "grease"
    with  name 'grease',
          before [;
              Examine, Search:
                  player.advanceGravity = false;
                  if (maintenanceGarage.alienWrecked)
                      "There is very little grease in the room, the acid boiling it away.";
                  "Grease is all over the workbench, land crawler, pallet, and even the large aft doors.";
              Attack, Burn, Climb, Close, Cut, Dig, Drink, Eat, Empty, Enter, Exit, GetOff, Go, GoIn, JumpOver, Kick, Listen, LookUnder, Open:
                  if (maintenanceGarage.alienWrecked) "It's covered in acid, and you'd burn yourself if you tried that.";
                  return PNL();
              Push, PushDir, Pull, Remove, Rub, Search, Set, SetTo, Smell, Squeeze, Swing, SwitchOn, SwitchOff, Take, Talk, Taste, Tie, Touch, Transfer, Turn, Unlock, Wave:
                  if (maintenanceGarage.alienWrecked) "It's covered in acid, and you'd burn yourself if you tried that.";
                  return PNL();
          ];

! 11/07/21

  StObj   maintenanceGarageSmoke "smoke"
    with  name 'smoke' 'air' 'haze' 'hazy' 'thick' 'gloom' 'dark' 'cloud' 'smog' 'dense' 'heavy',
          before [;
              Examine:
                  player.advanceGravity = false;
                  if (self in clawChamber) "The smoke seems to originate from this room as plumes from above bellow out the two open doors.";
                  "The smoke down here is heavy and thick, and you're thankful you are wearing your polymer bodysuit.";
              Enter, Go:
                  "You need to tell me which direction to go in.";
          ],
          found_in maintenanceGarage clawChamber;

! 01/05/22

  AcidObj maintenanceGarageAcid "acid"
    with  name 'acid' 'pool' 'secretion' 'secretions',
          before [;
              Examine, Search:
                  player.advanceGravity = false;
                  "The acid burns everything it touches, trying to melt all the way through the deck.";
              Go:
                  "You are already here.";
          ];
