
! ---------------------------------------------------------------------------- !
!       CONTROL ROOM. 11/06/21
!
  Room    controlRoomDeckC "Engineering Control Room - Deck C"
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
                  "There's more smoke than usual in this room, and the lights fail to help. But through this acidic haze,
                  you see the controls have been laid into - all the gauges that monitor the vessel are covered in acid,
                  adding to the thick smoke in the room. The only way out is forward.";
              }
              "There's smoke, and the lights struggle to get through it. But, in this gloom, you can at least see the
              aft bulkhead and the controls for the engines - with gauges and screens that monitor the vessel when under
              load.^^The room is cramped with controls, a locker, and a bench. So the only way out is forward.";
          ],
          n_to [;
              if (alien in self) return PXF();
              self.firstTime = true;
              return aftCompanionwayDeckC;
          ],
          cant_go [;
              if (alien in self) return PXF();
              "You can exit forward.";
          ],
          before [;
              Exit:
                  if (alien in self) return PXF();
                  self.firstTime = true;
                  PlayerTo(aftCompanionwayDeckC, 2);
                  rtrue;
              Listen:

          ],
          closetOpen false,
          takenLaptop false,
          alienWrecked false,
          destroyedYet false,
          testObjectInRoom false,
          roomCount true,
          firstTime true;

! 11/06/21

  RoomObj -> controlRoomDeckCObj "room"
    with  name 'area' 'place' 'room' 'section',
          description [;
              <<Look controlRoomDeckC>>;
          ],
          before [;
              Take, Remove, Turn, PushDir, Push, Pull:
                  "You can't do that to the room.";
          ];

! 11/06/21

  Object  -> controlRoomDeckCCabinet "locker"
    with  name 'cabinet' 'utility' 'closet' 'locker' 'door' 'latch',
          describe [;
              if (controlRoomDeckC.alienWrecked) {
                  print "^A locker lies on the port bulkhead - a thin thing like a utility closet that's covered in acid";
                  if (laptop in controlRoomDeckCBench) ". Across from it, on top of a bench, a broken laptop lies in a pool of the yellow stuff.";
                  ". Across from it sits a bench boiling away in a pool of the yellow stuff.";
              }
              print "^A locker lies on the port bulkhead - a thin thing like a utility closet that's ";
              if (controlRoomDeckC.closetOpen) print "open";
              else print "closed";
              print ". While across from it sits a bench";
              if (controlRoomDeckC.takenLaptop == false) " that has a small laptop on top of it.";
              ".";
          ],
          before [ iTempLoc;
              Attack:
                  if (alien in controlRoomDeckC) "Not with the alien standing in front of it.";
                  if (self.alienWrecked) "You don't want to touch that. It's melting, covered in acid.";
                  if (self.openedFirstTime) {
                      if (controlRoomDeckC.closetOpen) "The locker is already open. You don't need to do that.";
                      "You've already gotten everything out of there. There's no reason to open it again.";
                  }
                  "You could break the locker, but why don't you try opening it?";
              Close:
                  if (alien in controlRoomDeckC) "Not with the alien standing in front of it.";
                  if (self.alienWrecked) "You don't want to touch that. It's melting, covered in acid.";
                  if (controlRoomDeckC.closetOpen) {
                      controlRoomDeckC.closetOpen = false;
                      "You close the locker, but the door gets stuck on the latch.";
                  }
                  "That's already closed.";
              Enter:
                  if (alien in controlRoomDeckC) "Not with the alien standing in front of it.";
                  "You're too big to fit in there.";
              Examine:
                  player.advanceGravity = false;
                  if (self.alienWrecked) "The locker has been hit, slammed into, and broken. Then spit on by the alien before it left.";
                  print "The locker that sits on the port bulkhead is nothing more than a utility closet. ";
                  if (controlRoomDeckC.closetOpen) "Open, the contents have fallen out.";
                  "Closed, you can't see inside.";
              Go:
                  "You are already here.";
              Open, Pull:
                  if (alien in controlRoomDeckC) "Not with the alien standing in front of it.";
                  if (self.alienWrecked) "You don't want to touch that. It's melting, covered in acid.";
                  if (controlRoomDeckC.closetOpen) "That's already open.";
                  if (self.openedFirstTime) "The door sticks when you try to open it.";
                  self.openedFirstTime = true;
                  controlRoomDeckC.closetOpen = true;
                  move crowbar to controlRoomDeckC;
                  move controlRoomDeckCCabinet to controlRoomDeckC;
                  if (alien.sleeping) {
                      alien.sleeping = false;
                      player.alienMove = true;
                      iMonsterDestination = CONTROLRM;
                      print "Opening the locker, you try to catch a crowbar as it falls to the ground. You miss.^";
                      return AlienDestroysRoom(monster_loc-->0);
                  }
                  iMonsterDestination = CONTROLRM;
                  iTempLoc = iMonsterLoc;
                  iTempLoc++;
                  if (iTempLoc > MONSTERTOTAL) iTempLoc = 0;
                  monster_loc-->iMonsterLoc = CONTROLRM;
                  monster_loc-->iTempLoc = CONTROLRM;
                  alien.resetLocInControlRoom = true;
                  "Opening the locker, you try to catch a crowbar as it falls to the ground. You miss.";
              Unlock:
                  if (alien in controlRoomDeckC) "Not with the alien standing in front of it.";
                  if (self.alienWrecked) "You don't want to touch that. It's melting, covered in acid.";
                  if (controlRoomDeckC.closetOpen) "That's already open.";
                  if (second == cattleProd)
                      "You would break the cattle prod doing that. Unfortunately, the rod is not thick enough to pry open the locker.";
                  if (self.openedFirstTime) {
                      if (second == crowbar) {
                          iMonsterDestination = CONTROLRM;
                          iTempLoc = iMonsterLoc;
                          iTempLoc++;
                          if (iTempLoc > MONSTERTOTAL) iTempLoc = 0;
                          monster_loc-->iMonsterLoc = CONTROLRM;
                          monster_loc-->iTempLoc = CONTROLRM;
                          move crowbar to player;
                          alien.resetLocInControlRoom = true;
                          "You put the crowbar into the lip of the closet and push, giving it a good jolt. But the bar breaks free and slips out of your hand.^^As you pick it up, you realize you're making a lot of noise.";
                      }
                      "The door sticks. There is no need to play with it.";
                  }
              Blow:
                  "You can't blow through your suit. The polymer seals in your environment.";
              Attack, Burn, Climb, Close, Cut, Dig, Drink, Eat, Empty, Enter, Exit, GetOff, Go, GoIn, JumpOver, Kick, Listen, LookUnder, Open:
                  if (alien in controlRoomDeckC) "Not with the alien standing in front of it.";
                  if (self.alienWrecked) "You don't want to touch that. It's melting, covered in acid.";
                  "That's not going to help.";
              Push, PushDir, Pull, Remove, Rub, Search, Set, SetTo, Smell, Squeeze, Swing, SwitchOn, SwitchOff, Take, Talk, Taste, Tie, Touch, Transfer, Turn, Unlock, Wave:
                  if (alien in controlRoomDeckC) "Not with the alien standing in front of it.";
                  if (self.alienWrecked) "You don't want to touch that. It's melting, covered in acid.";
                  "That's not going to help.";
          ],
          alienWrecked false,
          openedFirstTime false,
     has  static;

! 11/15/21

  NoHelp  -> controlRoomDeckCBench "bench"
    with  name 'bench' 'desk' 'work' 'surface' 'metal' 'workbench' 'large',
          before [;
              Attack:
                  if (controlRoomDeckC.alienWrecked) "The bench is covered in acid. You'd only burn yourself if you tried that.";
                  if (sledgehammer in player)
                      "You could lay into it, that would be an excellent way to get your frustration out,
                      but you'd only dent it.";
                  "This bench has taken a lot more damage than you could dish out.";
              Examine:
                  player.advanceGravity = false;
                  if (laptop in self) {
                      if (laptop.spitOn)
                          "Strange cables that once coiled out from the engineering panel have melted away for a laptop that dissolves in a pool of acid.";
                      "Strange cables coil out from the engineering panel, hooked into a laptop that sits on the top of the bench.";
                  }
                  if (controlRoomDeckC.alienWrecked) "The bench has been spit on. It's covered in acid that slowly melts through the metal.";
                  "It's a standard bench made of metal, a pretty simple design that sits across from the locker.";
              Go:
                  "You are already here.";
              Close:
                  if (controlRoomDeckC.alienWrecked) "The bench is covered in acid. You'd only burn yourself if you tried that.";
                  "It's a simple bench. There's nothing to close.";
              Open:
                  if (controlRoomDeckC.alienWrecked) "The bench is covered in acid. You'd only burn yourself if you tried that.";
                  "It's a simple bench. There's nothing to open.";
              Push, PushDir, Pull, Turn:
                  if (controlRoomDeckC.alienWrecked) "The bench is covered in acid. You'd only burn yourself if you tried that.";
                  "The workbench is made of metal, and it's too heavy to push around.";
              Take:
                  if (controlRoomDeckC.alienWrecked) "The bench is covered in acid. You'd only burn yourself if you tried that.";
              Unlock:
                  if (controlRoomDeckC.alienWrecked) "The bench is covered in acid. You'd only burn yourself if you tried that.";
                  "It's a simple bench. There's nothing to unlock.";
              LookUnder:
                  if (controlRoomDeckC.alienWrecked) "There's nothing under the desk except dust. Ghost turds have accumulated, but the acid missed the dust balls.";
                  "There's nothing under the desk, only some ghost turds that have accumulated.";
              Attack, Burn, Climb, Close, Cut, Dig, Drink, Eat, Empty, Enter, Exit, GetOff, Go, GoIn, JumpOver, Kick, Listen, LookUnder, Open:
                  if (controlRoomDeckC.alienWrecked) "The bench is covered in acid. You'd only burn yourself if you tried that.";
                 "That's not going to help.";
              Push, PushDir, Pull, Remove, Rub, Search, Set, SetTo, Smell, Squeeze, Swing, SwitchOn, SwitchOff, Take, Talk, Taste, Tie, Touch, Transfer, Turn, Unlock, Wave:
                  if (controlRoomDeckC.alienWrecked) "The bench is covered in acid. You'd only burn yourself if you tried that.";
                 "That's not going to help.";
          ],
     has  supporter;

! 01/21/22

  StObj   -> controlRoomDeckCGauges "gauges"
    with  name 'gauge' 'gauges' 'screen' 'screens' 'control' 'controls',
          before [;
              Attack:
                  if (controlRoomDeckC.alienWrecked) "If you hit the acid it might splash up on you. That foolish action could kill you.";
              Examine:
                  player.advanceGravity = false;
                  if (controlRoomDeckC.alienWrecked) "The gauges melt under a layer of acid that covers the entire room.";
                  "All the gauges that monitor the ship are blank. She's dead in space.";
              Push, SwitchOn:
                  if (controlRoomDeckC.alienWrecked) "The gauges are covered in acid. You'd only burn yourself if you tried that.";
                  "There's no power running through the control room. Messing with the gauges won't help.";
              Attack, Burn, Climb, Close, Cut, Dig, Drink, Eat, Empty, Enter, Exit, GetOff, Go, GoIn, JumpOver, Kick, Listen, LookUnder, Open:
                  if (controlRoomDeckC.alienWrecked) "The gauges are covered in acid. You'd only burn yourself if you tried that.";
                  "You need to loot the ship, not mess with ", (the) self, ".";
              Push, PushDir, Pull, Remove, Rub, Search, Set, SetTo, Smell, Squeeze, Swing, SwitchOn, SwitchOff, Take, Talk, Taste, Tie, Touch, Transfer, Turn, Unlock, Wave:
                  if (controlRoomDeckC.alienWrecked) "The gauges are covered in acid. You'd only burn yourself if you tried that.";
                  "You need to loot the ship, not mess with ", (the) self, ".";
          ],
     has  pluralname;

! 03/26/22

  StObj   -> controlRoomDeckCTurds "ghost turds"
    with  name 'ghost' 'turds' 'turd' 'dust' 'ball' 'balls',
          before [;
              Examine:
                  player.advanceGravity = false;
                  if (controlRoomDeckC.alienWrecked) "There are still ghost turds underneath the desk, clear of the acid.";
                  "Thick balls of dust have accumulated underneath the desk. You've heard Navy personnel refer to them as ghost turds.";
              Take:
                  "You learned long ago that dust balls are worthless.";
              Rub:
                  "This is no time to clean up. You are plunging into the sun.";
          ],
     has  pluralname;

! 03/26/22

  StObj   -> controlRoomDeckCPanel "panel"
    with  name 'panel' 'engineering' 'coil' 'colored' 'cables' 'colors' 'wire' 'wires',
          before [;
              Attack:
                  if (controlRoomDeckC.alienWrecked) "If you hit the acid it might splash up on you. That foolish action could kill you.";
              Examine:
                  player.advanceGravity = false;
                  if (controlRoomDeckC.alienWrecked) "The cables coming out of the engineering panel melted when the acid hit them, while the rest of the panel was also covered.";
                  "Different colored cables coil out from the engineering panel, plugging into the back of the laptop.";
              Pull:
                  if (controlRoomDeckC.alienWrecked) "The panel is covered in acid. You'd only burn yourself if you tried that.";
                  "You don't need to unplug the laptop. Take what you want.";
              Push, SwitchOn:
                  if (controlRoomDeckC.alienWrecked) "The panel is covered in acid. You'd only burn yourself if you tried that.";
                  "There's no power running through the control room. Messing with the panel won't help.";
              Attack, Burn, Climb, Close, Cut, Dig, Drink, Eat, Empty, Enter, Exit, GetOff, Go, GoIn, JumpOver, Kick, Listen, LookUnder, Open:
                  if (controlRoomDeckC.alienWrecked) "The panel is covered in acid. You'd only burn yourself if you tried that.";
                  "You need to loot the ship, not mess with ", (the) self, ".";
              Push, PushDir, Pull, Remove, Rub, Search, Set, SetTo, Smell, Squeeze, Swing, SwitchOn, SwitchOff, Take, Talk, Taste, Tie, Touch, Transfer, Turn, Unlock, Wave:
                  if (controlRoomDeckC.alienWrecked) "The panel is covered in acid. You'd only burn yourself if you tried that.";
                  "You need to loot the ship, not mess with ", (the) self, ".";
          ];

! 01/05/22

  AcidObj controlRoomDeckCAcid "acid"
    with  name 'acid' 'pool' 'secretion' 'secretions' 'yellow',
          before [;
              Examine, Search:
                  player.advanceGravity = false;
                  "The acid burns everything it touches, trying to melt all the way through the deck.";
              Go:
                  "You are already here.";
          ];
