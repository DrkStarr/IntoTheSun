
! ---------------------------------------------------------------------------- !
!       STARBOARD SHUTTLE BAY. 10/27/21
!
  Room    starboardShuttleBay "Starboard Shuttle Bay - Deck B"
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
                  "There's not as much smoke here, but it churns from recent activity. The airlock is
                  dented, scratched, and showered in acid. Like something tried to open it the hard
                  way.^^You can see a shuttle docked out the observation window, but with the acid
                  melting the door, the only exit is port.";
              }
              "The shuttle bay is a round room with an airlock on the forward end. There's not as
              much smoke in this section, but there's a lot of haze. Looking through the observation
              window, you see a shuttle that holds four.^^The airlock's been beaten on and is damaged.
              The only exit is port.";
          ],
          n_to [;
              <<Enter starboardShuttleBayAirlock>>;
          ],
          w_to [;
              if (alien in self) return PXF();
              self.firstTime = true;
              return aftJunctionDeckB;
          ],
          cant_go [;
              if (alien in self) return PXF();
              "You can exit port.";
          ],
          before [;
              Exit:
                  if (alien in self) return PXF();
                  self.firstTime = true;
                  PlayerTo(aftJunctionDeckB, 2);
                  rtrue;
              Listen:

          ],
          destroyedYet false,
          alienWrecked false,
          takenSuit false,
          roomCount true,
          firstTime true;

! 10/27/21

  RoomObj -> starboardShuttleBayObj "bay"
    with  name 'bay' 'area' 'place' 'room',
          description [;
              <<Look starboardShuttleBay>>;
          ],
          before [;
              Take, Remove, Turn, PushDir, Push, Pull:
                  "You can't do that to the bay.";
          ];

! 10/27/21

  StObj   -> starboardShuttleBayAirlock "airlock"
    with  name 'airlock' 'door' 'damage' 'damaged',
          before [;
              Attack:
                  if (starboardShuttleBay.alienWrecked) return PCinA();
                  "The door is damaged and wouldn't hold if you forced it open. You'd end up in deep space.";
              Examine:
                  player.advanceGravity = false;
                  if (starboardShuttleBay.alienWrecked)
                      "It held up well during the second beating for a door already damaged. But the alien spewed acid on it. Now it's weak under pressure.";
                  "The airlock's dented from something beating on it, trying to get to the shuttle. But the door held under pressure.";
              Go:
                  "You are already here.";
              Attack, Enter, Open, Unlock:
                  if (alien in starboardShuttleBay) return PXF();
                  if (starboardShuttleBay.alienWrecked) return PCinA();
                  "The door's damaged and wouldn't hold if you forced it open. You'd end up in deep space.";
              Close:
                  "That's already closed.";
              Attack, Burn, Climb, Close, Cut, Dig, Drink, Eat, Empty, Enter, Exit, GetOff, Go, GoIn, JumpOver, Kick, Listen, LookUnder, Open:
                  if (starboardShuttleBay.alienWrecked) return PCinA();
                  return PNL();
              Push, PushDir, Pull, Remove, Rub, Search, Set, SetTo, Smell, Squeeze, Swing, SwitchOn, SwitchOff, Take, Talk, Taste, Tie, Touch, Transfer, Turn, Unlock, Wave:
                  if (starboardShuttleBay.alienWrecked) return PCinA();
                  return PNL();
          ];

! 03/23/22

  StObj   -> starboardShuttleBayWindow "observation window"
    with  name 'protective' 'observation' 'window' 'tempered' 'glass',
          before [;
              Attack:
                  if (starboardShuttleBay.alienWrecked) return PWA();
                  "You could lay into the window, taking out your aggression, but you'd end up in deep space if it broke.";
              Examine:
                  player.advanceGravity = false;
                  if (starboardShuttleBay.alienWrecked)
                      "You can still see the shuttle through the window, but some acid has splashed upon the tempered glass, trying to burn through.";
                  "The observation window gives you a detailed view of the shuttle docked outside. The name reads Salmacis.";
              Search:
                  if (starboardShuttleBay.alienWrecked)
                      "You can still see the shuttle through the window, but some acid has splashed upon the tempered glass, trying to burn through.";
                  "The view out the window is blocked by the shuttle docked here. However, you can see the ship's name: Salmacis.";
              Go:
                  "You are already here.";
              Close:
                  "That's already closed.";
              Attack, Burn, Climb, Close, Cut, Dig, Drink, Eat, Empty, Enter, Exit, GetOff, Go, GoIn, JumpOver, Kick, Listen, LookUnder, Open:
                  if (starboardShuttleBay.alienWrecked) return PWA();
                  return PNL();
              Push, PushDir, Pull, Remove, Rub, Search, Set, SetTo, Smell, Squeeze, Swing, SwitchOn, SwitchOff, Take, Talk, Taste, Tie, Touch, Transfer, Turn, Unlock, Wave:
                  if (starboardShuttleBay.alienWrecked) return PWA();
                  return PNL();
          ];

! 10/27/21

  OutRch  -> starboardShuttleBayShuttle "shuttle"
    with  name 'shuttle' 'salmacis',
          before [;
              Examine:
                  player.advanceGravity = false;
                  "The shuttle will accommodate four people. Since the ship is crewed by seven, that's the reason the vessel is equipped with two of them.";
              Enter:
                  if (alien in starboardShuttleBay) return PXF();
                  "It's on the other side of the door, and won't have anything of value in it like this vessel does.";
              Close:
                  "That's already closed.";
          ];

! 01/05/22

  AcidObj starboardShuttleBayAcid "acid"
    with  name 'acid' 'pool' 'secretion' 'secretions',
          before [;
              Examine, Search:
                  player.advanceGravity = false;
                  "The acid burns everything it touches, trying to melt all the way through the airlock.";
              Go:
                  "You are already here.";
          ];

  [ PWA;
        "The window has acid on it, and you'd only burn yourself if you tried that.";
  ];

  [ PCinA;
        "The door's covered in acid, and you'd only burn yourself if you tried that.";
  ];
