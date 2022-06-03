
! ---------------------------------------------------------------------------- !
!       FORWARD COMPANIONWAY DECK C. 10/28/21
!
  Room    forwardCompanionwayDeckC "Forward Companionway - Deck C"
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
              d_obj.&name-->6 = 'water';
              d_obj.&name-->7 = 'liquid';
              if (forwardStarboardJunctionDeckC.pipesBlown) {
                  print "The smoke here churns along with hot steam from the broken pipes venting gas into
                  the underbelly of the ship. There are not a lot of lights, but you can see the garage
                  door aft is open, though full of so much smoke you can't see inside.";
                  if (forwardCompanionwayDeckACanister in self)print " A coolant canister is lodged in the deck.";
                  "^^You can enter the garage or climb the ladder well to go to B deck.";
              }
              print "It's hard to see in the underbelly of the ship. There are few lights and lots of smoke. Electric
              scarring on the overload module can be seen. It took a huge power spike. The garage door aft is open but full
              of so much smoke you can't see inside.";
              if (forwardCompanionwayDeckACanister in self)print " A coolant canister is lodged in the deck.";
              print"^^The corridor runs starboard. Aft, you can enter the garage or climb the ladder well to go to B deck";
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
                  print ".^^You jump at the loud explosion to starboard. It rings out through the ship as one of the
                  pipes in the junction blows. Hot steam from the reactor pours out of broken metal, blocking
                  off the starboard corridor";
                  iMonsterDestination = FWDJUNDECKC;
                  iTempLoc = iMonsterLoc;
                  iTempLoc++;
                  if (iTempLoc > MONSTERTOTAL) iTempLoc = 0;
                  monster_loc-->iTempLoc = FWDJUNDECKC;
                  if (alien.sleeping) {
                      print ".^^";
                      return ItemWake();
                  }
                  if (AlienAboveCDeck()) {
                      ". From above you, a high pitch scream cries out.";
                  }
              }
              ".";
          ],
          s_to [;
              if (alien in self) return PXF();
              self.firstTime = true;
              return maintenanceGarage;
          ],
          e_to [;
              if (alien in self) return PXF();
              if (forwardStarboardJunctionDeckC.pipesBlown) "The starboard junction is full of hot gas that vents from the reactor. You're going to have to find another way around.";
              self.firstTime = true;
              return forwardStarboardJunctionDeckC;
          ],
          w_to [;
              "The corridor port has collapsed and is full of debris. Like something slammed into the ship while she floated through space.";
          ],
          u_to [;
              <<Enter forwardCompanionwayDeckCLadder>>;
          ],
          d_to [;
              "You're already on the bottom deck.";
          ],
          cant_go [;
              if (alien in self) return PXF();
              "You can go aft, starboard, or up.";
          ],
          before [;
              Exit:

              GoIn:
                  if (alien in self) return PXF();
                  self.firstTime = true;
                  PlayerTo(maintenanceGarage, 2);
                  rtrue;
              Listen:
                  if (forwardStarboardJunctionDeckC.pipesBlown) "Next to you, loud gas venting into the air howls through the ship.";
	  ],
          roomCount true,
	  firstTime true;

! 10/28/21

  RoomObj -> forwardCompanionwayDeckCObj "companionway"
    with  name 'companionway' 'area' 'room' 'place',
          description [;
	      <<Look forwardCompanionwayDeckC>>;
          ],
          before [;
	      Take, Remove, Turn, PushDir, Push, Pull:
                  "You can't do that to the companionway.";
              Enter, Go:
                  "You need to give me a direction to go in - aft, starboard, or up.";
          ];

! 10/28/21

  OutRch  -> forwardCompanionwayDeckCOpening "opening"
    with  name 'opening',
          before [;
              Examine:
                  player.advanceGravity = false;
		  "There's an opening here. The smoke slowly drifts up it.";
	      Enter, Go:
                  <<Enter forwardCompanionwayDeckCLadder>>;
          ];

! 10/28/21

  StObj   -> forwardCompanionwayDeckCLadder "ladder"
    with  name 'ladder' 'well',
          before [;
              Examine:
                  player.advanceGravity = false;
		  "The ladder well gives access to the upper decks of the ship. With it in the middle of the room, it's easy to access.";
              Enter, Go, Climb:
                  if (alien in forwardCompanionwayDeckC) return PXF();
                  if (lookmode == 2) print "Slowly you climb up the ladder well.^";
                  forwardCompanionwayDeckC.firstTime = true;
                  PlayerTo(forwardCompanionwayDeckB, 2);
                  rtrue;
          ];

! 01/05/22

  NoHelp  -> forwardCmpnnwyDckCCllpsdCrrdr "collapsed corridor"
    with  name 'collapsed' 'corridor' 'blocked' 'port',
          before [;
              Examine:
                  player.advanceGravity = false;
		  "The corridor port is blocked. Like something slammed into the ship while she floated through space.";
              Enter, Go:
                  "You're not getting through that.";
          ];

! 01/18/22

  StObj   -> forwardCompanionwayDeckCGarage "garage"
    with  name 'garage' 'door' 'large',
          before [;
              Examine, Search:
                  player.advanceGravity = false;
		  "A large garage door sits aft - open. The smoke is thick inside, like it's coming from that room, and you can't make anything out.";
              Open:
                  "That's already open.";
              Enter, Go:
                  if (alien in forwardCompanionwayDeckC) return PXF();
                  forwardCompanionwayDeckC.firstTime = true;
                  PlayerTo(maintenanceGarage, 2);
                  rtrue;
          ];

! 02/21/22

  StObj   -> forwardCompanionwayDeckCPipes "pipes"
    with  name 'pipe' 'pipes' 'coolant' 'ph018' 'ph019' 'ph020' 'ph021' 'ph022' 'junction',
          before [;
              Attack:
                  if (forwardStarboardJunctionDeckC.pipesBlown)
                      "The pipes are hot as gas floods the junction. You'd burn yourself if you did that.";
                  if (alien.sleeping) "That would make a lot of noise. It's best you don't disturb the ship.";
                  "What are you trying to do? Call the xenomorph down here?";
              Examine:
                  player.advanceGravity = false;
                  if (forwardStarboardJunctionDeckC.pipesBlown)
                      "The pipes are broken with hot steam flooding the starboard junction. You're going to have to find another way around.";
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

! 03/09/22

  StObj   -> forwardCompanionwayDeckCModule "overload module"
    with  name 'overload' 'module' 'burned'  'burn' 'scarring' 'scar' 'black',
          before [;
              Attack:
                  "It is fused shut. Beating on it isn't going to open it.";
              Examine, Search:
                  player.advanceGravity = false;
		  "The overload module is recessed into the forward bulkhead. Energy is regulated here
                  when the ship is running using the device much like a fuse. But due to a power spike,
                  the whole thing blew, charring the outside of it in black.";
              Open:
                  "The module fused shut when the electric spike passed through it. There's no way to open it.";
              Take:
                  "Electricity fused the overload module in place. It is burnt out, sealed shut, and worthless.";
              Push, Pull, PushDir, Unlock:
                  "Electricity fused the overload module in place. There's no way to get at it. It's burnt out and sealed shut.";
          ];
