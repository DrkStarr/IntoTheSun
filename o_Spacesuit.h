
! ---------------------------------------------------------------------------- !
!       SPACESUIT. 10/27/21
!

Object  spacesuit "oversized spacesuit"
  with  name 'oversized' 'spacesuit' 'suit',
        describe [;
            if (self in starboardShuttleBay) {
                if (self.spitOn) "^An oversized spacesuit is covered in acid, boiling away as it sits across from the airlock.";
                "^An oversized spacesuit sits across from the airlock. Bunched up on the ground. Forgotten.";
            }
            rtrue;
        ],
        before [;
            Attack:
                if (self.spitOn) "It's covered in acid. Hitting it would cause it to spray back up on yourself. You could try to dodge, but it would catch your feet.";
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
                if (self.spitOn) "It's covered in acid. The alien sprayed all over it before he left the room.";
                if (second == dataReader) {
                    if (starboardShuttleBay.takenSuit) {
                        "That doesn't fit in there.";
                    } else {
                        move self to vortexBag;
                        starboardShuttleBay.takenSuit = true;
                        print "That doesn't fit in there, so you move it to the vortex bag.^";
                        return ItemFirstTaken();
                    }
                }
                if (second == aftCompanionwayDeckBLadder || second == forwardCompanionwayDeckALadder || second == forwardCompanionwayDeckBLadder) {
                    if (self in vortexBag) "You don't want to lose that, so you keep it in the bag.";
                }
                if (second == vortexBag) {
                    starboardShuttleBay.takenSuit = true;
                    move self to vortexBag;
                    print "You take the oversized spacesuit, cramming it in the hole as the bag pulls it into the vortex.^";
                    return ItemFirstTaken();
                }
                if (self in vortexBag && second == vortexBag) "", (The) self, " is already here.";
                if (self in vortexBag) {
                    "You don't want to leave it behind, so you keep it in the bag.";
                }
            Examine, Search:
                player.advanceGravity = false;
                if (self.spitOn) "Acid's been sprayed back and forth across this spacesuit. What's left slowly melts away.";
                "The oversized spacesuit is comical, like that old footage from the moon landing. It's as old as the ship or older. Who knows what it would be worth.";
            Kick:

            Take:
                if (self.spitOn) "It's covered in acid. It's worthless.";
                if (self in vortexBag) "You don't need that. You'll be able to sell it later.";
                starboardShuttleBay.takenSuit = true;
                move self to vortexBag;
                print "You take the oversized spacesuit, cramming it in the hole as the bag pulls it into the vortex.^";
                return ItemFirstTaken();
            Rub, Push, Pull, PushDir, Turn:
                if (self.spitOn) "It's covered in acid. The alien sprayed all over it before he left the room.";
            PutOn:
                if (self in vortexBag && second has supporter) "You don't want to leave that behind. You'll be able to sell it later once you get off the ship.";
            ThrowAt:
                if (second == alien) {
                    if (self in vortexBag) {
                        print "You can't quickly get to ", (the) self, ".";
                        return StandingDeath();
                    }
                }
            Wear:
                if (self.spitOn) "It's covered in acid. You don't want to do that.";
                "It's a big, bulky suit that would be too hard to move around in. Plus, it might be worth something.";
            default:
                if (self.spitOn) "It's covered in acid. There's no need to do that.";
        ],
        spitOn false;
