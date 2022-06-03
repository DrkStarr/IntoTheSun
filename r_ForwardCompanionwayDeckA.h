! Used, with the seal broken.
! ---------------------------------------------------------------------------- !
!       FORWARD COMPANIONWAY DECK A. 10/31/21
!
  Room    forwardCompanionwayDeckA "Forward Companionway - Deck A"
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
              print "The smoke up here barely moves, with LEDs giving off a faint glow. This companionway
              is a hub with rooms in all directions";
              if (forwardCompanionwayDeckACanister in self)
                  print ", but in the middle, a coolant canister has been left behind";
              ".^^There's a ladder well that sits in the middle of the companionway. Two rooms lie to port
              and starboard, and a corridor lies aft. While forward, you can go deeper into the derelict.";
          ],
          n_to [;
              if (alien in self) return PXF();
              self.firstTime = true;
              return galley;
          ],
          s_to [;
              if (alien in self) return PXF();
              self.firstTime = true;
              return aftJunctionDeckA;
          ],
          e_to [;
              if (alien in self) return PXF();
              self.firstTime = true;
              return hypersleepVault;
          ],
          w_to [;
              if (alien in self) return PXF();
              self.firstTime = true;
              return infirmary;
          ],
          u_to [;
              "You're already on the top deck.";
          ],
          d_to [;
              <<Enter forwardCompanionwayDeckALadder>>;
          ],
          cant_go [;
              if (alien in self) return PXF();
              "You can go forward, aft, port, starboard, or down.";
          ],
          before [;
              Exit:

              Listen:
                  if (forwardStarboardJunctionDeckC.pipesBlown) "Below you is the faint sound of gas venting into the air.";
          ],
          roomCount true,
          firstTime true;

! 10/31/21

  RoomObj -> forwardCompanionwayDeckAObj "companionway"
    with  name 'companionway' 'area' 'room' 'place' 'section',
          description [;
              <<Look forwardCompanionwayDeckA>>;
          ],
          before [;
              Take, Remove, Turn, PushDir, Push, Pull:
                  "You can't do that to the companionway.";
              Enter, Go:
                  "You need to give me a direction to go in - forward, aft, port, starboard, or down.";
          ];

! 10/31/21

  StObj   -> forwardCompanionwayDeckALadder "ladder"
    with  name 'ladder' 'well',
          before [;
              Examine:
                  player.advanceGravity = false;
                  "The ladder well gives access to the lower decks of the ship. With it in the middle of the room, it's easy to access.";
              Enter, Go, Climb:
                  if (alien in forwardCompanionwayDeckA) return PXF();
                  if (lookmode == 2) print "Carefully you descend to the deck below.^";
                  forwardCompanionwayDeckA.firstTime = true;
                  PlayerTo(forwardCompanionwayDeckB, 2);
                  rtrue;
          ],
     has  container open;

! 01/14/22

  OutRch  -> forwardCompanionwayDeckACorridor "corridor"
    with  name 'corridor',
          before [;
              Examine:
                  player.advanceGravity = false;
                  "Smoke fills the aft corridor, just like the rest of the ship.";
              Enter, Go:
                  if (alien in forwardCompanionwayDeckA) return PXF();
                  forwardCompanionwayDeckA.firstTime = true;
                  PlayerTo(aftJunctionDeckA, 2);
                  rtrue;
          ];

! 03/25/22

  StObj   -> forwardCompanionwayDeckACanister "coolant canister"
    with  name 'coolant' 'canister' 'large' 'cylinder' 'seal' 'hole',
          before [ iTempLoc;
              Examine:
                  player.advanceGravity = false;
                  if (self in forwardCompanionwayDeckC) "The coolant canister slammed into the deck and found a hole in the metal grating, getting stuck in the spit-on deck.";
                  "The coolant canister is a large cylinder, like a scuba tank, that holds liquid nitrogen under pressure. But the seal is broken - the canister used.";
              Take, Pull:
                  if (self in forwardCompanionwayDeckC)
                      "The canister lodge itself into the deck. You can't pull it out.";
                  if (self.triedToTake) "The seal is broken. The canister is empty and worthless.";
                  self.triedToTake = true;
                  "The seal is broken. The canister is empty and worthless. But it might be used for something else.";
              Push:
                  if (self in forwardCompanionwayDeckC) "That's not going to help. You're wasting your time down here.";
                  if (alien.sleeping) "That would make a lot of noise if you pushed it into the ladder well. It's best you don't disturb the ship.";
                  move self to forwardCompanionwayDeckC;
                  print "Grabbing the canister by the edge, you push it into the ladder well";
                  if (forwardStarboardJunctionDeckC.pipesBlown) ", but fail to hear it crash into the deck. The sound of venting gas from below is too loud.";
                  iMonsterDestination = FWDCOMPDECKC;
                  iTempLoc = iMonsterLoc;
                  iTempLoc++;
                  if (iTempLoc > MONSTERTOTAL) iTempLoc = 0;
                  monster_loc-->iTempLoc = FWDCOMPDECKC;
                  ". It bounces off metal a few times on the way down before hitting bottom. That should attract the xenomorph to the lowest parts of the ship.";
              Open:
                  "At the top of the canister, the seal's cracked. The gas has already been vented.";
          ],
          triedToTake false;
