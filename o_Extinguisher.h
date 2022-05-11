
! ---------------------------------------------------------------------------- !
!       EXTINGUISHER. 10/26/21
!

Object  extinguisher "extinguisher"
  with  name 'fire' 'extinguisher',
        describe [;
            if (self in portShuttleBay) {
                if (self.spitOn) "^Across from the airlock, there's an extinguisher covered in acid.";
                "^Across from the airlock, there's an extinguisher attached to the bulkhead.";
            }
            rtrue;
        ],
        before [;
            Attack:
                if (self.spitOn) "Even though the foam mixes with the acid, it would splash up into your face and melt it off.";
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
                if (self.spitOn) "Even though the foam mixes with the acid, it would still burn you if you tried that.";
                if (second == dataReader) {
                    if (portShuttleBay.takenExtinguisher) {
                        "That doesn't fit in the reader. You leave ", (the) self, " in the vortex bag.";
                    } else {
                        portShuttleBay.takenExtinguisher = true;
                        move self to vortexBag;
                        print "(first taking picking up ", (the) self, ")^";
                        print "That doesn't fit in the reader, so you move it to the vortex bag.^";
                        return ItemFirstTaken();
                    }
                }
                if (second == aftCompanionwayDeckBLadder || second == forwardCompanionwayDeckALadder || second == forwardCompanionwayDeckBLadder) {
                    if (self in vortexBag) "You don't want to lose that, so you keep it in the bag.";
                }
                if (second == vortexBag) {
                    portShuttleBay.takenExtinguisher = true;
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
                if (self.spitOn) "When the alien destroyed this room, it vomited acid all over the extinguisher. So now the foam mixes with the creature's secretions.";
                "It's a simple extinguisher but large enough for industrial fires. So you should be able to get something for it.";
            Take:
                if (self.spitOn) "The outer casing has melted away. It's worthless.";
                if (self in vortexBag) "You don't need that. You'll be able to sell it later.";
                portShuttleBay.takenExtinguisher = true;
                move self to vortexBag;
                print "You take ", (the) self, ", putting it in the vortex bag.^";
                return ItemFirstTaken();
            PutOn:
                if (self in vortexBag && second has supporter) "You don't want to leave that behind. You'll be able to sell it later once you get off the ship.";
            Rub, Push, Pull, PushDir, Turn:
                if (self.spitOn) "Even though the foam mixes with the acid, it would still burn you if you tried that.";
            ThrowAt:
                if (second == alien) {
                    if (self in vortexBag) {
                        print "You can't quickly get to ", (the) self, ".";
                        return StandingDeath();
                    }
                }
            default:
                if (self.spitOn) "Even though the foam mixes with the acid, it would still burn you if you tried that.";
        ],
        spitOn false;
