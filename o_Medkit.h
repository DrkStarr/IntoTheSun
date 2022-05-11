
! ---------------------------------------------------------------------------- !
!       MEDKIT. 12/28/21
!

Object  medkit "medkit"
  with  name 'medkit' 'med' 'kit',
        describe [;
            if (self in infirmary) {
                if (knitter in infirmary) {} else {
                    "^Next to the broken table, a medkit melts in a pool of acid.";
                }
            }
            rtrue;
        ],
        before [;
            Attack:
                if (self.spitOn) "Covered in acid, hitting the kit would cause the secretions to kick back up, spraying all over yourself.";
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
                if (self.spitOn) "Covered in acid, you would burn yourself if you tried that.";
                if (second == dataReader) {
                    if (infirmary.takenMedkit) {
                        "That doesn't fit in there.";
                    } else {
                        move self to vortexBag;
                        infirmary.takenMedkit = true;
                        print "That doesn't fit in there, so you move it to the vortex bag.^";
                        return ItemFirstTaken();
                    }
                }
                if (second == aftCompanionwayDeckBLadder || second == forwardCompanionwayDeckALadder || second == forwardCompanionwayDeckBLadder) {
                    if (self in vortexBag) "You don't want to lose that, so you keep it in the bag.";
                }
                if (second == vortexBag) {
                    infirmary.takenMedkit = true;
                    move self to vortexBag;
                    print "You put ", (the) self, " into the vortex bag.^";
                    return ItemFirstTaken();
                }
                if (self in vortexBag && second == vortexBag) "", (The) self, " is already here.";
                if (self in vortexBag) {
                    "You don't want to leave it behind, so you keep it in the bag.";
                }
          Examine, Search:
                player.advanceGravity = false;
                if (self.spitOn) {
                    if (knitter in infirmary) "The medkit dissolves in a pool of acid, along with a tissue knitter.";
                    "The medkit dissolves in a pool of acid next to a broken table that's also covered in the stuff.";
                }
                "It's an older first aid treatment that will stop the bleeding even if it has to cauterize the wound. Then the kit will inject anti-biotics.";
            Kick:

            Take:
                if (self.spitOn) "It's covered in acid, spit on by the alien. It's worthless.";
                if (self in vortexBag) "You don't need that. You'll be able to sell it later.";
                infirmary.takenMedkit = true;
                move self to vortexBag;
                print "You take ", (the) self, ", putting it in the vortex bag.^";
                return ItemFirstTaken();
            PutOn:
                if (self in vortexBag && second has supporter) "You don't want to leave that behind. You'll be able to sell it later once you get off the ship.";
            Rub, Push, Pull, PushDir, Turn:
                if (self.spitOn) "Covered in acid, you would burn yourself if you tried that.";
            ThrowAt:
                if (second == alien) {
                    if (self in vortexBag) {
                        print "You can't quickly get to ", (the) self, ".";
                        return StandingDeath();
                    }
                }
            default:
                if (self.spitOn) "It's covered in acid. There's no need to do that.";
        ],
        spitOn false;
