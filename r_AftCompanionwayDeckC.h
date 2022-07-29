
! ---------------------------------------------------------------------------- !
!       AFT COMPANIONWAY DECK C. 10/30/21
!
  Room    aftCompanionwayDeckC "Aft Companionway - Deck C"
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
              d_obj.&name-->6 = 'water';
              d_obj.&name-->7 = 'liquid';
              player.inCorridor = true;
              "It's dark on the lower decks, with the companionway saturated in an orange glow.
              But there is enough light to see a spare battery for the welding equipment up against
              the fore bulkhead.^^A ladder in the middle of this companionway will take you up to the
              B deck. A corridor runs port to starboard while the control room is aft.";
          ],
          s_to [;
              if (alien in self) return PXF();
              self.firstTime = true;
              return controlRoomDeckC;
          ],
          e_to [;
              if (alien in self) return PXF();
              self.firstTime = true;
              return aftStarboardJunctionDeckC;
          ],
          w_to [;
              if (alien in self) return PXF();
              self.firstTime = true;
              return aftPortJunctionDeckC;
          ],
          u_to [;
              <<Enter aftCompanionwayDeckCLadder>>;
          ],
          d_to [;
              "You're already on the bottom deck.";
          ],
          cant_go [;
              if (alien in self) return PXF();
              "You can go aft, port, starboard, or up.";
          ],
          before [;
              Exit:

              GoIn:
                  if (alien in self) return PXF();
                  self.firstTime = true;
                  PlayerTo(controlRoomDeckC, 2);
                  rtrue;
              Listen:
                  if (forwardStarboardJunctionDeckC.pipesBlown) "Starboard, the sound of gas venting into the air cries through the ship.";
          ],
          roomCount true,
          firstTime true;

! 10/30/21

  RoomObj -> aftCompanionwayDeckCObj "companionway"
    with  name 'companionway' 'area' 'room' 'place' 'section',
          description [;
              <<Look aftCompanionwayDeckC>>;
          ],
          before [;
              Take, Remove, Turn, PushDir, Push, Pull:
                  "You can't do that to the companionway.";
              Enter, Go:
                  "You need to give me a direction to go in - aft, port, starboard, or up.";
          ];

! 10/30/21

  StObj   -> aftCompanionwayDeckCLadder "ladder"
    with  name 'ladder' 'well',
          before [;
              Examine:
                  player.advanceGravity = false;
                  "The ladder well gives access to the up deck of the ship. With it in the middle of the room, it's easy to access.";
              Enter, Go, Climb:
                  if (alien in aftCompanionwayDeckC) return PXF();
                  if (lookmode == 2) print "Slowly you climb up the ladder well.^";
                  aftCompanionwayDeckC.firstTime = true;
                  PlayerTo(aftCompanionwayDeckB, 2);
                  rtrue;
          ];

! 10/23/21

  OutRch  -> aftCompanionwayDeckCOpening "opening"
    with  name 'opening',
          before [;
              Examine:
                  player.advanceGravity = false;
                  "Smoke tries to make its way down into this companionway through the opening above.";
              Enter, Go:
                  <<Enter aftCompanionwayDeckCLadder>>;
          ];

! 03/23/22

  StObj   -> aftCompanionwayDeckCBattery "spare battery"
    with  name 'spare' 'large' 'battery',
          before [;
              Attack:
                  if (alien.sleeping) "That would make a lot of noise. It's best you don't disturb the ship.";
                  "That would make a lot of noise. What are you trying to do? Attract the xenomorph?";
              Examine:
                  player.advanceGravity = false;
                  "There is another large battery here, designed to hold a charge for decades. It stands as tall
                  as the corridor and is used as backup power for the welder.";
              Push, Pull, PushDir:
                  "You don't need to use the battery. It can stay right there.";
              Take:
                  "It's larger than the bag and wouldn't fit.";
              SwitchOn, SwitchOff:
                  "That's not how it works.";
          ];

! 07/23/22

  OutRch  -> aftCompanionwayDeckCWelder "welding equipment"
    with  name 'welding' 'equipment' 'cold' 'laser' 'welder',
          before [;
              Examine:
                  player.advanceGravity = false;
                  "The laser welder is in the port corridor next to you. But it's hard to make out clearly
                  through all the smoke filling the ship.";
              Enter, Go:
                  aftCompanionwayDeckC.firstTime = true;
                  PlayerTo(aftStarboardJunctionDeckC, 2);
                  rtrue;
          ];
