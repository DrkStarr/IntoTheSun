
! ---------------------------------------------------------------------------- !
!       FOOD LOCKER CORRIDOR DECK B. 10/26/21
!
  Room    foodLockerCorridorDeckB "Starboard-Side Passageway - Deck B"
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
              player.inCorridor = true;
              if (foodStorage.alienWrecked) {
                  "With long rows of amber lights that try to shine through the smog, there's a storage locker
                  at the end of this corridor that houses all the extra meals the crew would need when not
                  in hypersleep. Along the aft bulkhead, a sensor relay sits in the center of this hallway.^
                  ^You can see the door to the locker is gone. Something beat its way out.^^A tunnel runs
                  towards the forward part of the ship, but you can't see anything at the other end. You can
                  also exit this corridor to port or enter the locker to starboard.";
              }
              print "With a long row of amber lights that try to shine through the smog, you make out a
              storage locker at the end of this corridor that houses all the extra meals the crew would need
              when not in hypersleep. Along the aft bulkhead, a sensor relay sits in the center of this
              hallway.^^You can see the door to the locker is ";
              if (foodLockerCorridorDeckBDoor.isDoorOpen) print "open";
              else print "closed";
              print ". A tunnel runs towards the forward part of the ship, but you can't see anything at the other end. ";
              if (foodLockerCorridorDeckBDoor.isDoorOpen) "You can also exit this corridor to port or enter the locker to starboard.";
              "You can also exit this corridor to port.";
          ],
          n_to [;
              if (alien in self) return PXF();
              self.firstTime = true;
              return forwardStarboardJunctionDeckB;
          ],
          w_to [;
              if (alien in self) return PXF();
              self.firstTime = true;
              return aftCompanionwayDeckB;
          ],
          e_to [;
              if (alien in self) return PXF();
              if (foodStorage.alienWrecked) {
                  self.firstTime = true;
                  return PlayerTo(foodStorage, 2);
              }
              <<Enter foodLockerCorridorDeckBDoor>>;
          ],
          cant_go [;
              if (alien in self) return PXF();
              if (foodStorage.alienWrecked) "You can go forward, port, or starboard.";
              if (foodLockerCorridorDeckBDoor.isDoorOpen) "You can go forward, port, or starboard.";
              "You can go forward or port.";
          ],
          before [;
              EnterDoorCode:
                  if (dataReader.knowDoorCode) {
                      <<SetCode foodLockerCorridorDeckBPanel>>;
                  }
                  "You don't know any codes.";
              Exit:
                  if (alien in self) return PXF();
                  self.firstTime = true;
                  PlayerTo(aftCompanionwayDeckB, 2);
                  rtrue;
              Listen:

              GoIn:
                  if (foodStorage.alienWrecked) <<Enter foodLockerCorridorDeckBDoor>>;
                  if (foodLockerCorridorDeckBDoor.isDoorOpen) <<Enter foodLockerCorridorDeckBDoor>>;
	  ],
          roomCount true,
	  firstTime true;

! 10/26/21

  RoomObj -> foodLockerCorridorDeckBObj "corridor"
    with  name 'corridor' 'area' 'passageway' 'passage' 'place',
          description [;
	      <<Look foodLockerCorridorDeckB>>;
          ],
          before [;
	      Take, Remove, Turn, PushDir, Push, Pull:
                  "You can't do that to the corridor.";
          ];

! 10/26/21

  Object  -> foodLockerCorridorDeckBPanel "panel"
    with  name 'security' 'panel' 'pad' 'input' 'screen',
          before [;
              Examine:
                  player.advanceGravity = false;
                  if (foodStorage.alienWrecked) "The panel has been spit on. Acid boils through the screen.";
                  if (door_code-->1 == 0) "The panel has a ten-digit input pad along with a readout that displays the last code entered: 0000";
                  if (door_code-->1 < 1000) {
                      print "The panel has a ten-digit input pad along with a readout that displays the last code entered: ";
                      if (door_code-->1 < 10) "000", door_code-->1;
                      if (door_code-->1 < 100) "00", door_code-->1;
                      "0", door_code-->1;
                  }
                  "The panel has a ten-digit input pad along with a readout that displays the last code entered: ", door_code-->1;
              SetTo:
                  if (foodStorage.alienWrecked) "The panel has been spit on. Acid boils through the screen. So you're not setting the code to anything.";
                  if (foodLockerCorridorDeckBDoor.isDoorOpen) "The door's open. You don't need to do that.";
                  if (second == 10000) "Please enter a four digit number.";
                  if (second == 0) {
                      door_code-->1 = 0;
                      "You clear the panel.";
                  }
                  door_code-->1 = second;
                  if (second == door_code-->0) {
!                      ScoreDoor();
                      foodLockerCorridorDeckBDoor.isDoorOpen = true;
                      "With a loud hiss, the locks disengage. Smoke swirls at the top, and the door opens.";
                  }
                  if (door_code-->1 < 10) "You set the panel to 000", door_code-->1, ".";
                  if (door_code-->1 < 100) "You set the panel to 00", door_code-->1, ".";
                  if (door_code-->1 < 1000) "You set the panel to 0", door_code-->1, ".";
                  "You set the panel to ", second, ".";
              SetCode:
                  if (foodStorage.alienWrecked) "The panel has been spit on. Acid boils through the screen. So you're not setting the code to anything.";
                  if (foodLockerCorridorDeckBDoor.isDoorOpen) "The door's open. You don't need to do that.";
                  if (dataReader.knowDoorCode) {
                      foodLockerCorridorDeckBDoor.isDoorOpen = true;
                      door_code-->1 = door_code-->0;
                      "With a loud hiss, the locks disengage. Smoke swirls at the top, and the door opens.";
                  }
                  rfalse;
              Set, SwitchOn:
                  "It doesn't work like that. You need to type in the numbers. Try: SET PANEL TO XXXX";
              Open:
                  "You need to open the door, not the panel.";
              Unlock:
                  if (foodStorage.alienWrecked) "The panel has been spit on. Acid boils through the screen. But the door has been ripped off and is already open.";
                  if (foodLockerCorridorDeckBDoor.isDoorOpen) "The door is already open.";
                  "That's not what is locked. The door is.";
              Blow:
                 "You can't blow through your suit. The polymer seals in your environment.";
              Attack, Blow, Burn, Climb, Close, Cut, Dig, Drink, Eat, Empty, Enter, Exit, GetOff, Go, GoIn, JumpOver, Kick, Listen, LookUnder, Open:
                  "That's not going to help.";
              Push, PushDir, Pull, Remove, Rub, Search, Set, SetTo, Smell, Squeeze, Swing, SwitchOn, SwitchOff, Take, Talk, Taste, Tie, Touch, Transfer, Turn, Unlock, Wave:
                  "That's not going to help.";
          ],
     has  static scenery;


! 10/26/21

  NoHelp  -> foodLockerCorridorDeckBDoor "door"
    with  name 'door' 'food' 'locker' 'freezer' 'rails' 'hatch' 'ph008' 'ph009' 'frame' 'storage',
          before [ w1 w2;
              Examine:
                  player.advanceGravity = false;
                  if (foodStorage.alienWrecked) "The locker door is gone, and the frame looks pounded on, but from the inside.";
		  if (self.isDoorOpen) "With the freezer door open, it exudes a cold mist that envelopes the corridor.";
		  "It's a sturdy door on rails, almost like a walk-in freezer, labeled ~Food Locker.~ It has a security panel next to it.";
              Enter:
                  if (alien in foodLockerCorridorDeckB) return PXF();
                  if (self.isDoorOpen || foodStorage.alienWrecked) {
                      foodLockerCorridorDeckB.firstTime = true;
                      return PlayerTo(foodStorage, 2);
                  }
                  "The storage locker is closed. You're not getting in without the code.";
              Open:
                  if (foodStorage.alienWrecked) "The door to the freezer has been torn off. You can't open it.";
                  if (self.isDoorOpen) "The freezer door is open, and a cold mist pours out. You watch it fight with smoke over who can obscure that air more.";
                  "It's locked. You need to enter the code into the panel.";
              Lock:
                  if (foodStorage.alienWrecked) "The door to the freezer has been torn off. You don't need to do that.";
                  if (self.isDoorOpen) "Don't waste your time trying to figure that out.";
                  "The hatch is locked at the moment.";
              Close:
                  if (foodStorage.alienWrecked) "The door to the freezer has been torn off. You can't close it.";
                  if (self.isDoorOpen) "But you worked so hard to open it.";
                  "It's already closed.";
              Unlock:
                  if (foodStorage.alienWrecked) "The door to the freezer has been torn off. You don't need to do that.";
                  wn--; wn--;
                  w1 = NextWord();
                  w2 = NextWord();
                  if (w2 == 'code') <<SetCode foodLockerCorridorDeckBPanel>>;
                  "That's not going to work. You need to enter the code into the panel.";
              SetTo:
                  <<SetTo foodLockerCorridorDeckBPanel second>>;
              SetCode:
                  <<SetCode foodLockerCorridorDeckBPanel>>;
              Set, SwitchOn:
                  "It doesn't work like that. You need to type in the numbers. Try: SET DOOR TO XXXX";
              Take:
                  if (foodStorage.alienWrecked) "The door is gone, and you're not taking the frame.";
                  "You're not going to pull the freezer door off the rails, plus it's worthless.";

          ],
          isDoorOpen false;

! 01/15/22

  OutRch  -> foodLockerCorridorDeckBTunnel "tunnel"
    with  name 'tunnel',
          before [;
              Examine:
                  player.advanceGravity = false;
                  if (alien in forwardStarboardJunctionDeckB) "Is there something shifting in the smoke down there? It's hard to tell.";
		  "Smoke fills the forward tunnel, just like the rest of the ship.";
              Enter, Go:
                  if (alien in foodLockerCorridorDeckB) return PXF();
                  foodLockerCorridorDeckB.firstTime = true;
                  PlayerTo(forwardStarboardJunctionDeckB, 2);
                  rtrue;
          ];

! 03/03/22

  StObj   -> foodLockerCorridorDeckBSensor "sensor relay"
    with  name 'sensor' 'relay' 'tall' 'cylinder' 'beige' 'receiver' 'smooth' 'metal',
          before [;
              Attack:
                  "The relay stands one meter wide. You're not going to do any damage to it.";
              Climb:
                  "The cylinder's a meter thick, but the only thing you'll find up there is radiation.";
              Examine, Search:
                  player.advanceGravity = false;
		  "The sensor relay is a tall cylinder painted beige and capped with lead. A warning label wraps around the covering. ";
              Touch:
                  "You hesitate for a moment, then put your hand on the smooth metal. It feels warm.";
              Push, PushDir, Pull, Take, Remove, Turn:
                  "It's a large cylinder, a meter thick and over 100 pounds. It would take two to move. It isn't going anywhere.";
              Rub:
                  "The metal is smooth and clean, and warm when you touch it.";

          ];

! 03/03/22

  OutRch  -> foodLockerCorridorDeckBCap "lead cap"
    with  name 'lead' 'cap' 'warning' 'label' 'cover' 'covering' 'top',
          before [;
              Climb:
                  <<Climb foodLockerCorridorDeckBSensor>>;
              Examine, Search:
                  player.advanceGravity = false;
		  "The receiver is capped with lead to limit radiation bleed through. Along the top, it says High Output.";
              Read:
                  "At the top, it says High Output.";
              Go:
                  "You're standing at the base of the cylinder. There's no need to reach the top.";
          ];
