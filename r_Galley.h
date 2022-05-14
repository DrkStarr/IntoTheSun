
! ---------------------------------------------------------------------------- !
!       GALLEY. 11/01/21
!
  Room    galley "Galley - Deck A"
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
              print "With one large table in the middle, this room serves as the galley for the ship.
              But something happened here, and someone tried to clean it up. Even in this light,
              you can see dried blood underneath the table.^^Forward, there's an automated door
              to the bridge. You can see the panel next to it lit up. Starboard, there's a torn-down
              hatch. Aft, you can go back to the companionway";
              if (nutrientProcessor in galleyCounter)".^^Along the port bulkhead, a nutrient processor sits on top of a counter.";
              ".";
          ],
          n_to [;
              if (alien in self) return PXF();
              <<Enter forwardCorridorDeckADoor>>;
          ],
          s_to [;
              if (alien in self) return PXF();
              self.firstTime = true;
              return forwardCompanionwayDeckA;
          ],
          e_to [;
              if (alien in self) return PXF();
              self.firstTime = true;
              return captainsQuarters;
          ],
          cant_go [;
              if (alien in self) return PXF();
              if (forwardCorridorDeckADoor.isDoorUnlocked) "You can go forward, aft, or starboard.";
              "You can go aft or starboard.";
          ],
          before [;
              EnterDoorCode:
                  if (dataReader.knowDoorCode) {
                      <<SetCode forwardCorridorDeckAPanel>>;
                  }
                  "You don't know any codes.";
              Exit:

              GoIn:
                  if (forwardCorridorDeckADoor.isDoorUnlocked) {
                      if (alien in self) return PXF();
                      <<Enter forwardCorridorDeckADoor>>;
                  }
              Listen:

          ],
          roomCount true,
          firstTime true,
          takenProcessor false;

! 11/01/21

  RoomObj -> galleyObj "galley"
    with  name 'galley' 'area' 'place' 'section',
          description [;
              <<Look galley>>;
          ],
          before [;
              Take, Remove, Turn, PushDir, Push, Pull:
                  "You can't do that to the galley.";
          ];

! 12/01/21

  Object  -> forwardCorridorDeckAPanel "panel"
    with  name 'security' 'panel' 'pad' 'input',
          before [;
              Examine:
                  player.advanceGravity = false;
                  if (door_code-->3 == 0) "The panel has a ten-digit input pad along with a readout that displays the last code entered: 0000";
                  if (door_code-->3 < 1000) {
                      print "The panel has a ten-digit input pad along with a readout that displays the last code entered: ";
                      if (door_code-->3 < 10) "000", door_code-->3;
                      if (door_code-->3 < 100) "00", door_code-->3;
                      "0", door_code-->3;
                  }
                  "The panel has a ten-digit input pad along with a readout that displays the last code entered: ", door_code-->3;
              SetTo:
                  if (forwardCorridorDeckADoor.isDoorUnlocked) "The door's unlocked. You don't need to do that.";
                  if (second == 10000) "Please enter a four digit number.";
                  if (second == 0) {
                      door_code-->3 = 0;
                      "You clear the panel.";
                  }
                  door_code-->3 = second;
                  if (second == door_code-->0) {
                      forwardCorridorDeckADoor.isDoorUnlocked = true;
                      "The locks disengage with a loud hiss as excess gas on the bridge is vented -
                      the smoke around you swirls and churns in its wake.";
                  }
                  if (door_code-->3 < 10) "You set the panel to 000", door_code-->3, ".";
                  if (door_code-->3 < 100) "You set the panel to 00", door_code-->3, ".";
                  if (door_code-->3 < 1000) "You set the panel to 0", door_code-->3, ".";
                  "You set the panel to ", second, ".";
              SetCode:
                  if (forwardCorridorDeckADoor.isDoorUnlocked) "The door's unlocked. You now have access to the heart of the ship.";
                  if (dataReader.knowDoorCode) {
                      forwardCorridorDeckADoor.isDoorUnlocked = true;
                      door_code-->3 = door_code-->0;
                      "The locks disengage with a loud hiss as excess gas on the bridge is vented -
                      the smoke around you swirls and churns in its wake.";
                  }
                  rfalse;
              Enter, Set, SwitchOn:
                  "It doesn't work like that. You need to type in the numbers. Try: SET PANEL TO XXXX";
              Unlock:
                  "That's not what is locked. The door is.";
              Blow:
                 "You can't blow through your suit. The polymer seals in your environment.";
              Attack, Blow, Burn, Climb, Close, Cut, Dig, Drink, Eat, Empty, Enter, Exit, GetOff, Go, GoIn, JumpOver, Kick, Listen, LookUnder, Open:
                  "That's not going to help.";
              Push, PushDir, Pull, Remove, Rub, Search, Set, SetTo, Smell, Squeeze, Swing, SwitchOn, SwitchOff, Take, Talk, Taste, Tie, Touch, Transfer, Turn, Unlock, Wave:
                  "That's not going to help.";
          ],
     has  static scenery;

! 12/01/21

  NoHelp  -> forwardCorridorDeckADoor "door"
    with  name 'automated' 'automatic' 'door' 'bridge',
          before [ w1 w2;
              Attack:
                  "You don't need to break it. The door still works. You just need to open it using the panel.";
              Examine:
                  player.advanceGravity = false;
                  if (self.isDoorUnlocked) "The automated door's unlocked. You now have access to the heart of the ship.";
                  "The automated door is for officers only and has a security panel next to it.
                  Dried blood sticks to the door.";
              Enter:
                  if (alien in galley) return PXF();
                  if (self.isDoorUnlocked) {
                      print "The door opens long enough for you to walkthrough, then closes behind you.^";
                      galley.firstTime = true;
                      PlayerTo(bridge, 2);
                      rtrue;
                  }
                  "The door is locked. You're not getting in without the code.";
              Open:
                  if (self.isDoorUnlocked) "The door's unlocked. You now have access to the heart of the ship.";
                  "It's locked. You need to open it using the panel.";
              Lock:
                  if (self.isDoorUnlocked) "Don't waste your time trying to figure that out.";
                  "The door's already locked.";
              Close:
                  if (self.isDoorUnlocked) "But you worked so hard to open it.";
                  "It's already closed.";
              Unlock:
                  if (self.isDoorUnlocked) "The door's unlocked. You now have access to the heart of the ship.";
                  wn--; wn--;
                  w1 = NextWord();
                  w2 = NextWord();
                  if (w2 == 'code') <<SetCode forwardCorridorDeckAPanel>>;
                  "That's not going to work. You need to enter the code into the panel.";
              SetTo:
                  <<SetTo forwardCorridorDeckAPanel second>>;
              SetCode:
                  <<SetCode forwardCorridorDeckAPanel>>;
              Set, SwitchOn:
                  "It doesn't work like that. You need to type in the numbers. Try: SET DOOR TO XXXX";
              Rub:
                  "You don't have time for that. You are plunging into the sun.";
          ],
          scoredDoor false,
          isDoorUnlocked false;

! 01/07/22

  StObj   -> galleyTable "table"
    with  name 'large' 'round' 'table',
          before [;
              Examine:
                  player.advanceGravity = false;
                  "A large round table takes up the center of the room. It's not big enough for the entire crew, but they take turns eating in the mess.";
              Push, Pull, PushDir, Remove, Turn:
                  "The table isn't going anywhere, it's large and bulky, and you're not going to be able to push it around.";
              Take:
                  "The table is big and isn't worth anything.";
              Rub:
                  "You don't have time for that. You are plunging into the sun.";
              LookUnder:
                  <<Examine galleyBlood>>;
          ],
     has  supporter;

! 01/07/22

  StObj   -> galleyBlood "blood"
    with  name 'dried' 'blood',
          before [;
              Examine:
                  player.advanceGravity = false;
                  "Blood splashed across this room before someone cleaned it up. Something ugly happened here if it's on the door and under the table.";
              Take, Push, Pull, PushDir, Remove, Turn:
                  "It has dried and isn't going anywhere.";
              Rub:
                  "You don't have time for that. You are plunging into the sun.";
          ];

! 01/14/22

  StObj   -> galleyHatch "hatch"
    with  name 'hatch' 'torn-down' 'torn' 'mangled' 'broken' 'room',
          before [;
              Examine:
                  player.advanceGravity = false;
                  if (alien in captainsQuarters) "Is there something shifting in the smoke behind the hatch? It's hard to tell.";
                  "Torn apart, there's not much left of the hatch allowing you to enter the room.";
              Enter:
                  if (alien in galley) return PXF();
                  galley.firstTime = true;
                  PlayerTo(captainsQuarters, 2);
                  rtrue;
              Go:
                  "You are already here.";
              Take:
                  "The hatch has been ripped apart. There's not much to take, and it's worthless.";
          ];

! 05/12/22

  StObj   -> galleyCounter "counter"
    with  name 'counter',
          before [;
              Examine:
                  if (nutrientProcessor in self)
                      "Looking over the counter, you see a nutrient processor - a large device that takes up the corner of this room.";
                  "Looking over the counter, you see only dust, a layer of soot that has settled in.";
              Go:
                  "You are already here.";
              Take:
                  "The counter is part of the ship. It isn't going anywhere.";
              Open:
                  "It's more of a utility surface than a storage area. There are no drawers on it.";
              Search:
                  if (nutrientProcessor in self)
                      "The nutrient processor is on the counter.";
                  "The counter is empty.";
          ],
     has  supporter;
