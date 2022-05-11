
! ---------------------------------------------------------------------------- !
!       CAMERA. 11/15/21
!

Object  camera "camera"
  with  name 'camera',
        describe [;
            if (instrumentationBay.takenCamera == false) {
                if (instrumentationBay.takeLens == false) "^An extra camera plus a spare lens sit in the corner of this room.";
                "^An extra camera sits in the corner of this room.";
            }
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
                    if (instrumentationBay.takenCamera) {
                        "That doesn't fit in the reader. You leave ", (the) self, " in the vortex bag.";
                    } else {
                        instrumentationBay.takenCamera = true;
                        move self to vortexBag;
                        print "(first taking picking up ", (the) self, ")^";
                        "That doesn't fit in the reader, so you move it to the vortex bag.";
                    }
                }
                if (second == aftCompanionwayDeckBLadder || second == forwardCompanionwayDeckALadder || second == forwardCompanionwayDeckBLadder) {
                    if (self in vortexBag) "You don't want to lose that, so you keep it in the bag.";
                }
                if (second == vortexBag) {
                    instrumentationBay.takenCamera = true;
                }
                if (self in vortexBag && second == vortexBag) "", (The) self, " is already here.";
                if (self in vortexBag) {
                    "You don't want to leave it behind, so you keep it in the bag.";
                }
            Examine, Search:
                player.advanceGravity = false;
                "Used in light-sensitive photography, the camera might be worth something to an astronomer.";
            Take:
                if (self in vortexBag) "You don't need that. You'll be able to sell it later.";
                if (instrumentationBay.takenCamera == false) {
                    instrumentationBay.takenCamera = true;
                    move self to vortexBag;
                    "You take ", (the) self, ", putting it in the vortex bag.";
                }
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
