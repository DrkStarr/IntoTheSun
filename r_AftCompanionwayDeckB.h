
! ---------------------------------------------------------------------------- !
!       AFT COMPANIONWAY DECK B. 10/27/21
!
  Room    aftCompanionwayDeckB "Aft Companionway - Deck B"
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
              d_obj.&name-->6 = 'ph023';
              d_obj.&name-->7 = 'ph024';
              player.inCorridor = true;
              "This open space is filled with a thick haze that blankets this area as it slowly rises from
              the opening below. As a result, the dim lights above are choked off by the smoke.
              ^^A ladder in the middle of the companionway will take you to the deck below, two junctions
              lie to port and starboard, and to the aft, a long corridor leads off into the darkness.";
          ],
          s_to [;
              <<Enter aftCompanionwayDeckBDarkness>>;
          ],
          e_to [;
              if (alien in self) return PXF();
              self.firstTime = true;
              return foodLockerCorridorDeckB;
          ],
          w_to [;
              if (alien in self) return PXF();
              self.firstTime = true;
              return passagewayDeckB;
          ],
          u_to [;
              "This is the rear of the ship, and the top deck back here. The ladder well doesn't go any higher.";
          ],
          d_to [;
              <<Enter aftCompanionwayDeckBLadder>>;
          ],
          cant_go [;
              if (alien in self) return PXF();
              "You can go aft, port, starboard, or down.";
          ],
          before [;
              Exit:

              Listen:
                  if (forwardStarboardJunctionDeckC.pipesBlown) "Below you is the faint sound of gas venting into the air.";
          ],
          roomCount true,
          firstTime true;

! 10/27/21

  RoomObj -> aftCompanionwayDeckBObj "companionway"
    with  name 'companionway' 'area' 'room' 'place' 'section',
          description [;
              <<Look aftCompanionwayDeckB>>;
          ],
          before [;
              Take, Remove, Turn, PushDir, Push, Pull:
                  "You can't do that to the companionway.";
              Enter, Go:
                  "You need to give me a direction to go in - aft, port, starboard, or down.";
          ];

! 10/27/21

  StObj   -> aftCompanionwayDeckBLadder "ladder"
    with  name 'ladder' 'well',
          before [;
              Examine:
                  player.advanceGravity = false;
                  "The ladder well gives access to the lower deck of the ship. With it in the middle of the room, it's easy to access.";
              Enter, Go, Climb:
                  if (alien in aftCompanionwayDeckB) return PXF();
                  if (lookmode == 2) print "Carefully you descend to the deck below.^";
                  aftCompanionwayDeckB.firstTime = true;
                  PlayerTo(aftCompanionwayDeckC, 2);
                  rtrue;
          ],
     has  container open;

! 10/27/21

  StObj   -> aftCompanionwayDeckBDarkness "corridor"
    with  name 'darkness' 'corridor',
          before [;
              Examine:
                  player.advanceGravity = false;
                  "The corridor aft falls off into darkness, but it looks like the smoke is letting up down there.";
              Enter, Go:
                  if (alien in aftCompanionwayDeckB) return PXF();
                  aftCompanionwayDeckB.firstTime = true;
                  PlayerTo(aftJunctionDeckB, 2);
                  rtrue;
          ];

! 01/14/22

  StObj   -> aftCompanionwayDeckBJunction "junctions"
    with  name 'junction' 'junctions',
          before [;
              Examine:
                  player.advanceGravity = false;
                  "There are two junctions on either side of you to port and starboard, but you can't see down them since smoke obscures everything.";
              Enter, Go:
                  "They go port and starboard. You need to tell me which direction to go in.";
          ],
     has  pluralname;
