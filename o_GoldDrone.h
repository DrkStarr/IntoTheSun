
! ---------------------------------------------------------------------------- !
!       DRONE. 10/29/21
!

Object  drone "gold drone"
  with  name 'gold' 'drone',
        describe [;
            if (self in clawChamber) "^Lying on the deck, by the skeleton, is a gold drone.";
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
                ! *********************************
                ! Because The Drone Is On The Bench
                ! *********************************
                if (clawChamber.takenDrone == false) {
                    clawChamber.takenDrone = true;
                    move self to vortexBag;
                    print "(first taking the gold drone off the bench)^";
                    "You don't need to leave it behind, so you put it in the vortex bag.";
                }
            Insert:
                if (second == dataReader) {
                    if (clawChamber.takenDrone) {
                        "That doesn't fit in the reader. You leave the drone in the vortex bag.";
                    } else {
                        move self to vortexBag;
                        clawChamber.takenDrone = true;
                        print "(first taking the gold drone off the bench)^";
                        "That doesn't fit in the reader, so you move it to the vortex bag.";
                    }
                }
                if (second == aftCompanionwayDeckBLadder || second == forwardCompanionwayDeckALadder || second == forwardCompanionwayDeckBLadder) {
                    if (self in vortexBag) "You don't want to lose that, so you keep it in the bag.";
                }
                if (second == vortexBag) {
                    clawChamber.takenDrone = true;
                }
                if (self in vortexBag && second == vortexBag) "", (The) self, " is already here.";
                if (self in vortexBag) {
                    "You don't want to leave it behind, so you keep it in the bag.";
                }
            Go:
                "You are already here.";
            Examine, Search:
                player.advanceGravity = false;
                print "Using electrostatic plating, gold has been adhered to the drone,
                making it usable in some of the harshest conditions. ";
                if (clawChamber.takenDrone) "You should get good money for this.";
                "For this vessel, it's used during inspections.";
            Kick:

            Take:
                if (self in vortexBag) "You don't need that. You'll be able to sell it later.";
                clawChamber.takenDrone = true;
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
