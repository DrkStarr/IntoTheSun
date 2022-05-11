
! ---------------------------------------------------------------------------- !
!       FORWARD-STARBOARD JUNCTION DECK B. 10/25/21
!
  Room    forwardStarboardJunctionDeckB "Forward-Starboard Junction - Deck B"
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
              "There was once a corridor to port, but it's now full of metal and debris. Something must
              have hit this ship. So smoke stagnates here even though there's another room to starboard.^
              ^The junction comes to an end here. You can go starboard into a hatch that's already open
              or aft towards the food locker.";
          ],
          s_to [;
              if (alien in self) return PXF();
              self.firstTime = true;
              return foodLockerCorridorDeckB;
          ],
          e_to [;
              if (alien in self) return PXF();
              self.firstTime = true;
              return crewLounge;
          ],
          w_to [;
              "The corridor port has collapsed and is full of debris. Like something slammed into the ship while she floated through space.";
          ],
          cant_go [;
              if (alien in self) return PXF();
              "You can go aft or starboard.";
          ],
          before [;
              Exit:
                  if (alien in self) return PXF();
                  self.firstTime = true;
                  PlayerTo(foodLockerCorridorDeckB, 2);
                  rtrue;
              Listen:

              GoIn:
                  if (alien in self) return PXF();
                  self.firstTime = true;
                  PlayerTo(crewLounge, 2);
                  rtrue;
          ],
          roomCount true,
          firstTime true;

! 10/25/21

  RoomObj -> forwardStarboardJunctionDeckBObj "junction"
    with  name 'junction' 'area' 'passage' 'place',
          description [;
              <<Look forwardStarboardJunctionDeckB>>;
          ],
          before [;
              Take, Remove, Turn, PushDir, Push, Pull:
                  "You can't do that to the junction.";
          ];

! 01/05/22

  NoHelp  -> forwardStarboardJunctnDckBCrrdr "collapsed corridor"
    with  name 'collapsed' 'corridor' 'blocked' 'port',
          before [;
              Examine:
                  player.advanceGravity = false;
                  "The corridor port is blocked. Like something slammed into the ship while she floated through space.";
              Enter, Go:
                  "You're not getting through that.";
          ];

! 01/15/22

  StObj   -> forwardStarboardJunctnDckBHatch "hatch"
    with  name 'hatch' 'hinge' 'hinges' 'door',
          before [;
              Examine:
                  player.advanceGravity = false;
                  if (alien in crewLounge) "Is there something shifting in the smoke behind the hatch? It's hard to tell.";
                  "The hatch has been left open, allowing anything to enter the room.";
              Enter:
                  if (alien in forwardStarboardJunctionDeckB) return PXF();
                  forwardStarboardJunctionDeckB.firstTime = true;
                  PlayerTo(crewLounge, 2);
                  rtrue;
              Go:
                  "You are already here.";
              Open:
                  "That's already open.";
              Take:
                  "The hatch isn't easily coming off its hinges, and it's worthless.";
          ];
