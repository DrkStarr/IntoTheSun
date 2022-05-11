
! ---------------------------------------------------------------------------- !
!       HOLOGRAM. 01/06/22
!

Object  hologram "hologram"
  with  name 'hologram' 'cube',
        before [;
            Attack:
                "Are you really going to break the stuff you're trying to loot?";
            Drop:
                if (self in vortexBag) {
                    print "(first taking ", (the) self, " from the vortex bag)^";
                    "You should leave it in the vortex bag. You'll be able to sell it later.";
                }
            Go:
                "You are already here.";
            Insert:
                if (second == dataReader) {
                    if (personalLockerRoom.takenHologram) {
                        "That doesn't fit in the reader. You leave ", (the) self, " in the vortex bag.";
                    } else {
                        personalLockerRoom.takenHologram = true;
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
                    personalLockerRoom.takenHologram = true;
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
                "The hologram is a face of a young woman. She slowly spins in a clockwise direction as she wipes away a tear every time she comes around.";
            Take:
                if (self in vortexBag) "You don't need that. You'll be able to sell it later.";
                personalLockerRoom.takenHologram = true;
                move self to vortexBag;
                print "You take ", (the) self, ", putting it in the vortex bag.^";
                return ItemFirstTaken();
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
