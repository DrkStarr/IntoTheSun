
! ---------------------------------------------------------------------------- !
!       MAINTENANCE LIFT DECK A. 11/08/21
!
  Room    maintenanceLiftDeckA "Maintenance Lift - Deck A"
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
              <<Enter maintenanceLiftDeckADoors>>;
          ],
          d_to [;
              <<SwitchOn maintenanceLiftDeckAPanel>>;
          ],
          cant_go [;
              "You can exit starboard or down.";
          ],
          before [;
              Exit:
                  <<Enter maintenanceLiftDeckADoors>>;
              Listen:

          ],
          isGateClosed true,
          roomCount true,
          firstTime true;

! 11/08/21

  RoomObj -> maintenanceLiftDeckAObj "lift"
    with  name 'maintenance' 'lift' 'elevator' 'cage',
          description [;
              <<Look maintenanceLiftDeckA>>;
          ],
          before [;
              Take, Remove, Turn, PushDir, Push, Pull:
                  "You can't do that to the lift.";
          ];

! 11/08/21

  StObj   -> maintenanceLiftDeckAPanel "panel"
    with  name 'panel' 'switch' 'grease',
          before [ iTempLoc;
              Examine:
                  player.advanceGravity = false;
                  "Grease covers the panel that operates the lift. It has two dirty buttons on it.
                  The one marked Deck A is red - the other marked Deck B is green.";
              SwitchOn, Turn, Push:
                  if (maintenanceLiftDeckADoors.isDoorOpen) {
                      maintenanceLiftDeckADoors.isDoorOpen = false;
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
                  print "You flip the switch to Deck B as the lift trembles in return. It takes a
                  moment as the chain slips and the cage jolts, but then you slowly descend.
                  Once there, the doors starboard open.^";
                  maintenanceLiftDeckB.isGateClosed = true;
                  maintenanceLiftDeckBDoors.isDoorOpen = true;
                  maintenanceLiftDeckA.firstTime = true;
                  PlayerTo(maintenanceLiftDeckB, 2);
                  rtrue;
              Set, SetTo:
                  "Try to push a button.";
          ];

! 11/08/21

  StObj   -> maintenanceLiftDeckAButtonA "red button"
    with  name 'red' 'button' 'buttons' 'dirty' 'dirt' 'grease',
          before [;
              Examine:
                  player.advanceGravity = false;
                  "Dirt and grease are smudged against the red button.";
              Push, SwitchOn, Turn:
                  "You push the button, but it does nothing. You're already on A deck.";
              Set, SetTo:
                  "Try to push the button.";
          ];

! 11/08/21

  StObj   -> maintenanceLiftDeckAButtonB "green button"
    with  name 'green' 'button' 'buttons' 'dirty' 'dirt' 'grease',
          before [;
              Examine:
                  player.advanceGravity = false;
                  "Covered in grease, the green button will take you down to B deck.";
              Push, SwitchOn, Turn:
                  if (maintenanceLiftDeckADoors.isDoorOpen) {
                      maintenanceLiftDeckADoors.isDoorOpen = false;
                      print "(first closing the doors)^";
                  }
                  print "You push the button as the lift trembles in return, slowly taking you down to the next deck. Once there, the doors starboard open.^";
                  maintenanceLiftDeckB.isGateClosed = true;
                  maintenanceLiftDeckBDoors.isDoorOpen = true;
                  maintenanceLiftDeckA.firstTime = true;
                  PlayerTo(maintenanceLiftDeckB, 2);
                  rtrue;
              Set, SetTo:
                  "Try to push the button.";
          ];

! 03/29/22

  StObj   -> maintenanceLiftDeckADoors "doors"
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
                  maintenanceLiftDeckA.isGateClosed = false;
                  maintenanceLiftDeckB.isGateClosed = true;
                  if (self.isDoorOpen == false) {
                      self.isDoorOpen = true;
                      print "(first opening the doors)^";
                  }
                  maintenanceLiftDeckA.firstTime = true;
                  PlayerTo(aftJunctionDeckA, 2);
                  rtrue;
          ],
          isDoorOpen true,
    has   pluralname;

! 01/17/22

  StObj   maintenanceLiftSmoke "smoke"
    with  name 'smoke' 'air' 'haze' 'hazy' 'thick' 'gloom' 'dark' 'cloud' 'smog' 'dense',
          before [;
              Examine:
                  player.advanceGravity = false;
                  "The smoke in here is thinner than the rest of the ship.";
              Enter, Go:
                  "You need to tell me which direction to go in.";
          ],
          found_in maintenanceLiftDeckA maintenanceLiftDeckB;

! 11/07/21

  StObj   maintenanceLiftLights "lights"
    with  name 'dim' 'light' 'lights' 'glow' 'soft' 'amber' 'led' 'leds' 'orange',
          before [;
              Examine:
                  player.advanceGravity = false;
                  "There are no lights in the lift. If there were, they burned out long ago.";
              Go:
                  "You are already here.";
          ],
          found_in maintenanceLiftDeckA maintenanceLiftDeckB;
