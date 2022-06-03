
! ---------------------------------------------------------------------------- !
!       PORT SHUTTLE BAY. 10/28/21
!
  Room    portShuttleBay "Port Shuttle Bay - Deck B"
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
              if (self.alienWrecked) {
                  "There's no shuttle docked here, but that didn't stop something from trying to
                  get through the airlock. Scratched and dented, the door held against the onslaught
                  and is covered in acid that threatens the ship's integrity.^^Since it's missing the
                  shuttle, you can only exit to the starboard.";
              }
              "The port shuttle bay once held a Starcub Light Intrasystem shuttle, but its engines
              scared the observation window when the lifeboat left the ship. The airlock forward to
              what was once the shuttle is sealed. The smoke in this room thins, but the orange haze
              persists.^^Since it's missing the shuttle, you can only exit to the starboard.";
          ],
          e_to [;
              if (alien in self) return PXF();
              self.firstTime = true;
              return aftJunctionDeckB;
          ],
          cant_go [;
              if (alien in self) return PXF();
              "You can exit starboard.";
          ],
          before [;
              Exit:
                  if (alien in self) return PXF();
                  self.firstTime = true;
                  PlayerTo(aftJunctionDeckB, 2);
                  rtrue;
              Listen:

          ],
          alienWrecked false,
          destroyedYet false,
          takenExtinguisher false,
          roomCount true,
          firstTime true;

! 10/28/21

  RoomObj -> portShuttleBayObj "bay"
    with  name 'bay' 'area' 'place' 'room',
          description [;
              <<Look portShuttleBay>>;
          ],
          before [;
              Take, Remove, Turn, PushDir, Push, Pull:
                  "You can't do that to the bay.";
          ];

! 10/28/21

  StObj   -> portShuttleBayAirlock "airlock"
    with  name 'airlock' 'door',
          before [;
              Examine:
                  player.advanceGravity = false;
                  if (portShuttleBay.alienWrecked) "The airlock's been beaten on, but the alien didn't get very far before spewing acid all over it.";
                  "The airlock door's closed - sealing you in from death in deep space.";
              Enter, Open:
                  if (alien in portShuttleBay) return PXF();
                  if (portShuttleBay.alienWrecked) "The door's covered in acid, and you'd only burn yourself if you tried that.";
                  "The airlock's seal. The shuttle is gone. If you breached the door, you'd be sucked into the cold void.";
              Go:
                  "You are already here.";
              Close:
                  "That's already closed.";
              Attack, Burn, Climb, Close, Cut, Dig, Drink, Eat, Empty, Enter, Exit, GetOff, Go, GoIn, JumpOver, Kick, Listen, LookUnder, Open:
                  if (portShuttleBay.alienWrecked) "The door's covered in acid, and you'd only burn yourself if you tried that.";
                  "You need to loot the ship, not mess with ", (the) self, ".";
              Push, PushDir, Pull, Remove, Rub, Search, Set, SetTo, Smell, Squeeze, Swing, SwitchOn, SwitchOff, Take, Talk, Taste, Tie, Touch, Transfer, Turn, Unlock, Wave:
                  if (portShuttleBay.alienWrecked) "The door's covered in acid, and you'd only burn yourself if you tried that.";
                  "You need to loot the ship, not mess with ", (the) self, ".";
          ];

! 10/28/21

  NotThr  -> portShuttleBayShuttle "shuttle"
    with  name 'shuttle' 'narcissus',
          before [;
              Examine, Enter, Go:
                  player.advanceGravity = false;
                  "The shuttle is gone. At least one person got off the ship.";
          ];

! 03/23/22

  StObj   -> portShuttleBayWindow "observation window"
    with  name 'protective' 'observation' 'window' 'tempered' 'glass' 'soot' 'scar' 'scarring',
          before [;
              Attack:
                  if (portShuttleBay.alienWrecked) "The window has acid on it, and you'd only burn yourself if you tried that.";
                  "The door is damaged and wouldn't hold if you forced it open. You'd end up in deep space.";
              Examine, Search:
                  player.advanceGravity = false;
                  if (portShuttleBay.alienWrecked)
                      "The observation window was covered in soot when the Narcissus left. Now some acid has splashed on it, trying to burn through the metal and risking the integrity of the ship.";
                  "The observation window is used to survey the shuttle from here, but it was covered in soot when the Narcissus departed.";
              Go:
                  "You are already here.";
              Close:
                  "That's already closed.";
              Attack, Burn, Climb, Close, Cut, Dig, Drink, Eat, Empty, Enter, Exit, GetOff, Go, GoIn, JumpOver, Kick, Listen, LookUnder, Open:
                  if (portShuttleBay.alienWrecked) "The window has acid on it, and you'd only burn yourself if you tried that.";
                  "You need to loot the ship, not mess with ", (the) self, ".";
              Push, PushDir, Pull, Remove, Rub, Search, Set, SetTo, Smell, Squeeze, Swing, SwitchOn, SwitchOff, Take, Talk, Taste, Tie, Touch, Transfer, Turn, Unlock, Wave:
                  if (portShuttleBay.alienWrecked) "The window has acid on it, and you'd only burn yourself if you tried that.";
                  "You need to loot the ship, not mess with ", (the) self, ".";
          ];

! 01/05/22

  AcidObj portShuttleBayAcid "acid"
    with  name 'acid' 'pool' 'foam' 'secretion' 'secretions',
          before [;
              Examine, Search:
                  player.advanceGravity = false;
                  if (extinguisher.spitOn) "Acid mixes with the foam from the extinguisher, but that does little to stop it from trying to melt through the deck.";
                  "The acid burns everything it touches, trying to melt all the way through the airlock.";
              Go:
                  "You are already here.";
          ];
