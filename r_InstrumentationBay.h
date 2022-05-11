
! ---------------------------------------------------------------------------- !
!       INSTRUMENTATION BAY. 11/09/21
!
  Room    instrumentationBay "Instrumentation Bay - Deck B"
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
              "This room has a little smoke due to the hatch being broken open, but besides that,
              it looks untouched, only by time and dust. Monitoring equipment is set up and plugged
              into a computer to observe gamma-ray bursts.^^The only way out is starboard, through
              the broken hatch.";
          ],
          e_to [;
              self.firstTime = true;
              return scienceCorridorDeckB;
          ],
          cant_go [;
              if (alien in self) return PXF();
              "You can exit starboard.";
          ],
          before [;
              Exit:
                  self.firstTime = true;
                  PlayerTo(scienceCorridorDeckB, 2);
                  rtrue;
              Listen:

          ],
          takeLens false,
          takenCamera false,
          roomCount true,
          firstTime true;

! 11/09/21

  RoomObj -> instrumentationBayObj "bay"
    with  name 'bay' 'area' 'place' 'room',
          description [;
              <<Look instrumentationBay>>;
          ],
          before [;
              Take, Remove, Turn, PushDir, Push, Pull:
                  "You can't do that to the bay.";
          ];

! 01/13/22

  StObj   -> instrumentationBaySmoke "smoke"
    with  name 'smoke' 'air' 'haze' 'hazy' 'thin' 'gloom' 'dark' 'cloud' 'smog',
          before [;
              Examine:
                  player.advanceGravity = false;
                  "Smoke makes its way into here, but it's not as thick as the rest of the ship. The hatch blocked it before you broke the door.";
              Enter, Go:
                  "You need to tell me which direction to go in.";
          ];

! 01/13/22

  StObj   -> instrumentationBayDust "dust"
    with  name 'dust' 'dirt',
          before [;
              Examine:
                  player.advanceGravity = false;
                  "A layer of dust covers the equipment in here.";
              Go:
                  "You are already here.";
          ];

! 01/13/22

  StObj   -> instrumentationBayEquipment "equipment"
    with  name 'monitoring' 'equipment',
          before [;
              Examine:
                  player.advanceGravity = false;
                  "Monitoring equipment is built directly into the ship, hooked into sensors that are scattered across the hull. There's no station to operate it. Instead, the small node collects all the data.";
              Take:
                  "The equipment is part of the ship. It isn't going anywhere.";
              Go:
                  "You are already here.";
          ];

! 01/13/22

  StObj   -> instrumentationBayComputer "computer"
    with  parse_name [w1;
              w1 = NextWord();
              if (w1 ~= 'small' or 'node' or 'computer') return 0;
              return 3;
          ],
          before [;
              Examine:
                  player.advanceGravity = false;
                  "This computer is a buffer that watches deepspace before sending any warnings to the core A.I.";
              Take:
                  "This single-function computer isn't worth anything.";
              Go:
                  "You are already here.";
          ];

! 01/13/22

  StObj   -> instrumentationBayHatch "hatch"
    with  name 'hatch' 'door' 'broken',
          before [;
              Close:
                  "You broke it open.";
              Examine:
                  player.advanceGravity = false;
                  if (alien in scienceCorridorDeckB) "Is there something shifting in the smoke behind the hatch? It's hard to tell.";
                  "The hatch has been broken open and leads back to the science corridor.";
              Enter:
                  instrumentationBay.firstTime = true;
                  PlayerTo(scienceCorridorDeckB, 2);
                  rtrue;
              Open:
                  "You already did that with the sledgehammer.";
              Go:
                  "You are already here.";
              Unlock:
                  "The hatch isn't locked.";
          ];
