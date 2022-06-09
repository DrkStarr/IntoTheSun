
! ---------------------------------------------------------------------------- !
!       CLAW CHAMBER. 11/10/21
!
  Room    clawChamber "Claw Chamber - Deck C"
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
              player.inCorridor = false;
              "The center strut is retracted into a two-deck chamber - its piston leaking oil.
              A skeleton lays in front of it, while one of the square panels that covers the
              deck has been removed. Surrounding you is the rattling sound of chains above,
              but you can't see anything up there through the smoke that pours out the tall
              doors.^^This chamber only houses the center gear. There's little else in the room.
              You can exit forward.";
          ],
          n_to [;
              self.firstTime = true;
              return maintenanceGarage;
          ],
          u_to [;
              "There's no way to get to the upper portion of the claw chamber. Maintenance done
              there is during dry dock. The way out is forward.";
          ],
          cant_go [;
              "You can go forward.";
          ],
          before [;
              Exit:
                  self.firstTime = true;
                  PlayerTo(maintenanceGarage, 2);
                  rtrue;
              Listen:
                  "The sound of chains rattling echo off the bulkheads.";
          ],
          roomCount true,
          firstTime true,
          takenDrone false;

! 11/10/21

  RoomObj -> clawChamberObj "chamber"
    with  name 'area' 'place' 'room',
          description [;
              <<Look clawChamber>>;
          ],
          before [;
              Take, Remove, Turn, PushDir, Push, Pull:
                  "You can't do that to the chamber.";
          ];

! 01/20/22

  StObj   -> clawChamberStrut "strut"
    with  name 'center' 'strut' 'piston' 'oil' 'support' 'gear' 'landing' 'retracted' 'leaking',
          before [;
              Examine:
                  player.advanceGravity = false;
                  "The landing strut is retracted, leaking oil from the piston. The entire thing
                  takes up most this room since the gear is stored away.";
              Climb:
                  "The metal here is smooth and covered in a layer of oil. That would be like climbing a greased pole.";
          ];

! 01/20/22

  OutRch  -> clawChamberChamber "chamber"
    with  name 'two-deck' 'chamber',
          before [;
              Examine:
                  player.advanceGravity = false;
                  "This chamber for the piston takes up B and C deck. It's one of three supports for
                  the vessel. With the other two landing gear only accessible from the ship's exterior.";
          ];

! 01/20/22

  OutRch  -> clawChamberChains "chains"
    with  name 'chains' 'chain',
          before [;
              Examine:
                  player.advanceGravity = false;
                  "You can't see the chains, but you hear them clanging above.";
          ],
     has  pluralname;

! 01/20/22

  StObj   -> clawChamberPlates "panel"
    with  name 'panel' 'square',
          before [;
              Examine:
                  player.advanceGravity = false;
                  "A square panel has been removed from the deck. It's big, giving access to the lowest parts of the ship.";
              Enter, Go:
                  deadflag = 1;
                  "If the alien were in there, you'd never make it back out. But you take the chance anyway, crawling deeper
                  into the ship. You head aft for a short while before being forced to go port for a bit. You become disorientated
                  when you find a junction, going straight down the next passage. Finally, you find the reactor room, wanting to get
                  out of these claustrophobic tunnels.^^You jump out and find large oval eggs all over the place. But before you have
                  time to turn around, the queen strikes. You would've been used as a host if the ship didn't plunge into the sun.";
          ],
     has  pluralname;

! 03/31/22

  StObj   -> clawChamberPanels "panels"
    with  name 'panels',
          before [;
              Examine:
                  <<Examine clawChamberPlates>>;
              Enter, Go:
                  <<Enter clawChamberPlates>>;
          ],
     has  pluralname;

! 01/20/22

  StObj   -> clawChamberSkeleton "skeleton"
    with  name 'skeleton' 'body' 'dead' 'bone' 'decayed' 'spine' 'dust',
          before [;
              Attack:
                  "That's not fair. The skeleton can't even put up a fight.";
              Examine:
                  player.advanceGravity = false;
                  "The bones of the skeleton have fallen away, brittle from age. Now there's
                  only a spine left lying against the piston. A few bones lie around it, but
                  the skull is nowhere to be seen.";
              Go:
                  "You are already here.";
              Attack, Blow, Burn, Climb, Close, Cut, Dig, Drink, Eat, Empty, Enter, Exit, GetOff, Go, GoIn, JumpOver, Kick, Listen, LookUnder, Open:
                  "The skeleton's dead. Leave him be.";
              Push, PushDir, Pull, Remove, Rub, Search, Set, SetTo, Smell, Squeeze, Swing, SwitchOn, SwitchOff, Take, Talk, Taste, Tie, Touch, Transfer, Turn, Unlock, Wave:
                  "The skeleton's dead. Leave him be.";
          ],
          life [;
              "The skeleton's dead. Leave him be.";
          ],
          orders [;
              "The skeleton's dead. Leave him be.";
          ];
!    has   animate male concealed;

! 03/31/22

  StObj   -> clawChamberBones "bones"
    with  name 'bones',
          before [;
              Attack:
                  "That's not fair. The skeleton can't even put up a fight.";
              Examine:
                  player.advanceGravity = false;
                  "Bones lie around the spine that leans against the piston. They're brittle. Some of them have already turned to dust.";
              Go:
                  "You are already here.";
              Attack, Blow, Burn, Climb, Close, Cut, Dig, Drink, Eat, Empty, Enter, Exit, GetOff, Go, GoIn, JumpOver, Kick, Listen, LookUnder, Open:
                  "The skeleton's dead. Leave him be.";
              Push, PushDir, Pull, Remove, Rub, Search, Set, SetTo, Smell, Squeeze, Swing, SwitchOn, SwitchOff, Take, Talk, Taste, Tie, Touch, Transfer, Turn, Unlock, Wave:
                  "The skeleton's dead. Leave him be.";
          ],
          life [;
              "The skeleton's dead. Leave him be.";
          ],
          orders [;
              "The skeleton's dead. Leave him be.";
          ],
    has   pluralname;

! 01/20/22

  StObj   -> clawChamberDoors "doors"
    with  name 'doors' 'tall' 'door',
          before [;
              Examine:
                  player.advanceGravity = false;
                  "The doors are open as smoke pours into the forward chamber.";
              Enter, Go:
                  clawChamber.firstTime = true;
                  PlayerTo(maintenanceGarage, 2);
                  rtrue;
              Open, Pull:
                  "The doors are already open as smoke pours into the forward chamber.";
          ],
     has  pluralname;
