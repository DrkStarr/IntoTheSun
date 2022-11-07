
! ---------------------------------------------------------------------------- !
!       FORWARD-STARBOARD JUNCTION DECK C. 10/30/21
!
  Room    forwardStarboardJunctionDeckC "Forward-Starboard Junction - Deck C"
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
              if (self.advanceTrigger) {
                  self.advanceTrigger = false;
                  iPipesBlown++;
              }
              print "The smoke slowly stirs in the air down here, being drawn into the companionway that's port.
              The lights try to cut through the haze with little effect.^^Pipes run along the bulkhead as
              they come around here, starting at the port end and turning aft. ";
              if (iPipesBlown>2) "When you get near the pipes, you hear them cry.";
              if (iPipesBlown>1) "When you get near the pipes, you hear them moan.";
              "When you get near the pipes, you hear them creak.";
          ],
          s_to [;
              if (alien in self) return PXF();
              self.firstTime = true;
              self.advanceTrigger = true;
              return aftStarboardJunctionDeckC;
          ],
          w_to [;
              if (alien in self) return PXF();
              self.firstTime = true;
              self.advanceTrigger = true;
              return forwardCompanionwayDeckC;
          ],
          cant_go [;
              if (alien in self) return PXF();
              "You can go aft or port.";
          ],
          before [;
              Exit:

              Listen:

	  ],
      roomCount true,
	  firstTime true,
      advanceTrigger true,
      pipesBlown false;

! 10/30/21

  RoomObj -> forwardStarboardJunctionDeckCObj "junction"
    with  name 'junction' 'area' 'passage' 'corridor' 'place',
          description [;
	            <<Look forwardStarboardJunctionDeckC>>;
          ],
          before [;
	      Take, Remove, Turn, PushDir, Push, Pull:
                  "You can't do that to the junction.";
          ];

! 10/30/21

  StObj   -> frwrdStrbrdJunctionDeckCPipes "pipes"
    with  name 'pipe' 'pipes' 'coolant' 'metal' 'flakes' 'flake',
          before [;
              Attack:
                  if (alien.sleeping) "That would make a lot of noise. It's best you don't disturb the ship.";
                  "You don't want to bang on the pipes? They're already old, and couldn't stand the beating.";
              Examine:
                  player.advanceGravity = false;
                  "Coolant pipes run throughout the lower deck of the ship. The ones at this junction are old,
                  covered in dust, with metal flaking away. They're tied into the reactor and used as part of
                  a heat exchange.";
              Push, Pull:
                  if (forwardStarboardJunctionDeckC.pipesBlown) "The pipes might be under pressure. You don't want to do that.";
                  "The pipes are under pressure. You don't want to do that.";
              Rub:
                  "They're dirty, but you don't have time to clean the ship. You need to loot her before you're crushed by the pressure from the sun.";
          ],
     has  pluralname;
