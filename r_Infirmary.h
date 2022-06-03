
! ---------------------------------------------------------------------------- !
!       INFIRMARY. 11/02/21
!
  Room    infirmary "Infirmary - Deck A"
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
                  "The smoke in the infirmary is thick, colliding with the lights, so the room is doused in
                  an orange glow. The examination table in the middle has been destroyed, broken in half, and
                  covered in acid, along with the cabinets that have been shattered.^^The alien wrecked this
                  room. There's only one way out with the cabinets torn off the walls, starboard.";
              }
              "The infirmary is barely lit with lots of smoke here - the room doused in an orange glow.
              There is an examination table in the middle of the room. The light above it creates god rays
              looking down.^^The bulkheads are lined with cabinets. There's only one way out, starboard.";
          ],
          e_to [;
              if (alien in self) return PXF();
              self.firstTime = true;
              return forwardCompanionwayDeckA;
          ],
          cant_go [;
              if (alien in self) return PXF();
              "You can exit starboard.";
          ],
          before [;
              Exit:
                  if (alien in self) return PXF();
                  self.firstTime = true;
                  PlayerTo(forwardCompanionwayDeckA, 2);
                  rtrue;
              Listen:

          ],
          alienWrecked false,
          destroyedYet false,
          takenKnitter false,
          takenMedkit false,
          roomCount true,
          firstTime true;

! 11/02/21

  RoomObj -> infirmaryObj "infirmary"
    with  name 'infirmary' 'area' 'place' 'room' 'section',
          description [;
              <<Look infirmary>>;
          ],
          before [;
              Take, Remove, Turn, PushDir, Push, Pull:
                  "You can't do that to the infirmary.";
          ];

! 12/28/21

  Object   -> infirmaryCabinet "cabinet"
    with  name 'cabinet' 'utility' 'closet' 'locker' 'door' 'plastic' 'wood',
          before [;
              Close, Search:
                  if (infirmary.alienWrecked) "You can't do that. The cabinets have been smashed and spit on. There's nothing left.";
              Examine:
                  player.advanceGravity = false;
                  if (infirmary.alienWrecked) "Smashed by a heavy impact, all that's left of the cabinets are pieces of plastic.";
                  print "Cabinets line the room. They are made from plastic and molded to look like wood";
                  if (self has open) {
                      if (medkit in self) ". One of them is open with a medkit inside.";
                      ". One of them is open with nothing inside.";
                  }
                  ", giving the infirmary a homey feeling.";
              Go:
                  "You are already here.";
              Open:
                  if (infirmary.alienWrecked) "You can't do that. The cabinets have been smashed and spit on. There's nothing left.";
              Blow:
                  "You can't blow through your suit. The polymer seals in your environment.";
              Attack, Burn, Climb, Close, Cut, Dig, Drink, Eat, Empty, Enter, Exit, GetOff, Go, GoIn, JumpOver, Kick, Listen, LookUnder, Open:
                  if (infirmary.alienWrecked) "You can't do that. The cabinets have been smashed and spit on. There's nothing left.";
                  "That's not going to help.";
              Push, PushDir, Pull, Remove, Rub, Set, SetTo, Smell, Squeeze, Swing, SwitchOn, SwitchOff, Take, Talk, Taste, Tie, Touch, Transfer, Turn, Unlock, Wave:
                  if (infirmary.alienWrecked) "You can't do that. The cabinets have been smashed and spit on. There's nothing left.";
                  "That's not going to help.";
          ],
     has  container openable ~open static concealed;

! 12/28/21

  Object   -> infirmaryCabinets "cabinets"
    with  name 'cabinets',
          before [;
              Close:
                  <<Close infirmaryCabinet>>;
              Examine:
                  <<Examine infirmaryCabinet>>;
              Search:
                  <<Search infirmaryCabinet>>;
              Go:
                  "You are already here.";
              Open:
                  <<Open infirmaryCabinet>>;
              Blow:
                  "You can't blow through your suit. The polymer seals in your environment.";
              Attack, Burn, Climb, Close, Cut, Dig, Drink, Eat, Empty, Enter, Exit, GetOff, Go, GoIn, JumpOver, Kick, Listen, LookUnder, Open:
                  if (infirmary.alienWrecked) "You can't do that. The cabinets have been smashed and spit on. There's nothing left.";
                  "That's not going to help.";
              Push, PushDir, Pull, Remove, Rub, Set, SetTo, Smell, Squeeze, Swing, SwitchOn, SwitchOff, Take, Talk, Taste, Tie, Touch, Transfer, Turn, Unlock, Wave:
                  if (infirmary.alienWrecked) "You can't do that. The cabinets have been smashed and spit on. There's nothing left.";
                  "That's not going to help.";
          ],
     has  static concealed pluralname;

! 01/10/22

  StObj   -> infirmaryTable "table"
    with  name 'operating' 'table' 'metal' 'examination',
          before [;
              Examine:
                  player.advanceGravity = false;
                  if (infirmary.alienWrecked)
                      "Something heavy slammed into the table. It broke where it was attached to the deck.
                      Then it's been topped off with a layer of acid that slowly burns through the metal.";
                  print "The table is only big enough to hold a single crew member. Along with the auto-doc,
                  it's used during crew examinations. Underneath it is an acid stain";
                  if (knitter in infirmary)", while a tissue knitter has been left out on top of it.";
                  ".";
              Take, Push, Pull, PushDir, Remove, Turn:
                  if (infirmary.alienWrecked) "Really? It's covered in acid, and you'd burn yourself.";
                  "The table isn't going anywhere. It's built into the ship and comes straight out of the deck.";
              Rub:
                  if (infirmary.alienWrecked) "Really? It's covered in acid, and you'd burn yourself.";
                  "You don't have time for that. You are plunging into the sun.";
              LookUnder:
                  if (infirmary.alienWrecked) "The metal has been crushed and then spit on with acid. There's nothing to look under.";
                  "You see a nasty-looking hole that has burned through to the deck below.";
              Attack, Burn, Climb, Close, Cut, Dig, Drink, Eat, Empty, Enter, Exit, GetOff, Go, GoIn, JumpOver, Kick, Listen, LookUnder, Open:
                  if (infirmary.alienWrecked) "Really? It's covered in acid, and you'd burn yourself.";
                  "You need to loot the ship, not mess with ", (the) self, ".";
              Push, PushDir, Pull, Remove, Rub, Set, SetTo, Smell, Squeeze, Swing, SwitchOn, SwitchOff, Take, Talk, Taste, Tie, Touch, Transfer, Turn, Unlock, Wave:
                  if (infirmary.alienWrecked) "Really? It's covered in acid, and you'd burn yourself.";
                  "You need to loot the ship, not mess with ", (the) self, ".";
          ],
     has  supporter;

! 06/02/22

  StObj   -> infirmaryAutoDoc "auto-doc"
    with  name 'auto' 'doc' 'auto-doc' 'machine',
          before [;
              Examine:
                  player.advanceGravity = false;
                  if (infirmary.alienWrecked)
                      "The auto-doc is covered in a layer of acid. As it slowly burns away, smoke comes of it.";
                  "The auto-doc is used to examine crew members but is limited in treatment abilities. When
                  diagnosing any patient, it can only treat them with anti-biotics.";
              Take, Push, Pull, PushDir, Remove, Turn:
                  if (infirmary.alienWrecked) "Really? It's covered in acid, and you'd burn yourself.";
                  "The auto-doc isn't going anywhere. It's built into the side of the ship.";
              Enter:
                  if (infirmary.alienWrecked) "Like everything else in this room, the auto-doc has been covered in acid. You would burn yourself if you tried to get inside.";
                  if (alien.sleeping) "The machine's not working. You have no reason to crawl in there.";
                  "The machine's not working. And if you're trying to hide, that's an awful spot.";
              Rub:
                  if (infirmary.alienWrecked) "Really? It's covered in acid, and you'd burn yourself.";
                  "You don't have time for that. You are plunging into the sun.";
              SwitchOn, SwitchOff:
                  if (infirmary.alienWrecked) "Really? It's covered in acid, and you'd burn yourself.";
                  "There's no power going to the auto-doc. It's not working.";
              Close:
                  if (infirmary.alienWrecked) "Really? It's covered in acid, and you'd burn yourself.";
                  "That's already closed.";
              Open:
                  if (infirmary.alienWrecked) "Really? It's covered in acid, and you'd burn yourself.";
                  "There's no need to open the auto-doc. It's not working.";
              LookUnder:
                  if (infirmary.alienWrecked) "The metal has been crushed and then spit on with acid. There's nothing to look under.";
                  "There is no space to look under. The auto-doc sits firmly on the deck.";
              Attack, Burn, Climb, Close, Cut, Dig, Drink, Eat, Empty, Enter, Exit, GetOff, Go, GoIn, JumpOver, Kick, Listen, LookUnder, Open:
                  if (infirmary.alienWrecked) "Really? It's covered in acid, and you'd burn yourself.";
                  "You need to loot the ship, not mess with ", (the) self, ".";
              Push, PushDir, Pull, Remove, Rub, Set, SetTo, Smell, Squeeze, Swing, SwitchOn, SwitchOff, Take, Talk, Taste, Tie, Touch, Transfer, Turn, Unlock, Wave:
                  if (infirmary.alienWrecked) "Really? It's covered in acid, and you'd burn yourself.";
                  "You need to loot the ship, not mess with ", (the) self, ".";
          ];

! 01/10/22

  StObj   -> infirmaryLight "light"
    with  name 'beam' 'light' 'ray' 'god' 'rays',
          before [;
              Examine:
                  player.advanceGravity = false;
                  "The smoke here tries to block the beam of light that shines down from the middle of the ceiling.";
              Go:
                  "You are already here.";
              Take, Push, Pull, PushDir, Unlock:
                  "The light is recessed into the ceiling. You can't get at it.";
          ];

! 01/10/22

  StObj   -> infirmaryLights "lights"
    with  name 'dim' 'lights' 'glow' 'soft' 'amber' 'led' 'leds',
          before [;
              Examine:
                  player.advanceGravity = false;
                  "There's a ring of lights that wraps around the ceiling, giving the entire room a haunting glow.";
              Go:
                  "You are already here.";
          ],
     has  pluralname;

! 05/13/22

  StObj   -> infirmaryHole "hole"
    with  name 'small' 'hole' 'nasty' 'acid' 'stain',
          before [;
              Examine:
                  player.advanceGravity = false;
                  "A hole burned itself into the deck as acid spilled all over the place - the solution making its way through to B Deck.";
              Go:
                  "You are already here.";
              Take, Push, Pull, PushDir, Unlock:
                  "It's a hole. You can't do that.";
              Open:
                  "It's a small hole in the deck. You would need more acid.";
              Enter:
                   "It's not that big.";
              Search:
                  "Looking through the hole, you can't tell if you see B Deck or not. It's too dark down there.";
          ];

! 12/28/21

  AcidObj infirmaryAcid "acid"
    with  name 'acid' 'pool' 'secretion' 'secretions',
          before [;
              Examine, Search:
                  player.advanceGravity = false;
                  "The acid burns everything it touches, trying to melt all the way through the deck.";
              Go:
                  "You are already here.";
          ];
