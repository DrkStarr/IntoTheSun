
! ---------------------------------------------------------------------------- !
!       PERSONAL LOCKER ROOM. 11/05/21
!
  Room    personalLockerRoom "Personal Locker Room - Deck A"
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
              "The crew doesn't have staterooms of their own, only the captain has that privilege, so
              they share this locker room when not in hypersleep. There are two rows of lockers, six
              total, on the fore and aft bulkheads with plenty of room in between. A bench runs down
              the center of this room.^^The only way out of the locker room is to the port.";
          ],
          w_to [;
              if (alien in self) return PXF();
              self.firstTime = true;
              return aftJunctionDeckA;
          ],
          cant_go [;
              "You can exit port.";
          ],
          before [;
              Exit:
                  if (alien in self) return PXF();
                  self.firstTime = true;
                  PlayerTo(aftJunctionDeckA, 2);
                  rtrue;
              Listen:

          ],
          takenDataReader false,
          takenHologram false,
          roomCount true,
          firstTime true;

! 11/05/21

  RoomObj -> personalLockerRoomObj "room"
    with  name 'quarters' 'area' 'place' 'room' 'section',
          description [;
              <<Look personalLockerRoom>>;
          ],
          before [;
              Take, Remove, Turn, PushDir, Push, Pull:
                  "You can't do that to the room.";
          ];

! 01/06/22

  NoHelp  -> personalLockerRoomBench "bench"
    with  name 'bench' 'wood',
          before [;
              Attack:
                  if (second == cattleProd) "That wouldn't do anything to the wood.";
                  if (second == sledgehammer) "Why? You'd break the bench in half and call the creature to here.";
                  "There's no reason to. Plus, beating on it with your hands wouldn't get you very far.";
              Examine:
                  player.advanceGravity = false;
                  if (dataReader in personalLockerRoom)
                      "The bench is a long piece of wood that runs down the middle of this room between the lockers. A
                      data reader has been left at one end.";
                  "The bench is a long piece of wood that runs down the middle of this room between the lockers.";
              Go:
                  "You are already here.";
              Open, Close, Unlock:
                  "The bench doesn't work like that. It's a flat piece of wood, nothing more.";
              Push, PushDir, Take, Remove, Turn:
                  "The bench isn't going anywhere, and it has no value.";
              Enter:
                  "This is no time to relax. You are plunging into the sun.";
          ],
     has  supporter;

! 01/06/22

  Object   -> personalLockerRoomLocker "locker"
    with  name 'locker' 'lockers' 'door' 'doors' 'cabinet' 'cabinets',
          before [;
              Examine:
                  player.advanceGravity = false;
                  print "A long row of lockers run along the fore and aft bulkheads. ";
                  if (self has open) {
                      if (hologram in self) "One is open with a hologram inside.";
                      "Open, there's nothing inside.";
                  }
                  "Closed, you can't see inside.";
              Go:
                  "You are already here.";
              Blow:
                  "You can't blow through your suit. The polymer seals in your environment.";
              Attack, Blow, Burn, Climb, Cut, Dig, Drink, Eat, Empty, Enter, Exit, GetOff, Go, GoIn, JumpOver, Kick, Listen, LookUnder:
                  "That's not going to help.";
              Push, PushDir, Pull, Remove, Rub, Set, SetTo, Smell, Squeeze, Swing, SwitchOn, SwitchOff, Take, Talk, Taste, Tie, Touch, Transfer, Turn, Unlock, Wave:
                  "That's not going to help.";
          ],
     has  static concealed container openable ~open pluralname;
