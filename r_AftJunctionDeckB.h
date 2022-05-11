
! ---------------------------------------------------------------------------- !
!       AFT JUNCTION DECK B. 10/27/21
!
  Room    aftJunctionDeckB "Aft Junction - Deck B"
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
              "The smoke thins towards the back of the ship, but the air is still unbreathable.
              The few lights here are barely lit. It's a wonder that the power has stayed on this
              long.^^This junction shoots off to the port and starboard. It also connects to the
              forward part of the ship.";
          ],
          n_to [;
              if (alien in self) return PXF();
!              print "You walk up the long corridor back to the companionway.^";
              self.firstTime = true;
              return aftCompanionwayDeckB;
          ],
          e_to [;
              if (alien in self) return PXF();
              self.firstTime = true;
              return starboardShuttleBay;
          ],
          w_to [;
              if (alien in self) return PXF();
              self.firstTime = true;
              return portShuttleBay;
          ],
          cant_go [;
              if (alien in self) return PXF();
              "You can go forward, port, or starboard.";
          ],
          before [;
              Exit:

              Listen:

          ],
          roomCount true,
          firstTime true;

! 10/27/21

  RoomObj -> aftJunctionDeckBObj "junction"
    with  name 'junction' 'area' 'place' 'passage' 'tunnel' 'corridor',
          description [;
              <<Look aftJunctionDeckB>>;
          ],
          before [;
              Take, Remove, Turn, PushDir, Push, Pull:
                  "You can't do that to the junction.";
          ];

! 10/27/21

  StObj   aftJunctionDeckBSmoke "smoke"
    with  name 'smoke' 'air' 'haze' 'hazy' 'thin' 'gloom' 'dark' 'cloud' 'smog',
          before [;
              Examine:
                  player.advanceGravity = false;
                  "The smoke thins towards the back part of the ship. So the light cuts through a little more.";
              Enter, Go:
                  "You need to tell me which direction to go in.";
          ],
          found_in aftJunctionDeckB portShuttleBay starboardShuttleBay;
