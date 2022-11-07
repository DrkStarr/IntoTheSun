
! ---------------------------------------------------------------------------- !
!       FORWARD COMPANIONWAY DECK B. 10/23/21
!
  Room    forwardCompanionwayDeckB "Forward Companionway - Deck B"
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
              starboardJunctionDeckB.playerEnterCompanionway = true;
              d_obj.&name-->6 = 'ph023';
              d_obj.&name-->7 = 'ph024';
              "With the batteries running out, the lights in this section collide with the smoke
              to create an orange glow. It gives the room an imagined warmth, where there is none
              in space. The companionway is wide, with an access panel on the forward bulkhead.^
              ^A ladder well sits in the middle of the room while corridors
              spider off from it, heading fore and starboard. The corridor aft has
              collapsed.";
          ],
          n_to [;
              if (alien in self) return PXF();
              self.firstTime = true;
              return scienceCorridorDeckB;
          ],
          s_to [;
              "The corridor aft has collapsed and is full of debris. Like something slammed into the ship while she floated through space.";
          ],
          e_to [;
              if (alien in self) return PXF();
              self.firstTime = true;
              return starboardJunctionDeckB;
          ],
          u_to [;
              <<Enter forwardCompanionwayDeckBOpening>>;
          ],
          d_to [;
              if (alien in self) return PXF();
              if (lookmode == 2) print "Carefully you descend to the deck below.^";
              self.firstTime = true;
              return forwardCompanionwayDeckC;
          ],
          cant_go [;
              if (alien in self) return PXF();
              "You can go forward, starboard, up, or down.";
          ],
          before [;
              Exit:

              Listen:
                  if (forwardStarboardJunctionDeckC.pipesBlown) "Below you, the sound of gas venting into the air cries through the ship.";

          ],
          roomCount true,
          firstTime true;

! 10/23/21

  RoomObj -> forwardCompanionwayDeckBObj "companionway"
    with  name 'companionway' 'area' 'room' 'place' 'section',
          description [;
              <<Look forwardCompanionwayDeckB>>;
          ],
          before [;
              Take, Remove, Turn, PushDir, Push, Pull:
                  "You can't do that to the companionway.";
              Enter, Go:
                  "You need to give me a direction to go in - forward, starboard, up, or down.";
          ];

! 10/23/21

  OutRch  -> forwardCompanionwayDeckBOpening "opening"
    with  name 'opening',
          before [;
              Examine:
                  player.advanceGravity = false;
                  "You can tell there's an opening here from a light above that tries to cut through all the smoke.";
              Enter, Go:
                  if (alien in forwardCompanionwayDeckB) return PXF();
                  if (lookmode == 2) print "Slowly you climb up the ladder well.^";
                  forwardCompanionwayDeckB.firstTime = true;
                  PlayerTo(forwardCompanionwayDeckA, 2);
                  rtrue;
          ];

! 10/23/21

  StObj   -> forwardCompanionwayDeckBLadder "ladder"
    with  name 'ladder' 'well',
          before [;
              Examine:
                  player.advanceGravity = false;
                  "The ladder well gives access to the upper and lower decks of the ship. With it in the middle of the room, it's easy to access.";
              Enter, Go, Climb:
                  "You need to give me a direction to go in - up or down.";
          ],
     has  container open;

! 11/30/21

  NoHelp  -> forwardCompanionwayDeckBCorridor "collapsed corridor"
    with  name 'collapsed' 'corridor' 'blocked' 'aft',
          before [;
              Examine:
                  player.advanceGravity = false;
                  "The corridor aft is blocked. Like something slammed into the ship while she floated through space.";
              Enter, Go:
                  "You're not getting through that.";
          ];

! 02/18/22

  StObj   -> forwardCompanionwayDeckBPanel "access panel"
    with  name 'access' 'panel' 'life' 'support' 'system' 'plate',
          before [;
              Attack:
                  if (self.objectAttacked) "You don't need to break the panel. There's no time to disassemble the equipment. Now you're just wasting time.";
                  self.objectAttacked = true;
                  "You don't need to break the panel. There's no time to disassemble the equipment. You need to loot what's
                  easily takeable before you burn up in the sun.";
              Examine, Search:
                  player.advanceGravity = false;
                  "The access panel is recessed into the bulkhead. Behind it is the life support system for the ship.
                  Located here in the companionway, it gave engineering easy access to the equipment.";
              Open, Unlock:
                  if (self.objectUsed) "There's no need. You don't have time to disassemble the ship. Now you're just wasting time.";
                  self.objectUsed = true;
                  "There's no need. You don't have time to disassemble the ship. You need to loot what's easily takeable.";
              Touch:
                  "You put your hand on the panel but feel nothing. None of the equipment is running.";
              Push, PushDir, Pull, Take, Remove, Turn:
                  if (self.objectUsed) "The access panel is sealed, and there's no need to get inside. Now you're just wasting time.";
                  self.objectUsed = true;
                  "The access panel is sealed, and there's no need to get inside. You don't have time to disassemble the ship. You need to loot what's easily takeable.";
              SetCode, SetTo:
                  "There is no input. The panel is designed to be pried off.";
          ],
          objectUsed false,
          objectAttacked false;

! 02/20/22

  OutRch  -> forwardCompanionwayDeckBVent "vent"
    with  name 'vent' 'ventilation' 'vents',
          before [;
              Enter:
                  "You wouldn't last long in there.";
              Examine:
                  player.advanceGravity = false;
                  "The ventilation system runs throughout the ship. It was used to supply the vessel with fresh air
                  when it was in working condition. The scrubbers are blown. The ship's full of smoke.";
              Go:
                  "You are as close as you're going to get.";
          ];

! 01/05/22

  NoHelp  forwardCompanionwayDeckBDebris "debris"
    with  name 'debris' 'rubble' 'blockage' 'junk',
          before [;
              Examine:
                  player.advanceGravity = false;
                  "Debris blocks the corridor. You're going to have to find another way around.";
              Enter, Go:
                  "You're not getting through that.";
              Attack, Burn, Push, PushDir, Pull, Take, Remove, Kick, Turn:
                  "A hard impact created the debris. It's not going anywhere.";
          ],
          found_in forwardCompanionwayDeckB forwardPortJunctionDeckB forwardStarboardJunctionDeckB forwardCompanionwayDeckC
                   aftPortJunctionDeckC;
