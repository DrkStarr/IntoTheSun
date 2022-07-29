
! ---------------------------------------------------------------------------- !
!       AFT-STARBOARD JUNCTION DECK C. 10/30/21
!
  Room    aftStarboardJunctionDeckC "Aft-Starboard Junction - Deck C"
   with   description [ iTempLoc;
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
              if (forwardStarboardJunctionDeckC.pipesBlown)
                  "The thick smoke down here swirls and churns with the hot gas pouring out of a pipe.
                  The lights flicker. In the corner, some welding equipment is stored out of the way.^^The
                  forward corridor is full of hot steam from a broken pipe that vents gas from the
                  reactor room. You can go port to the companionway.";
              print "The smoke is thick because the air's not moving. The lights flicker, barely cutting through
              the haze. In the corner, some welding equipment is stored out of the way.^^Coolant pipes run along
              this junction, starting at the forward end and turning port";
              if (iPipesBlown > BLOWN_PIPES) {
                  aftStarboardJunctionDeckCPipes.&name-->3 = 'hot';
                  aftStarboardJunctionDeckCPipes.&name-->4 = 'gas';
                  aftStarboardJunctionDeckCPipes.&name-->5 = 'steam';
                  aftStarboardJunctionDeckCPipes.&name-->6 = 'broken';
                  aftStarboardJunctionDeckCPipes.&name-->7 = 'metal';
                  forwardCompanionwayDeckCPipes.&name-->3 = 'hot';
                  forwardCompanionwayDeckCPipes.&name-->4 = 'gas';
                  forwardCompanionwayDeckCPipes.&name-->5 = 'steam';
                  forwardCompanionwayDeckCPipes.&name-->6 = 'broken';
                  forwardCompanionwayDeckCPipes.&name-->7 = 'metal';
                  forwardStarboardJunctionDeckC.pipesBlown = true;
                  print ".^^You jump at the loud explosion behind you. It rings out through the ship as one of the
                  pipes in the junction blows. Hot steam from the reactor pours out of the broken metal, blocking
                  off the forward corridor";
                  iMonsterDestination = FWDJUNDECKC;
                  iTempLoc = iMonsterLoc;
                  iTempLoc++;
                  if (iTempLoc > MONSTERTOTAL) iTempLoc = 0;
                  monster_loc-->iTempLoc = FWDJUNDECKC;
                  if (alien.sleeping) {
                      print ".^^";
                      return ItemWake();
                  }
                  if (AlienOnBDeck()) {
                      ". From above you, a high pitch scream cries out.";
                  }
              }
              ".";
          ],
          n_to [;
              if (alien in self) return PXF();
              if (forwardStarboardJunctionDeckC.pipesBlown) "The forward junction is full of hot gas that vents from the reactor. You're going to have to find another way around.";
              self.firstTime = true;
              return forwardStarboardJunctionDeckC;
          ],
          w_to [;
              if (alien in self) return PXF();
              self.firstTime = true;
              return aftCompanionwayDeckC;
          ],
          cant_go [;
              if (alien in self) return PXF();
              "You can go forward or port.";
          ],
          before [;
              Exit:

              Listen:
                  if (forwardStarboardJunctionDeckC.pipesBlown) "Towards the front, loud gas venting into the air howls through the ship.";

          ],
          takenExtinguisher false,
          roomCount true,
          firstTime true;

! 10/30/21

  RoomObj -> aftStarboardJunctionDeckCObj "junction"
    with  name 'junction' 'area' 'passage' 'corridor' 'tunnel' 'place' 'corner',
          description [;
              <<Look aftStarboardJunctionDeckC>>;
          ],
          before [;
              Take, Remove, Turn, PushDir, Push, Pull:
                  "You can't do that to the junction.";
          ];

! 02/19/22

  StObj   -> aftStarboardJunctionDeckCWelder "welding equipment"
    with  name 'welding' 'equipment' 'cold' 'laser' 'welder',
          before [;
              Attack:
                  if (alien.sleeping) "That would make a lot of noise. It's best you don't disturb the ship.";
                  "That would only make a lot of noise. What are you trying to do? Attract the xenomorph?";
              Examine:
                  player.advanceGravity = false;
                  "It's a laser welder that gets its power from the large battery next to it. Engineering uses
                  it sparingly on the ship, but it does fire a cold laser when activated.";
              Push, Pull, PushDir:
                  "You don't need to use the equipment. It can stay right there.";
              Take:
                  "It's larger than the bag and wouldn't fit.";
              SwitchOn:
                  "You don't need to weld anything. You need to loot the ship.";
              SwitchOff:
                  "The equipment is already off.";
          ];

! 03/12/22

  StObj   -> aftStarboardJunctionDeckCBattery "large battery"
    with  name 'large' 'battery',
          before [;
              Attack:
                  if (alien.sleeping) "That would make a lot of noise. It's best you don't disturb the ship.";
                  "That would only make a lot of noise. What are you trying to do? Attract the xenomorph?";
              Examine:
                  player.advanceGravity = false;
                  "This large battery, designed to hold a charge for decades, stands as tall as the corridor.
                  Tied into the welder, it powers the cold laser.";
              Push, Pull, PushDir:
                  "You don't need to use the equipment. It can stay right there.";
              Take:
                  "It's larger than the bag and wouldn't fit.";
              SwitchOn:
                  "You don't need to weld anything. You need to loot the ship.";
              SwitchOff:
                  "The equipment is already off.";
          ];

! 10/30/21

  StObj   -> aftStarboardJunctionDeckCPipes "pipes"
    with  name 'pipe' 'pipes' 'coolant' 'ph018' 'ph019' 'ph020' 'ph021' 'ph022',
          before [;
              Attack:
                  if (forwardStarboardJunctionDeckC.pipesBlown)
                      "The pipes are hot as gas floods the junction. You'd burn yourself if you did that.";
                  if (alien.sleeping) "That would make a lot of noise. It's best you don't disturb the ship.";
                  "What are you trying to do? Call the xenomorph down here?";
              Examine:
                  player.advanceGravity = false;
                  if (forwardStarboardJunctionDeckC.pipesBlown)
                      "The pipes are broken with hot steam flooding the forward junction. You're going to have to find another way around.";
                  "Coolant pipes run throughout the lower deck of the ship. Tied into the reactor,
                  they're used as part of a heat exchange.";
              Push, Pull:
                  if (forwardStarboardJunctionDeckC.pipesBlown)
                      "The pipes are hot as gas floods the junction. You'd burn yourself if you did that.";
                  "The pipes are under pressure. You don't want to do that.";
              Enter, Go:
                  "You need to tell me which direction to go in.";
          ],
     has  pluralname;
