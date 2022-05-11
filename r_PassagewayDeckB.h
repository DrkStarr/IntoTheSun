
! ---------------------------------------------------------------------------- !
!       PASSAGEWAY DECK B. 10/25/21
!
  Room    passagewayDeckB "Port-Side Passageway - Deck B"
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
              if (weaponsLocker.alienWrecked) {
                  "Lights try to break through the haze, but there's not enough juice coursing back here.
                  This corridor has a weapons locker that sits at the end of it, port side, but the hatch
                  is torn off, and the panel is covered in acid.^^Forward, a corridor leads off into
                  darkness - port, you can enter the weapons locker, starboard you can exit the passageway.";
              }
              print "Lights try to break through the haze, but there's not enough juice coursing back here.
              This corridor has a weapons locker that sits at the end of it, port side. ";
              if (self.enterWeaponsLocker) print "Too bad it didn't have much inside, but this ship is a tug";
              else print "A locker that should hold plenty of munitions but on a tug like this could have nothing at all";
              print ".^^";
              if (passagewayDeckBDoor.isDoorOpen || weaponsLocker.alienWrecked)
                  "Forward, a corridor leads off into darkness - port, you can enter the weapons locker, starboard you can exit the passageway.";
              "Forward, a corridor leads off into darkness - starboard you can exit the passageway.";
          ],
          n_to [;
              if (alien in self) return PXF();
              self.firstTime = true;
              return forwardPortJunctionDeckB;
          ],
          e_to [;
              if (alien in self) return PXF();
              self.firstTime = true;
              return aftCompanionwayDeckB;
          ],
          w_to [;
              if (alien in self) return PXF();
              if (weaponsLocker.alienWrecked) {
                  self.firstTime = true;
                  return PlayerTo(weaponsLocker, 2);
              }
              <<Enter passagewayDeckBDoor>>;
          ],
          cant_go [;
              if (alien in self) return PXF();
              if (weaponsLocker.alienWrecked) "You can go forward, port, or starboard.";
              if (passagewayDeckBDoor.isDoorOpen) "You can go forward, port, or starboard.";
              "You can go forward or starboard.";
          ],
          before [;
              EnterDoorCode:
                  if (dataReader.knowDoorCode) {
                      <<SetCode passagewayDeckBPanel>>;
                  }
                  "You don't know any codes.";
              Exit:
                  if (alien in self) return PXF();
                  self.firstTime = true;
                  PlayerTo(aftCompanionwayDeckB, 2);
                  rtrue;
              Listen:

              GoIn:
                  if (weaponsLocker.alienWrecked) <<Enter passagewayDeckBDoor>>;
                  if (passagewayDeckBDoor.isDoorOpen) <<Enter passagewayDeckBDoor>>;
          ],
          enterWeaponsLocker false,
          roomCount true,
          firstTime true;

! 10/25/21

  RoomObj -> passagewayDeckBObj "passageway"
    with  name 'area' 'passageway' 'passage' 'place',
          description [;
              <<Look passagewayDeckB>>;
          ],
          before [;
              Take, Remove, Turn, PushDir, Push, Pull:
                  "You can't do that to the passageway.";
          ];

! 10/25/21

  NoHelp  -> passagewayDeckBPanel "panel"
    with  name 'security' 'panel' 'code' 'pad' 'input',
          before [;
              Examine:
                  player.advanceGravity = false;
                  if (weaponsLocker.alienWrecked) "Acid cooks the screen and melts through the input pad.";
                  if (door_code-->2 == 0) "The panel has a ten-digit input pad along with a readout that displays the last code entered: 0000";
                  if (door_code-->2 < 1000) {
                      print "The panel has a ten-digit input pad along with a readout that displays the last code entered: ";
                      if (door_code-->2 < 10) "000", door_code-->2;
                      if (door_code-->2 < 100) "00", door_code-->2;
                      "0", door_code-->2;
                  }
                  "The panel has a ten-digit input pad along with a readout that displays the last code entered: ", door_code-->2;
              SetTo:
                  if (weaponsLocker.alienWrecked) "Acid cooks the screen and melts through the input pad. So you're not setting the code to anything.";
                  if (passagewayDeckBDoor.isDoorOpen) "The door's open. You don't need to do that.";
                  if (second == 10000) "Please enter a four digit number.";
                  if (second == 0) {
                      door_code-->2 = 0;
                      "You clear the code on the panel.";
                  }
                  door_code-->2 = second;
                  if (second == door_code-->0) {
!                      ScoreDoor();
                      passagewayDeckBDoor.isDoorOpen = true;
                      "With a loud hiss, the locks disengage. Smoke swirls at the top, and the door opens.";
                  }
                  if (door_code-->2 < 10) "You set the code to 000", door_code-->2, ".";
                  if (door_code-->2 < 100) "You set the code to 00", door_code-->2, ".";
                  if (door_code-->2 < 1000) "You set the code to 0", door_code-->2, ".";
                  "You set the code to ", second, ".";
              SetCode:
                  if (weaponsLocker.alienWrecked) "Acid cooks the screen and melts through the input pad. So you're not setting the code to anything.";
                  if (passagewayDeckBDoor.isDoorOpen) "The door's open. You don't need to do that.";
                  if (dataReader.knowDoorCode) {
                      passagewayDeckBDoor.isDoorOpen = true;
                      door_code-->2 = door_code-->0;
                      "With a loud hiss, the locks disengage. Smoke swirls at the top, and the door opens.";
                  }
                  rfalse;
              Set, SwitchOn:
                  "It doesn't work like that. You need to type in the numbers. Try: SET PANEL TO XXXX";
              Open:
                  "You need to open the door, not the panel.";
              Unlock:
                  if (weaponsLocker.alienWrecked) "The panel has been spit on. Acid boils through the screen. But the door has been ripped off and is already open.";
                  if (passagewayDeckBDoor.isDoorOpen) "The door is already open.";
                  "That's not what is locked. The door is.";
          ];

! 10/25/21

  NoHelp  -> passagewayDeckBDoor "door"
    with  name 'door' 'weapons' 'locker' 'empty' 'void' 'dried' 'blood' 'hatch' 'ph006' 'ph007' 'frame',
          before [ w1 w2;
              Examine:
                  player.advanceGravity = false;
                  if (weaponsLocker.alienWrecked) "The door to the weapons locker has been torn off. All that's left is the frame.";
                  if (self.isDoorOpen) "The door's open, giving you access to what little the ship has.";
                  "The door to port is labeled ~Weapons Locker,~ and has a security panel next to it.
                  As you look at it a little closer, you see a spot of dried blood on it.";
              Enter:
                  if (alien in passagewayDeckB) return PXF();
                  if (self.isDoorOpen || weaponsLocker.alienWrecked) {
                      passagewayDeckB.enterWeaponsLocker = true;
                      passagewayDeckB.firstTime = true;
                      PlayerTo(weaponsLocker, 2);
                      rtrue;
                  }
                  "The weapons locker is closed. You're not getting in without the code.";
              Open:
                  if (weaponsLocker.alienWrecked) "The door to the weapons locker has been torn off. You can't open it.";
                  if (self.isDoorOpen) "The door is already open, and the smoke in this passageway is drawn into the empty void.";
                  "It's locked. You need to enter the code into the panel.";
              Close:
                  if (weaponsLocker.alienWrecked) "The door to the weapons locker has been torn off. You can't close it.";
                  if (self.isDoorOpen) "But you worked so hard to open it.";
                  "It's already closed.";
              Lock:
                  if (weaponsLocker.alienWrecked) "The door to the weapons locker has been torn off. You don't need to do that.";
                  if (self.isDoorOpen) "Don't waste your time trying to figure that out.";
                  "The door is locked at the moment.";
              Unlock:
                  if (weaponsLocker.alienWrecked) "The door to the weapons locker has been torn off. You don't need to do that.";
                  wn--; wn--;
                  w1 = NextWord();
                  w2 = NextWord();
                  if (w2 == 'code') <<SetCode passagewayDeckBPanel>>;
                  "That's not going to work. You need to enter the code into the panel.";
              SetTo:
                  <<SetTo passagewayDeckBPanel second>>;
              SetCode:
                  <<SetCode passagewayDeckBPanel>>;
              Set, SwitchOn:
                  "It doesn't work like that. You need to type in the numbers. Try: SET DOOR TO XXXX";
              Take:
                  if (weaponsLocker.alienWrecked) "The door is gone, and you're not taking the frame.";
                  "The door isn't easily coming off the rails, and it's worthless.";
          ],
          isDoorOpen false;

! 01/16/22

  StObj   -> passagewayDeckBDarkness "corridor"
    with  name 'heavy' 'darkness' 'corridor',
          before [;
              Examine:
                  player.advanceGravity = false;
                  "The corridor forward falls off into heavy darkness. You can't see anything down there.";
              Enter, Go:
                  if (alien in passagewayDeckB) return PXF();
                  passagewayDeckB.firstTime = true;
                  PlayerTo(forwardPortJunctionDeckB, 2);
                  rtrue;
          ];
