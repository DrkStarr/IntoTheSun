
! ---------------------------------------------------------------------------- !
!       NECKLACE. 11/03/21
!

Object  necklace "necklace"
  with  name 'necklace' 'jewelry' 'chain',
        describe [;
            if (self in hypersleepVault) {
                if (self.spitOn) "^Lying in the middle of this destruction, a necklace melts in the acid.";
                "^Hanging off one of the pods is a necklace sparkling in the amber light.";
            }
            rtrue;
        ],
        before [;
            Attack:
                if (self.spitOn) "The acid would splash on you if you did that. It would melt through your torso, taking out your crotch.";
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
                if (self.spitOn) "You'd burn yourself if you did that. It's covered in acid.";
                if (second == dataReader) {
                    if (hypersleepVault.takenNecklace) {
                        move self to vortexBag;
                        "That doesn't fit in there.";
                    } else {
                        move self to vortexBag;
                        hypersleepVault.takenNecklace = true;
                        print "That doesn't fit in there, so you move it to the vortex bag.^";
                        return ItemFirstTaken();
                    }
                }
                if (second == aftCompanionwayDeckBLadder || second == forwardCompanionwayDeckALadder || second == forwardCompanionwayDeckBLadder) {
                    if (self in vortexBag) "You don't want to lose that, so you keep it in the bag.";
                }
                if (second == vortexBag) {
                    hypersleepVault.takenNecklace = true;
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
                if (self.spitOn) "What must have been a nice silver necklace melts in the acid sprayed throughout the room.";
                if (hypersleepVault.takenNecklace) "The necklace was small when you took it. Now it's tiny, lying at the bottom of the bag.";
                "A silver necklace hangs off one of the pods. It sways back and forth as the ship drifts through space. It looks forgotten but has value.";
            Kick:

            Take:
                if (self.spitOn) "It's covered in acid and is worthless.";
                if (self in vortexBag) "You don't need that. You'll be able to sell it later.";
                hypersleepVault.takenNecklace = true;
                move self to vortexBag;
                print "You take ", (the) self, ", putting it in the vortex bag.^";
                return ItemFirstTaken();
            PutOn:
                if (self in vortexBag && second has supporter) "You don't want to leave that behind. You'll be able to sell it later once you get off the ship.";
            Rub, Push, Pull, PushDir, Turn:
                if (self.spitOn) "You'd burn yourself if you did that. It's covered in acid.";
            Wear:
                if (hypersleepVault.takenNecklace) "You don't need to wear the jewelry. It's safe where it is. You'll be able to sell it later.";
                "You don't need to wear the jewelry. You need to loot the ship before you burn up in the sun.";
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
