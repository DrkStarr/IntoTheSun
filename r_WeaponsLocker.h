
! ---------------------------------------------------------------------------- !
!       WEAPONS LOCKER. 11/17/21
!
  Room    weaponsLocker "Weapons Locker - Deck B"
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
                  if (weaponsLocker.takenArmor || weaponsLocker.takenBaton)
                      "Amber lights create a thick haze as smoke drifts in from the broken door. There's only one
                      pallet, covered in acid, that slowly burns through the deck.^^The space isn't that big, and
                      there's nothing else in the room. You can exit starboard.";
                  "Amber lights create a thick haze as smoke drifts in from the broken door. There's only one pallet
                  of stuff that's been left behind, and it's covered in acid that slowly burns through the
                  deck.^^The space isn't that big, and there's nothing else in the room. You can exit starboard.";
              }
              "Because the door was sealed, there's little smoke here. Amber lights create a slight haze, revealing
              what little is in the room. There's only one pallet of stuff that's been left behind. It's a shame
              there are no pulse rifles that would help you kill this thing.^^The space isn't that big, and there's
              nothing else in the room. You can exit starboard.";
          ],
          e_to [;
              if (alien in self) return PXF();
              self.firstTime = true;
              return passagewayDeckB;
          ],
          cant_go [;
              if (alien in self) return PXF();
              "You can exit starboard.";
          ],
          before [;
              Exit:
                  if (alien in self) return PXF();
                  self.firstTime = true;
                  PlayerTo(passagewayDeckB, 2);
                  rtrue;
              Listen:

          ],
          alienWrecked false,
          destroyedYet false,
          takenBaton false,
          takenArmor false,
          roomCount true,
          firstTime true;

! 11/17/21

  RoomObj -> weaponsLockerObj "room"
    with  name 'area' 'place' 'room' 'section' 'locker',
          description [;
              <<Look weaponsLocker>>;
          ],
          before [;
              Take, Remove, Turn, PushDir, Push, Pull:
                  "You can't do that to the room.";
          ];

! 12/13/21

  StObj   -> weaponsLockerPallet "pallet"
    with  name 'pallet' 'industrial',
          before [;
              Attack:

              Examine:
                  player.advanceGravity = false;
                  if (weaponsLocker.alienWrecked) {
                      if (weaponsLocker.takenArmor == false) {
                          if (weaponsLocker.takenBaton == false) {
                              "On top of a pallet covered in acid, a set of trooper armor melts into the deck along with a stun baton.";
                          }
                          "On top of a pallet covered in acid, a set of trooper armor melts into the deck.";
                      }
                      if (weaponsLocker.takenBaton == false)
                        "The pallet is covered in acid that burns through it. The stun baton got hit by the liquid, and you watch it melt away.";
                      "The pallet is covered in acid that burns through it.";
                  }
                  if (weaponsLocker.takenArmor == false) {
                      if (weaponsLocker.takenBaton == false) {
                          "On top of a pallet in the corner of the room is a set of trooper armor, while a stun baton lies beside it.";
                      }
                      "On top of a pallet that lies in the corner of the room is a set of trooper armor.";
                  }
                  if (weaponsLocker.takenBaton == false)
                      "The pallet lies in the corner of this room. Beside it is a stun baton.";
                  "The pallet lies in the corner of this room.";
              Go:
                  "You are already here.";
              Take:
                  if (weaponsLocker.alienWrecked) "The pallet is covered in acid. That's not something you want to take.";
                  "The pallet is big and isn't worth anything. You leave it alone.";
              Attack, Burn, Climb, Close, Cut, Dig, Drink, Eat, Empty, Enter, Exit, GetOff, Go, GoIn, JumpOver, Kick, Listen, LookUnder, Open:
                  if (weaponsLocker.alienWrecked) "It's covered in acid, and you'd burn yourself if you tried that.";
                  "You need to loot the ship, not mess with ", (the) self, ".";
              Push, PushDir, Pull, Remove, Rub, Search, Set, SetTo, Smell, Squeeze, Swing, SwitchOn, SwitchOff, Take, Talk, Taste, Tie, Touch, Transfer, Turn, Unlock, Wave:
                  if (weaponsLocker.alienWrecked) "It's covered in acid, and you'd burn yourself if you tried that.";
                  "You need to loot the ship, not mess with ", (the) self, ".";
          ];

! 01/16/22

  StObj   -> weaponsLockerHatch "door"
    with  name 'hatch' 'rail' 'rails' 'ph005' 'frame' 'door',
          before [;
              Examine:
                  player.advanceGravity = false;
                  if (alien in passagewayDeckB) "Is there something shifting in the smoke behind the hatch? It's hard to tell.";
                  if (weaponsLocker.alienWrecked) "The door has been torn off. Only the frame is left.";
                  "The door is open as smoke from the passageway drifts into this room.";
              Enter:
                  if (alien in weaponsLocker) return PXF();
                  weaponsLocker.firstTime = true;
                  PlayerTo(passagewayDeckB, 2);
                  rtrue;
              Go:
                  "You are already here.";
              Open:
                  "That's already open.";
              Take:
                  if (weaponsLocker.alienWrecked) "The door is gone, and you're not taking the frame.";
                  "The door isn't easily coming off the rails, and it's worthless.";
          ];

! 01/16/22

  StObj   weaponsLockerLight "lights"
    with  name 'dim' 'light' 'lights' 'glow' 'soft' 'amber' 'led' 'leds' 'orange' 'rays',
          before [;
              Examine:
                  player.advanceGravity = false;
                  if (weaponsLocker.alienWrecked) "Fresh smoke dominates the air as amber lights try to fight through.";
                  "Since there's very little smoke in this room, amber lights easily cut through.";
              Go:
                  "You are already here.";
          ];


! 01/16/22

  StObj   weaponsLockerSmoke "smoke"
    with  name 'smoke' 'air' 'haze' 'hazy' 'thick' 'gloom' 'dark' 'cloud' 'smog' 'dense',
          before [;
              Examine:
                  player.advanceGravity = false;
                  if (weaponsLocker.alienWrecked) "With the hatch broken, smoke drifts into the room, blocking the lights as orange rays penetrate the haze.";
                  "There's not a lot of smoke in this room since you recently opened the hatch.";
              Go:
                  "You are already here.";
          ];

! 01/05/22

  AcidObj weaponsLockerAcid "acid"
    with  name 'acid' 'pool' 'secretion' 'secretions' 'vomit' 'acidic',
          before [;
              Examine, Search:
                  player.advanceGravity = false;
                  "The acid burns everything it touches, trying to melt all the way through the deck.";
              Go:
                  "You are already here.";
          ];
