
! ---------------------------------------------------------------------------- !
!       CREW LOUNGE. 11/30/21
!
  Room    crewLounge "Crew Lounge - Deck B"
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
                  "Smoke has filled this room, and there's little light. The couch that wraps the bulkheads
                  is torn into and spit on with acid. The corrosive material eats through the sofa as it melts
                  like a popsicle.^^With a couch wrapped around most of the room, you can only exit to port.";
              }
              "With the hatch left open, smoke has filled this place. It's a circular room lined with a
              couch wrapped around the bulkheads. This lounge is where the crew gathers to listen to music
              on the rare occasion that they're not in hypersleep.^^With a couch wrapped around most of the
              room, you can only exit to port.";
          ],
          w_to [;
              if (alien in self) return PXF();
              self.firstTime = true;
              return forwardStarboardJunctionDeckB;
          ],
          cant_go [;
              if (alien in self) return PXF();
              "You can exit port.";
          ],
          before [;
              Exit:
                  if (alien in self) return PXF();
                  self.firstTime = true;
                  PlayerTo(forwardStarboardJunctionDeckB, 2);
                  rtrue;
              Listen:

              SitRoom:
                  <<Enter crewLoungeCouch>>;
          ],
          takenMusicBox false,
          alienWrecked false,
          destroyedYet false,
          roomCount true,
          firstTime true;

! 11/30/21

  RoomObj -> crewLoungeObj "lounge"
    with  name 'lounge' 'area' 'place' 'room' 'section' 'chamber',
          description [;
              <<Look crewLounge>>;
          ],
          before [;
              Take, Remove, Turn, PushDir, Push, Pull:
                  "You can't do that to the lounge.";
          ];

! 12/09/21

  NHSeen  -> crewLoungeStand "disk"
    with  name 'stand' 'pedestal' 'base' 'disk' 'round' 'table',
          describe [;
              if (crewLounge.alienWrecked) {
                  if (musicBox in self) "^A disk melts in a pool of acid, along with a music box, in the middle of the lounge.";
                  "^A disk melts in a pool of acid in the middle of the lounge.";
              }
              if (musicBox in self) "^A disk hovers in the middle of the lounge. On top of it, a music box has been left out.";
              "^A disk hovers in the middle of the lounge.";
          ],
          before [;
              Examine:
                  player.advanceGravity = false;
                  if (crewLounge.alienWrecked)
                      "When the alien destroyed the room, it spit all over the table. The disk used to float in the air. Now it melts in a pool of acid.";
                  if (musicBox in self)
                      "The table is a round disk that hovers a half meter off the ground. There's a music box on top.";
                  "The table is a round disk that hovers a half meter off the ground. Two repelling forces keep it in place.";
              Go:
                  "You are already here.";
              Take:
                  if (crewLounge.alienWrecked) "You don't want to do that. You could get acid on yourself.";
                  "There's no need. It has little value.";
              Push, PushDir:
                  if (crewLounge.alienWrecked) "You don't want to do that. You could get acid on yourself.";
                  "You push the disk forward a little, but the force that holds it in place snaps it back into the original position.";
              Pull:
                  if (crewLounge.alienWrecked) "You don't want to do that. You could get acid on yourself.";
                  "You pull the disk forward a little, but the force that holds it in place snaps it back into the original position.";
              Turn:
                  if (crewLounge.alienWrecked) "You don't want to do that. You could get acid on yourself.";
                  "You try to flip the disk, but the force that holds it in place won't let it turn over.";
              LookUnder:
                  if (crewLounge.alienWrecked) "It no longer floats in the air. It melts in a pool of acid.";
                  "Nothing is underneath it. It looks like the disk floats in the air, but two forces repelling each other keep it in place.";
              Attack, Burn, Climb, Close, Cut, Dig, Drink, Eat, Empty, Enter, Exit, GetOff, Go, GoIn, JumpOver, Kick, Listen, LookUnder, Open:
                  if (crewLounge.alienWrecked) "You don't want to do that. You could get acid on yourself.";
                  "That's not going to help.";
              Push, PushDir, Pull, Remove, Rub, Search, Set, SetTo, Smell, Squeeze, Swing, SwitchOn, SwitchOff, Take, Talk, Taste, Tie, Touch, Transfer, Turn, Unlock, Wave:
                  if (crewLounge.alienWrecked) "You don't want to do that. You could get acid on yourself.";
                  "That's not going to help.";
          ],
    has   supporter;

! 12/11/21

  StObj   -> crewLoungeCouch "couch"
    with  name 'couch' 'sofa' 'leather',
          before [;
              Examine:
                  player.advanceGravity = false;
                  if (crewLounge.alienWrecked)
                      "The black leather couch has been torn into - shredded by a set of claws. Then spit on, covering it with acid.";
                  "It's a black leather couch that wraps around a hovering disk in the center of the room.";
              Enter:
                  if (crewLounge.alienWrecked) "The couch is covered in acid. You don't want to sit in that.";
                  "This is no time to relax. You are plunging into the sun.";
              Go:
                  "You are already here.";
              Attack, Burn, Climb, Close, Cut, Dig, Drink, Eat, Empty, Enter, Exit, GetOff, Go, GoIn, JumpOver, Kick, Listen, LookUnder, Open:
                  if (crewLounge.alienWrecked) "You don't want to do that. You could get acid on yourself.";
                  "You need to loot the ship, not mess with ", (the) self, ".";
              Push, PushDir, Pull, Remove, Rub, Search, Set, SetTo, Smell, Squeeze, Swing, SwitchOn, SwitchOff, Take, Talk, Taste, Tie, Touch, Transfer, Turn, Unlock, Wave:
                  if (crewLounge.alienWrecked) "You don't want to do that. You could get acid on yourself.";
                  "You need to loot the ship, not mess with ", (the) self, ".";
          ];

! 01/15/22

  StObj   -> crewLoungeHatch "hatch"
    with  name 'hatch' 'hinge' 'hinges' 'door',
          before [;
              Examine:
                  player.advanceGravity = false;
                  if (alien in forwardStarboardJunctionDeckB) "Is there something shifting in the smoke behind the hatch? It's hard to tell.";
                  "The hatch has been left open, allowing anything to enter the room.";
              Enter:
                  if (alien in crewLounge) return PXF();
                  crewLounge.firstTime = true;
                  PlayerTo(forwardStarboardJunctionDeckB, 2);
                  rtrue;
              Go:
                  "You are already here.";
              Open:
                  "That's already open.";
              Take:
                  "The hatch isn't easily coming off its hinges, and it's worthless.";
          ];

! 01/05/22

  AcidObj crewLoungeAcid "acid"
    with  name 'acid' 'pool' 'secretion' 'secretions',
          before [;
              Examine, Search:
                  player.advanceGravity = false;
                  "The acid burns everything it touches, trying to melt all the way through the deck.";
              Go:
                  "You are already here.";
          ];
