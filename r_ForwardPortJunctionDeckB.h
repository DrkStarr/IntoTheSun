! There is an egg in this room

! The player can mess with it, to the point of opening it up, but the creature is dead inside.

! The queen has a nest in one of the two back wheelwells of the ship. Wheelwells are the places
! where the landing gear is stored during flight. Much like the Claw Chamber, but with no internal
! access. They're sealed in, and there's room to lay eggs.

! The one the PC finds in this corridor she shit out by accident


! There is a collapsed corridor here
! Also, a passageway - passage
! It's set in a Junction

! ---------------------------------------------------------------------------- !
!       FORWARD-PORT JUNCTION DECK B. 12/02/21
!
  Room    forwardPortJunctionDeckB "Forward-Port Junction - Deck B"
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
              print "With cargo brought down from a lift that's port, this corridor becomes a shortcut to the aft portion of B Deck. Smoke hangs stagnant in the air.^^Port, ";
              if (maintenanceLiftDeckB.isGateClosed) print "the vertical doors are closed since the maintenance lift is not on this deck";
              else print "you can barely make out the maintenance lift through the gloom";
              " - starboard, the corridor has collapsed - aft, the smoke shifts heading down another passageway.";
          ],
          e_to [;
              "The corridor starboard has collapsed and is full of debris. Like something slammed into the ship while she floated through space.";
          ],
          w_to [;
              <<Enter forwardPortJunctionDeckBLift>>;
          ],
          s_to [;
              self.firstTime = true;
              return passagewayDeckB;
          ],
          cant_go [;
              if (maintenanceLiftDeckB.isGateClosed) "You can exit aft.";
              "You can go port, or aft.";
          ],
          before [;
              Exit:

              GoIn:
                  <<Enter forwardPortJunctionDeckBLift>>;
              Listen:

          ],
          roomCount true,
          firstTime true;

! 10/24/21

  RoomObj -> forwardPortJunctionDeckBObj "junction"
    with  name 'junction' 'area' 'place' 'section',
          description [;
              <<Look forwardPortJunctionDeckB>>;
          ],
          before [;
              Take, Remove, Turn, PushDir, Push, Pull:
                  "You can't do that to the junction.";
          ];

! 10/24/21

  NoHelp  -> forwardPortJunctionDeckBLift "maintenance lift"
    with  name 'maintenance' 'lift' 'heavy' 'gate' 'elevator' 'cage' 'door' 'vertical',
          before [;
              Examine:
                  player.advanceGravity = false;
                  if (maintenanceLiftDeckB.isGateClosed) "The maintenance lift is hard to see through the smoke, but the two vertical doors give it away. There's a call button here.";
                  "The maintenance lift's vertical doors are open, allowing smoke to trickle into the elevator. Air doesn't circulate through that area, so it's not filled with a lot of smoke.";
              Enter, Go:
                  if (maintenanceLiftDeckB.isGateClosed) "The vertical doors are shut. The lift isn't on this level, but there's a call button on the side.";
                  forwardPortJunctionDeckB.firstTime = true;
                  PlayerTo(maintenanceLiftDeckB, 2);
                  rtrue;
              Close:
                  if (maintenanceLiftDeckB.isGateClosed) "That's already closed.";
                  "You don't need to do that.";
              Open:
                  if (maintenanceLiftDeckB.isGateClosed) <<Push forwardPortJunctionDeckBButton>>;
                  "That's already open.";
          ];

! 03/29/22

  NoHelp  -> forwardPortJunctionDeckBDoors "maintenance lift"
    with  name 'doors',
          before [;
              Examine:
                  <<Examine forwardPortJunctionDeckBLift>>;
              Enter, Go:
                  <<Enter forwardPortJunctionDeckBLift>>;
              Close:
                  <<Close forwardPortJunctionDeckBLift>>;
              Open:
                  <<Open forwardPortJunctionDeckBLift>>;
          ],
    has   pluralname;

! 11/08/21

  StObj   -> forwardPortJunctionDeckBButton "call button"
    with  name 'call' 'button',
          before [;
              Examine:
                  player.advanceGravity = false;
                  "It's a simple button used to call the elevator down to this deck.";
              Push, Pull:
                  if (alien in forwardPortJunctionDeckB) return PXF();
                  if (maintenanceLiftDeckB.isGateClosed) {
                      maintenanceLiftDeckB.isGateClosed = false;
                      maintenanceLiftDeckA.isGateClosed = true;
                      maintenanceLiftDeckADoors.isDoorOpen = false;
                      maintenanceLiftDeckBDoors.isDoorOpen = true;
                      "You push the button calling the elevator down to this deck. The ship rubbles
                      around you, the cage shakes, and then with a loud thud, the lift comes to a stop
                      as the vertical doors open.";
                  }
                  "You don't need to call the lift. It's already on this deck.";
          ];

! 01/05/22

  NoHelp  -> forwardPortJunctionDeckBCorridor "collapsed corridor"
    with  name 'collapsed' 'corridor' 'blocked' 'starboard',
          before [;
              Examine:
                  player.advanceGravity = false;
                  "The corridor starboard is blocked. Like something slammed into the ship while she floated through space.";
              Enter, Go:
                  "You're not getting through that.";
          ];

! 01/16/22

  StObj   -> forwardPortJunctionDeckBDarkness "passageway"
    with  name 'passage' 'passageway',
          before [;
              Examine:
                  player.advanceGravity = false;
                  "Brighter lights lie at the far end of this corridor.";
              Enter, Go:
                  forwardPortJunctionDeckB.firstTime = true;
                  PlayerTo(passagewayDeckB, 2);
                  rtrue;
          ];

! 01/16/22

  Object  forwardPortJunctionDeckBDust "dust pile"
    with  name 'dust' 'pile' 'pod' 'egg' 'husk',
          describe [;
              "^In the middle of this corridor sits a dust pile.";
          ],
          before [;
              Attack:
                  "The pod's not a threat. It's a pile of dust.";
              Climb:
                  "Now that the pod is a pile of dust, there's nothing to climb.";
              Dig:
                  "Now that the pod is a pile of dust, there's nothing to dig.";
              Drink:
                  "Now that the pod is a pile of dust, there's nothing to drink.";
              Eat:
                  "Now that the pod is a pile of dust, there's nothing to eat.";
              Examine, Search:
                  player.advanceGravity = false;
                  "There's a pile of dust where the pod once was.";
              Go:
                  "You are already here.";
              LookUnder:
                  "Now that the pod is a pile of dust, there's nothing to look under.";
              Take:
                  "Now that the pod is a pile of dust, there's not much to take.";
              Touch, Push, Pull, PushDir, Turn, Open, Unlock:
                  "Now that the pod is a pile of dust, there's nothing to play with.";
              Blow:
                  "You can't blow through your suit. The polymer seals in your environment.";
              Attack, Blow, Burn, Climb, Close, Cut, Dig, Drink, Eat, Empty, Enter, Exit, GetOff, Go, GoIn, JumpOver, Kick, Listen, LookUnder, Open:
                  "You need to loot the ship, not mess with ", (the) self, ".";
              Push, PushDir, Pull, Remove, Rub, Search, Set, SetTo, Smell, Squeeze, Swing, SwitchOn, SwitchOff, Take, Talk, Taste, Tie, Touch, Transfer, Turn, Unlock, Wave:
                  "You need to loot the ship, not mess with ", (the) self, ".";
          ];
