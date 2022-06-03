
! ---------------------------------------------------------------------------- !
!       KNITTER. 11/02/21
!

Object  knitter "tissue knitter"
  with  name 'tissue' 'knitter' 'old' 'tool',
        describe [;
            if (self.spitOn) {
                if (medkit in infirmary) "^Next to the broken table, a tissue knitter and a medkit melt in a pool of acid.";
                "^Next to the broken table, a tissue knitter melts in a pool of acid.";
            }
            if (self in infirmary) "^On the examination table, a tissue knitter has been left out.";
            rtrue;
        ],
        before [;
            Attack:
                if (self.spitOn) "Covered in acid, an impact like that would splash on your legs and burn all the way through to your feet.";
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
                    if (infirmary.takenKnitter) {
                        "That doesn't fit in there.";
                    } else {
                        move self to vortexBag;
                        infirmary.takenKnitter = true;
                        print "That doesn't fit in there, so you move it to the vortex bag.^";
                        return ItemFirstTaken();
                    }
                }
                if (second == aftCompanionwayDeckBLadder || second == forwardCompanionwayDeckALadder || second == forwardCompanionwayDeckBLadder) {
                    if (self in vortexBag) "You don't want to lose that, so you keep it in the bag.";
                }
                if (second == vortexBag) {
                    infirmary.takenKnitter = true;
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
                    if (medkit in infirmary) "The tissue knitter boils away in a pool of acid along with a medkit.";
                    "The tissue knitter boils away in a pool of acid.";
                }
                print "The tissue knitter is an old tool that was replaced long ago by bioplast-flesh. ";
                if (infirmary.takenKnitter) "Though it might have some use, you're not going to get that much for it.";
                "It looks like this ship has been floating through space for a long time.";
            Kick:

            Take:
                if (self.spitOn) "It's covered in acid, spit on by the alien. It's worthless.";
                if (self in vortexBag) "You don't need that. You'll be able to sell it later.";
                infirmary.takenKnitter = true;
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
