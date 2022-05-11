
! ---------------------------------------------------------------------------- !
!       TRINKET. 11/15/21
!
!   ***  Frosty came up with the idea of crystal like star  ***

Object  trinket "trinket"
  with  name 'trinket' 'crystal' 'star' 'silver',
        describe [;
            if (self in bridge) "^The command chairs are empty, except for a trinket that has been left behind on one of them.";
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
                    if (bridge.takenTrinket) {
                        "That doesn't fit in there.";
                    } else {
                        move self to vortexBag;
                        bridge.takenTrinket = true;
                        "That doesn't fit in there, so you move it to the vortex bag.";
                    }
                }
                if (second == aftCompanionwayDeckBLadder || second == forwardCompanionwayDeckALadder || second == forwardCompanionwayDeckBLadder) {
                    if (self in vortexBag) "You don't want to lose that, so you keep it in the bag.";
                }
                if (second == vortexBag) {
                    bridge.takenTrinket = true;
                }
                if (self in vortexBag && second == vortexBag) "", (The) self, " is already here.";
                if (self in vortexBag) {
                    "You don't want to leave it behind, so you keep it in the bag.";
                }
            Examine, Search:
                player.advanceGravity = false;
                "The trinket is a crystal that's coated in silver. It reminds you of a captured star.";
            Kick:

            Take:
                if (self in vortexBag) "You don't need that. You'll be able to sell it later.";
                bridge.takenTrinket = true;
                move self to vortexBag;
                "You take ", (the) self, ", putting it in the vortex bag.";
            PutOn:
                if (self in vortexBag && second has supporter) "You don't want to leave that behind. You'll be able to sell it later once you get off the ship.";
            ThrowAt:
                if (second == alien) {
                    if (self in vortexBag) {
                        print "You can't quickly get to ", (the) self, ".";
                        return StandingDeath();
                    }
                }
        ];
