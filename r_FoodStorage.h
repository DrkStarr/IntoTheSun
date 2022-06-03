
! ---------------------------------------------------------------------------- !
!       FOOD STORAGE. 11/17/21
!
  Room    foodStorage "Food Locker - Deck B"
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
                  "Smoke has flooded the locker, and all the light in here comes from the passageway.
                  The door to this room has been torn off. Crates of prefab meals were stacked here,
                  along with coffee, but they're all broken into and spit on - acid burning through
                  the plastic.^^Since half the room is covered in acid, the only way out is port.";
              }
              "Smoke trickles in from the corridor, and a little light comes with it. It's dark
              in here and cold, but you can make out crates of prefab food that sit on pallets.
              Half are already gone. On the other side are containers of coffee. Quite a few of
              those are missing too.^^Even though half of the stuff is gone, the locker is packed
              tight, so the only way out is port.";
          ],
          w_to [;
              if (alien in self) return PXF();
              self.firstTime = true;
              return foodLockerCorridorDeckB;
          ],
          cant_go [;
              if (alien in self) return PXF();
              "You can exit port.";
          ],
          before [;
              Exit:
                  if (alien in self) return PXF();
                  self.firstTime = true;
                  PlayerTo(foodLockerCorridorDeckB, 2);
                  rtrue;
              Listen:

          ],
          takenWine false,
          alienWrecked false,
          destroyedYet false,
          roomCount true,
          firstTime true;

! 11/17/21

  RoomObj -> foodStorageObj "room"
    with  name 'area' 'place' 'room' 'section' 'locker',
          description [;
              <<Look foodStorage>>;
          ],
          before [;
              Take, Remove, Turn, PushDir, Push, Pull:
                  "You can't do that to the room.";
          ];

! 01/15/22

  StObj   -> foodStorageCrate "meals"
    with  name 'crate' 'crates' 'prefab' 'meal' 'meals' 'food' 'plastic' 'boxes' 'box',
          before [;
              Attack:
                  if (foodStorage.alienWrecked) "They're covered in acid. If you hit them at all, you'd burn yourself horribly.";
                  "While it might be fun, you'd only make a mess breaking into the crates.";
              Examine:
                  player.advanceGravity = false;
                  if (foodStorage.alienWrecked)
                      "The crates were piled high but are now broken into and scattered. A layer of acid covers them, melting through the boxes.";
                  "Crates are piled high in this room - containers full of prefab meals. Along with the nutrient processor, this is all the crew needs when not in hypersleep.";
              Open:
                  if (foodStorage.alienWrecked) "Scattered around the room, they're melting in acid.";
                  "You're not hungry enough to try century-old food.";
              Take, Remove:
                  if (foodStorage.alienWrecked) "The crates are scattered and covered in acid. You'd only burn yourself if you tried that.";
                  "They sat out here in space for a long time. These crates are worthless.";
              Attack, Burn, Climb, Close, Cut, Dig, Drink, Eat, Empty, Enter, Exit, GetOff, Go, GoIn, JumpOver, Kick, Listen, LookUnder, Open:
                  if (foodStorage.alienWrecked) "The crates are scattered and covered in acid. You'd only burn yourself if you tried that.";
                  "You need to loot the ship, not mess with ", (the) self, ".";
              Push, PushDir, Pull, Remove, Rub, Search, Set, SetTo, Smell, Squeeze, Swing, SwitchOn, SwitchOff, Take, Talk, Taste, Tie, Touch, Transfer, Turn, Unlock, Wave:
                  if (foodStorage.alienWrecked) "The crates are scattered and covered in acid. You'd only burn yourself if you tried that.";
                  "You need to loot the ship, not mess with ", (the) self, ".";
          ],
     has  pluralname;

! 01/15/22

  StObj   -> foodStorageCoffee "coffee"
    with  name 'coffee' 'container' 'containers',
          before [;
              Attack:
                  if (foodStorage.alienWrecked) "They're covered in acid. If you hit them at all, you'd burn yourself horribly.";
                  "The containers are made from thick plastic and don't break that easily.";
              Examine:
                  player.advanceGravity = false;
                  if (foodStorage.alienWrecked)
                      "The containers have been broken open, coffee spilling its way onto the floor. But a layer of acid covers everything as it tries to burn its way to the C deck.";
                  "It's the crew's one comfort. Plenty of coffee has been stored here to keep them going through long days. But some of it is gone, just like the food.";
              Take, Remove:
                  if (foodStorage.alienWrecked) "The containers are scattered and covered in acid. You'd only burn yourself if you tried that.";
                  "They sat out here in space for a long time. These containers are worthless.";
              Attack, Burn, Climb, Close, Cut, Dig, Drink, Eat, Empty, Enter, Exit, GetOff, Go, GoIn, JumpOver, Kick, Listen, LookUnder, Open:
                  if (foodStorage.alienWrecked) "The containers are scattered and covered in acid. You'd only burn yourself if you tried that.";
                  "You need to loot the ship, not mess with ", (the) self, ".";
              Push, PushDir, Pull, Remove, Rub, Search, Set, SetTo, Smell, Squeeze, Swing, SwitchOn, SwitchOff, Take, Talk, Taste, Tie, Touch, Transfer, Turn, Unlock, Wave:
                  if (foodStorage.alienWrecked) "The containers are scattered and covered in acid. You'd only burn yourself if you tried that.";
                  "You need to loot the ship, not mess with ", (the) self, ".";
          ];

! 01/15/22

  StObj   -> foodStoragePallets "pallets"
    with  name 'pallet' 'pallets',
          before [;
              Examine:
                  player.advanceGravity = false;
                  if (foodStorage.alienWrecked)
                      "Everything in here is covered in acid. The pallets fare no better.";
                  "With it kept cold in here, pallets line the floor creating a buffer between the deck and the food crates.";
              Take, Remove:
                  "The pallets aren't worth anything at all.";
              Attack, Burn, Climb, Close, Cut, Dig, Drink, Eat, Empty, Enter, Exit, GetOff, Go, GoIn, JumpOver, Kick, Listen, LookUnder, Open:
                  if (foodStorage.alienWrecked) "The pallets are covered in acid. You'd only burn yourself if you tried that.";
                  "You need to loot the ship, not mess with ", (the) self, ".";
              Push, PushDir, Pull, Remove, Rub, Search, Set, SetTo, Smell, Squeeze, Swing, SwitchOn, SwitchOff, Take, Talk, Taste, Tie, Touch, Transfer, Turn, Unlock, Wave:
                  if (foodStorage.alienWrecked) "The pallets are covered in acid. You'd only burn yourself if you tried that.";
                  "You need to loot the ship, not mess with ", (the) self, ".";
          ],
     has  pluralname;

! 01/15/22

  StObj   -> foodStorageDoor "door"
    with  name 'freezer' 'door' 'corridor' 'rails' 'hatch' 'ph010' 'ph011' 'ph012' 'ph013' 'frame',
          before [;
              Examine:
                  player.advanceGravity = false;
                  if (foodStorage.alienWrecked) "Light comes in from the gaping hole in the bulkhead. The door is gone - the frame dented all around.";
                  "Light comes in from the open door. It leads back to the corridor.";
              Enter:
                  if (alien in foodStorage) return PXF();
                  foodStorage.firstTime = true;
                  PlayerTo(foodLockerCorridorDeckB, 2);
                  rtrue;
              Go:
                  "You are already here.";
              Open:
                  "That's already open.";
              Take:
                  if (foodStorage.alienWrecked) "The door is gone, and you're not taking the frame.";
                  "You're not going to pull the freezer door off the rails, plus it's worthless.";
          ];

! 01/05/22

  AcidObj foodStorageAcid "acid"
    with  parse_name [w1;
              w1 = NextWord();
              if (w1 ~= 'acid' or 'pool' or 'secretion' or 'secretions' or 'red' or 'liquid') return 0;
              if (wine.spitOn == false && w1 == 'red' or 'liquid') return 0;
              return 3;
          ],
          before [;
              Examine, Search:
                  player.advanceGravity = false;
                  if (wine.spitOn) "Acid mixes with the red liquid but does nothing to dilute the strength of the secretion. It still tries to melt through the deck.";
                  "The acid burns everything it touches, trying to melt all the way through the deck.";
              Go:
                  "You are already here.";
          ];
