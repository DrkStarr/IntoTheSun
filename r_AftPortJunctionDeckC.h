
! ---------------------------------------------------------------------------- !
!       AFT-PORT JUNCTION DECK C. 10/30/21
!
  Room    aftPortJunctionDeckC "Aft-Port Junction - Deck C"
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
              "A thick blanket of smoke hangs in this corner of the ship due to the collapsed corridor that's
              forward. The smoke's not moving. Instead, it's stagnant in this section of the tunnel, chocking
              off the light.^^Pipes run along the junction as it bends around, ending at a collapsed corridor.
              You can exit to starboard.";
          ],
          n_to [;
              "The corridor forward has collapsed and is full of debris. Like something slammed into the
              ship while she floated through space.";
          ],
          e_to [;
              if (alien in self) return PXF();
              self.firstTime = true;
              return aftCompanionwayDeckC;
          ],
          cant_go [;
              if (alien in self) return PXF();
              "You can exit starboard.";
          ],
          before [;
              Exit:
                  if (alien in self) return PXF();
                  self.firstTime = true;
                  PlayerTo(aftCompanionwayDeckC, 2);
                  rtrue;
              Listen:
                  if (forwardStarboardJunctionDeckC.pipesBlown) "Starboard, you hear the faint sound of gas venting into the air.";
          ],
          takenExtinguisher false,
          roomCount true,
          firstTime true;

! 10/30/21

  RoomObj -> aftPortJunctionDeckCObj "junction"
    with  name 'junction' 'area' 'passage' 'tunnel' 'place',
          description [;
              <<Look aftPortJunctionDeckC>>;
          ],
          before [;
              Take, Remove, Turn, PushDir, Push, Pull:
                  "You can't do that to the junction.";
          ];

! 01/05/22

  NoHelp  -> aftPortJunctionDeckCCorridor "collapsed corridor"
    with  name 'collapsed' 'corridor' 'blocked' 'forward',
          before [;
              Examine:
                  player.advanceGravity = false;
                  "The corridor forward is blocked. Like something slammed into the ship while she floated through space.";
              Enter, Go:
                  "You're not getting through that.";
          ];

! 10/30/21

  StObj   -> aftPortJunctionDeckCPipes "pipes"
    with  name 'pipe' 'pipes' 'coolant',
          before [;
              Attack:
                  if (alien.sleeping) "That would make a lot of noise. It's best you don't disturb the ship.";
                  "What are you trying to do? Call the xenomorph down here?";
              Examine:
                  player.advanceGravity = false;
                  "Coolant pipes run throughout the lower deck of the ship. Tied into the reactor,
                  they're used as part of a heat exchange.";
              Push, Pull:
                  if (forwardStarboardJunctionDeckC.pipesBlown) "The pipes might be under pressure. You don't want to do that.";
                  "The pipes are under pressure. You don't want to do that.";
              Enter, Go:
                  "You need to tell me which direction to go in.";
          ],
     has  pluralname;
