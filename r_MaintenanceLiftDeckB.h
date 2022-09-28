
! ---------------------------------------------------------------------------- !
!       MAINTENANCE LIFT DECK B. 10/24/21
!
  Room    maintenanceLiftDeckB "Maintenance Lift - Deck B"
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
              "The air doesn't circulate here, so there's not as much smoke in the lift.
              A panel is attached to the doors with two buttons that operate the elevator,
              while the only way out is through the vertical doors starboard.";
          ],
          e_to [;
              <<Enter maintenanceLiftDeckBDoors>>;
          ],
          u_to [;
              <<SwitchOn maintenanceLiftDeckBPanel>>;
          ],
          cant_go [;
              "You can exit starboard or up.";
          ],
          before [;
              Exit:
                  <<Enter maintenanceLiftDeckBDoors>>;
              Listen:

          ],
          isGateClosed false,
          roomCount true,
          firstTime true;

! 10/24/21

  RoomObj -> maintenanceLiftDeckBObj "lift"
    with  name 'maintenance' 'lift' 'elevator' 'cage',
          description [;
              <<Look maintenanceLiftDeckB>>;
          ],
          before [;
              Take, Remove, Turn, PushDir, Push, Pull:
                  "You can't do that to the lift.";
          ];

! 10/24/21

  StObj   -> maintenanceLiftDeckBPanel "panel"
    with  name 'panel' 'switch' 'grease',
          before [ iTempLoc;
              Examine:
                  player.advanceGravity = false;
                  "Grease covers the panel that operates the lift. It has two dirty buttons on it.
                  The one marked Deck A is red - the other marked Deck B is green.";
              SwitchOn, Turn, Push:
                  if (maintenanceLiftDeckBDoors.isDoorOpen) {
                      maintenanceLiftDeckBDoors.isDoorOpen = false;
                      print "(first closing the doors)^";
                  }
                  if (AlienCloseToElevator()) {
                      iMonsterDestination = AFTJNCTNDECKA;
                      monster_loc-->iMonsterLoc = AFTJNCTNDECKA;
                      iTempLoc = iMonsterLoc;
                      iTempLoc++;
                      if (iTempLoc > MONSTERTOTAL) iTempLoc = 0;
                      monster_loc-->iTempLoc = AFTJNCTNDECKA;
                  }
                  print "You flip the switch to Deck A as the lift trembles in return. And then, slowly,
                  it takes you to the deck above. Once there, the doors starboard open.^";
                  maintenanceLiftDeckA.isGateClosed = true;
                  maintenanceLiftDeckADoors.isDoorOpen = true;
                  maintenanceLiftDeckB.firstTime = true;
                  PlayerTo(maintenanceLiftDeckA, 2);
                  return ItemFirstTaken();
              Set, SetTo:
                  "Try to push a button.";
          ];

! 10/24/21

  StObj   -> maintenanceLiftDeckBButtonA "red button"
    with  name 'red' 'button' 'buttons' 'dirty' 'dirt' 'grease',
          before [;
              Examine:
                  player.advanceGravity = false;
                  "Grease and dirt are smudged against the red button that will take you to the upper deck.";
              Push, SwitchOn, Turn:
                  if (maintenanceLiftDeckBDoors.isDoorOpen) {
                      maintenanceLiftDeckBDoors.isDoorOpen = false;
                      print "(first closing the doors)^";
                  }
                  print "You push the button as the lift trembles in return. The doors automatically close,
                  causing you to step back. And then you hear gears grind, like an old engine starting up.
                  Slowly, you go to the deck above. Once there, the doors starboard open.^";
                  maintenanceLiftDeckA.isGateClosed = true;
                  maintenanceLiftDeckADoors.isDoorOpen = true;
                  maintenanceLiftDeckB.firstTime = true;
                  PlayerTo(maintenanceLiftDeckA, 2);
                  return ItemFirstTaken();
              Set, SetTo:
                  "Try to push the button.";
          ];

! 10/24/21

  StObj   -> maintenanceLiftDeckBButtonB "green button"
    with  name 'green' 'button' 'buttons' 'dirty' 'dirt' 'grease',
          before [;
              Examine:
                  player.advanceGravity = false;
                  "Covered in grease, the green button is worn from too much use.";
              Push, SwitchOn, Turn:
                  "You push the button, but it does nothing. You're already on B deck.";
              Set, SetTo:
                  "Try to push the button.";
          ];

! 03/29/22

  StObj   -> maintenanceLiftDeckBDoors "doors"
    with  name 'gate' 'doors' 'door' 'vertical',
          before [;
              Examine:
                  player.advanceGravity = false;
                  if (self.isDoorOpen) "The vertical doors to the elevator are open, allowing smoke to drift into this room.";
                  "The vertical doors are closed, but there is plenty of space in this large elevator.";
              Open:
                  if (self.isDoorOpen) "They're already open.";
                  self.isDoorOpen = true;
                  "As the doors open, smoke drifts into the elevator.";
              Close:
                  if (self.isDoorOpen == false) "They're already closed.";
                  self.isDoorOpen = false;
                  "The vertical doors come together with a comforting thud. You are closed off in here.";
              Enter, Go:
                  maintenanceLiftDeckB.isGateClosed = false;
                  maintenanceLiftDeckA.isGateClosed = true;
                  if (self.isDoorOpen == false) {
                      self.isDoorOpen = true;
                      print "(first opening the doors)^";
                  }
                  maintenanceLiftDeckB.firstTime = true;
                  PlayerTo(forwardPortJunctionDeckB, 2);
                  rtrue;
          ],
          isDoorOpen true,
    has   pluralname;
