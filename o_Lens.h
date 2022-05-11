
! ---------------------------------------------------------------------------- !
!       LENS. 11/15/21
!

Object  lens "lens"
  with  parse_name [w1;
            w1 = NextWord();
            if (w1 ~= 'padded' or 'case' or 'lens') return 0;
            if (w1 == 'padded' or 'case') {
                self.objectCase = true;
                return 3;
            }
            self.objectCase = false;
            return 3;
        ],
        describe [;
            if (instrumentationBay.takenCamera == false) rtrue;
            if (instrumentationBay.takeLens == false) "^A spare lens sits in the corner of this room.";
            rtrue;
        ],
        before [;
            Attack:
                "Are you really going to break the stuff you're trying to loot?";
            Burn:

            Drop:
                if (self in vortexBag) {
                    print "(first taking ", (the) self, " from the vortex bag)^";
                    "You should leave it in the vortex bag. You'll be able to sell it later.";
                }
            Go:
                "You are already here.";
            Insert:
                if (second == dataReader) {
                    if (instrumentationBay.takeLens) {
                        "That doesn't fit in the reader. You leave ", (the) self, " in the vortex bag.";
                    } else {
                        instrumentationBay.takeLens = true;
                        move self to vortexBag;
                        print "(first taking picking up ", (the) self, ")^";
                        "That doesn't fit in the reader, so you move it to the vortex bag.";
                    }
                }
                if (second == aftCompanionwayDeckBLadder || second == forwardCompanionwayDeckALadder || second == forwardCompanionwayDeckBLadder) {
                    if (self in vortexBag) "You don't want to lose that, so you keep it in the bag.";
                }
                if (second == vortexBag) {
                    instrumentationBay.takeLens = true;
                }
                if (self in vortexBag && second == vortexBag) "", (The) self, " is already here.";
                if (self in vortexBag) {
                    "You don't want to leave it behind, so you keep it in the bag.";
                }
            Examine, Search:
                player.advanceGravity = false;
                if (self.objectCase) "The lens is kept in place by a case that's padded on the inside.";
                "Because the lens is so sensitive, and used in gamma-ray and supernova detection, it's kept in a padded case.";
            Take:
                if (self in vortexBag) "You don't need that. You'll be able to sell it later.";
                instrumentationBay.takeLens = true;
                move self to vortexBag;
                "You take ", (the) self, ", putting it in the vortex bag.";
            Open:
                if (self.objectCase) "You should leave the case closed. You don't want to damage the lens. It might be worth something.";
                "That's inside the case.";
            PutOn:
                if (self in vortexBag && second has supporter) "You don't want to leave that behind. You'll be able to sell it later once you get off the ship.";
            ThrowAt:
                if (second == alien) {
                    if (self in vortexBag) {
                        print "You can't quickly get to ", (the) self, ".";
                        return StandingDeath();
                    }
                }
        ],
        objectCase false;
