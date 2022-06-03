
! ---------------------------------------------------------------------------- !
!       AFT JUNCTION DECK A. 11/03/21
!
  Room    aftJunctionDeckA "Aft Junction - Deck A"
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
              print "Filled with smoke, the aft portion of A deck never has a lot of light - the area
              is used for support. Goods are brought through here from a maintenance lift that's port. A
              handcart is pushed up against the vertical doors.^^";
              if (maintenanceLiftDeckA.isGateClosed) "The elevator doors are closed. The corridor runs forward to the companionway and starboard to a room.";
              "This corridor runs port into the lift and starboard into a room. You can also go forward to the companionway.";
          ],
          n_to [;
              if (alien in self) return PXF();
              self.firstTime = true;
              return forwardCompanionwayDeckA;
          ],
          e_to [;
              if (alien in self) return PXF();
              self.firstTime = true;
              return personalLockerRoom;
          ],
          w_to [;
              <<Enter logisticsCorridorLift>>;
          ],
          cant_go [;
              if (alien in self) return PXF();
              if (maintenanceLiftDeckA.isGateClosed) "You can go forward or starboard.";
              "You can go forward, port, or starboard.";
          ],
          before [;
              Exit:

              GoIn:
                  <<Enter logisticsCorridorLift>>;
              Listen:

          ],
          roomCount true,
          firstTime true;

! 11/03/21

  RoomObj -> aftJunctionDeckAObj "junction"
    with  name 'junction' 'area' 'place' 'passage' 'tunnel' 'corridor',
          description [;
              <<Look aftJunctionDeckA>>;
          ],
          before [;
              Take, Remove, Turn, PushDir, Push, Pull:
                  "You can't do that to the junction.";
          ];

! 11/08/21

  NoHelp   -> logisticsCorridorLift "maintenance lift"
    with  name 'maintenance' 'lift' 'heavy' 'gate' 'elevator' 'cage' 'metal' 'door' 'vertical',
          before [;
              Examine:
                  player.advanceGravity = false;
                  if (maintenanceLiftDeckA.isGateClosed)
                      "The maintenance lift has two large vertical doors that are closed, scratched, and dirty. They also
                      block the way port, choking off the smoke in this area. Next to the lift, there's a call button.";
                  "The maintenance lift's vertical doors are open. As a result, smoke trickles into the elevator. However, air doesn't circulate through that area, so it's not filled with a lot of smoke.";
              Enter, Go:
                  if (alien in aftJunctionDeckA) return PXF();
                  if (maintenanceLiftDeckA.isGateClosed) "The vertical doors are shut. The lift isn't on this level, but there's a call button on the side.";
                  aftJunctionDeckA.firstTime = true;
                  PlayerTo(maintenanceLiftDeckA, 2);
                  rtrue;
              Rub:
                  "What a noble gesture, but you don't have time for that sort of thing.";
              Close:
                  if (maintenanceLiftDeckA.isGateClosed) "That's already closed.";
                  "You don't need to do that.";
              Open:
                  if (maintenanceLiftDeckA.isGateClosed) <<Push logisticsCorridorButton>>;
                  "That's already open.";
          ];

! 03/29/22

  NoHelp  -> logisticsCorridorDoors "maintenance lift"
    with  name 'doors',
          before [;
              Examine:
                  <<Examine logisticsCorridorLift>>;
              Enter, Go:
                  <<Enter logisticsCorridorLift>>;
              Rub:
                  <<Rub logisticsCorridorLift>>;
              Close:
                  <<Close logisticsCorridorLift>>;
              Open:
                  <<Open logisticsCorridorLift>>;
          ],
    has   pluralname;

! 11/08/21

  StObj   -> logisticsCorridorButton "call button"
    with  name 'call' 'button',
          before [ iTempLoc;
              Examine:
                  player.advanceGravity = false;
                  "It's a simple button used to call the elevator to this deck.";
              Push, Pull:
                  if (alien in aftJunctionDeckA) return PXF();
                  if (maintenanceLiftDeckA.isGateClosed) {
                      maintenanceLiftDeckA.isGateClosed = false;
                      maintenanceLiftDeckB.isGateClosed = true;
                      maintenanceLiftDeckADoors.isDoorOpen = true;
                      maintenanceLiftDeckBDoors.isDoorOpen = false;
                      if (AlienCloseToElevator()) {
                          iMonsterDestination = AFTJNCTNDECKA;
                          monster_loc-->iMonsterLoc = AFTJNCTNDECKA;
                          iTempLoc = iMonsterLoc;
                          iTempLoc++;
                          if (iTempLoc > MONSTERTOTAL) iTempLoc = 0;
                          monster_loc-->iTempLoc = AFTJNCTNDECKA;
                      }
                      print "You push the button calling the elevator up to this deck. The ship rubbles
                      around you, the cage shakes, and then with a loud thud, the lift comes to a stop
                      as the vertical doors open.^";
                      return ItemFirstTaken();
                  }
                  "You don't need to call the lift. It's already on this deck.";
          ];

! 01/14/22

  OutRch  -> aftJunctionDeckARoom "room"
    with  name 'room',
          before [;
              Examine:
                  player.advanceGravity = false;
                  "The smoke is too dense to see into the room.";
              Enter, Go:
                  if (alien in aftJunctionDeckA) return PXF();
                  aftJunctionDeckA.firstTime = true;
                  PlayerTo(personalLockerRoom, 2);
                  rtrue;
          ];

! 02/18/22

  StObj   -> logisticsCorridorHandcart "handcart"
    with  name 'handcart' 'cart',
          before [;
              Examine:
                  player.advanceGravity = false;
                  "The handcart is used to move logistics around quickly. On it, some crates of coffee have been left behind.";
              Push, Pull, PushDir:
                  "Moving the cart around won't help you do anything. It's worthless.";
              Take:
                  "The handcart is old and used. No one would buy it.";
          ];

! 02/18/22

  StObj   -> logisticsCorridorCoffee "coffee"
    with  name 'crate' 'crates' 'coffee' 'soot',
          before [;
              Examine:
                  player.advanceGravity = false;
                  "The crates of coffee are old and covered in soot with labels that read ~Weyland Corp.~";
              Take, Open:
                  "The coffee's over 100 years old. It's worthless.";
              Rub:
                  "What? You're going to clean up this old relic before she burns up in the sun? You need to loot the ship.";
          ];
