
! ---------------------------------------------------------------------------- !
!       STARBOARD JUNCTION DECK B. 10/22/21
!
  Room    starboardJunctionDeckB "Starboard Junction - Deck B"
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
              if (self.playerEnterCompanionway) {
                  print "The smoke is dense in this junction and just as thick as the rest of the ship.
                  The lights in this area are out, creating a dark corner as this connection bends around.";
              } else {
                  print "The haze is dense in this junction, making you think the air scrubbers are blown
                  for sure. This ship has coasted through space for a long time. You wonder if the reactor
                  could still be running or, knowing how bad it can get on a vessel this old, leaking.";
              }
              player.inCorridor = true;
              forwardCorridorDeckBAirlock.playerNeverLeavesRoom = false;
              "^^You can go forward towards the airlock or port into the corridor.";
          ],
          n_to [;
              if (alien in self) return PXF();
              self.firstTime = true;
              return forwardCorridorDeckB;
          ],
          w_to [;
              <<Enter starboardJunctionDeckBSmoke>>;
          ],
          cant_go [;
              if (alien in self) return PXF();
              "You can go forward or port.";
          ],
          before [;
              Exit:

              Listen:
                  if (forwardStarboardJunctionDeckC.pipesBlown) "Port, you hear the faint sound of gas venting into the air.";
          ],
          roomCount true,
          firstTime true,
          playerEnterCompanionway false;

! 10/22/21

  RoomObj -> starboardJunctionDeckBObj "junction"
    with  name 'junction' 'area' 'place' 'passage' 'tunnel' 'connection',
          description [;
              <<Look starboardJunctionDeckB>>;
          ],
          before [;
              Take, Remove, Turn, PushDir, Push, Pull:
                  "You can't do that to the junction.";
          ];

! 10/22/21

  OutRch  -> starboardJunctionDeckBAirlock "airlock"
    with  name 'airlock',
          before [;
              Examine:
                  player.advanceGravity = false;
                  "The airlock is forward. You can't see it through the smoke.";
              Go:
                  if (alien in starboardJunctionDeckB) return PXF();
                  starboardJunctionDeckB.firstTime = true;
                  PlayerTo(forwardCorridorDeckB, 2);
                  rtrue;
          ];

! 10/22/21

  OutRch  -> starboardJunctionDeckBSmoke "smoke"
    with  name 'dense' 'smoke' 'haze' 'hazy' 'gloom' 'spin' 'mass',
          before [;
              Examine:
                  player.advanceGravity = false;
                  "Dense smoke spins in a slow labored motion as it drifts into the next corridor.";
              Enter, Go:
                  if (alien in starboardJunctionDeckB) return PXF();
                  starboardJunctionDeckB.firstTime = true;
                  PlayerTo(forwardCompanionwayDeckB, 2);
                  rtrue;
          ];

! 10/23/21

  OutRch  -> starboardJunctionDeckBCorridor "corridor"
    with  name 'corridor',
          before [;
              Examine:
                  player.advanceGravity = false;
                  "You can't see the corridor. Instead, you see the smoke drifting towards it.";
              Enter, Go:
                  if (alien in starboardJunctionDeckB) return PXF();
                  starboardJunctionDeckB.firstTime = true;
                  PlayerTo(forwardCompanionwayDeckB, 2);
                  rtrue;
          ];
