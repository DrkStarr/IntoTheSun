
! ---------------------------------------------------------------------------- !
!       DATA READER. 11/05/21
!

Object  dataReader "data reader"
  with  name 'data' 'reader' 'pad' 'tablet' 'screen' 'ph017' 'device',
        describe [;
            if (self in personalLockerRoom) "^A data reader used to record ship logs sits on the edge of the bench.";
            rtrue;
        ],
        before [;
            Attack:
                "This tool is invaluable. You think twice about breaking it.";
            Burn:

            Drop:
                if (self in player || self in vortexBag) "You don't want to do that. You can at least try to sell it later.";
            Go:
                "You are already here.";
            Insert:
                if (self in vortexBag && second == vortexBag) "", (The) self, " is already here.";
                if (second == vortexBag) {
                    move self to vortexBag;
                    personalLockerRoom.takenDataReader = true;
                    print "You put the data reader into the vortex bag. Even though it contracts, you can still read the screen.^";
                    return ItemFirstTaken();
                }
                if (second == musicBox || second == maintenanceGaragePanel || second == computerRoomPanel) {
                    "That doesn't fit in there.";
                }
                if (second == infirmaryCabinet || second == personalLockerRoomLocker) {
                    "That doesn't belong in there.";
                }
                if (second == aftCompanionwayDeckBLadder || second == forwardCompanionwayDeckALadder || second == forwardCompanionwayDeckBLadder) {
                    "You don't want to lose that.";
                }
            Examine, Search:
                player.advanceGravity = false;
                if (yellowFlashCard in self) {
                    print "The screen lights up with a green phosphorous glow.^^";
                    style fixed;
                    self.knowDoorCode = true;
                    print "*******************^";
                    print " MAINTENANCE ORDER^";
                    print "*******************^";
                    print "^Change all the door locks. It looks like Ripley figured them out again. But I don't
                    want to have to remember a million numbers, so input ", door_code-->0, ". And put it on all
                    the locks, that should really piss her off next time.^";
                    print "^                    ";
                    style roman;
                    "- Parker";
                }
                if (redFlashcard in self) {
                    print "The screen lights up with a green phosphorous glow.^^";
                    style fixed;
                    print "***************^";
                    print " CAPTAIN'S LOG^";
                    print "***************^";
                    print "^June 2, 2122^
                    MU/TH/UR woke us up to investigate a signal from an uncharted planet in the Zeta II Reticuli system.^
                    ^June 3, 2122^
                    Touch down. Damage to the Nostromo. 24 hours to repair. Investigated the signal. Kane was infected.^
                    ^June 5, 2122^
                    Left planet. Nostromo docked with the refinery. Set course back to Earth.^
                    ^June 10, 2122^
                    Kane's dead. There's a xenomorph aboard the vessel. A creature came out of the executive officer. If we don't handle this thing, none of us are going to make it out alive.^
                    ^June 11, 2122^
                    Someone needs to go into the vents and kill this creature. I'm the one to do it. This ship's my responsibility.^";
                    print "^                    ";
                    style roman;
                    "- Dallas";
                }
                "The data reader is an outdated logging device used by the ship's personal.
                Colored flashcards can be inserted into the reader, which will display the
                information on the screen.";
            Kick:

            Take:
                if (self in player) "You already have that.";
                if (personalLockerRoom.takenDataReader == false) {
                    personalLockerRoom.takenDataReader = true;
                    move self to player;
                    print "You take the data reader, this thing might come in handy.^";
                    return ItemFirstTaken();
                }
            PutOn:
                if (self in player || self in vortexBag) {
                    if (second has supporter) "You don't want to leave that behind.";
                }
            Close, Open:
                "It doesn't work like that. You slide flashcards in and out of it.";
            SwitchOn:
                "The data reader doesn't work like that. Instead, it comes on automatically when a flashcard is inserted.";
            SwitchOff:
                "The data reader doesn't work like that. Instead, it shuts off automatically when the flashcard is removed.";
            ThrowAt:
                if (second == alien) {
                    if (self in vortexBag) {
                        deadflag = 1;
                        "You can't quickly get to the data reader.^^The xenomorph swings at you, crushing bones and breaking ribs as you go flying into a bulkhead. Then it comes at you, mouth open, claws reaching, ready to finish the job. It doesn't take long before you bleed out, only to be crushed from the pressure of the sun.";
                    }
                    if (self in player) {
                        deadflag = 1;
                        "You throw the data reader, but it bounces off the creature as the beast smacks it out of the way.^^With its other hand, the xenomorph swings at you, crushing bones and breaking ribs as you go flying into a bulkhead. Then it comes at you, mouth open, claws reaching, ready to finish the job. It doesn't take long before you bleed out, only to be crushed from the pressure of the sun.";
                    }
                }
        ],
        knowDoorCode false,
   has  container open;
